#![allow(non_snake_case)]

extern crate mcpat_sys;

use mcpat_sys::*;
use std::collections::HashMap;

enum Action {
    CompareWith(f64),
    CompareWithProcessed(f64, Box<Fn(f64) -> f64>),
}

macro_rules! ok(
    ($result:expr) => ($result.unwrap());
);

macro_rules! c_str(
    ($string:expr) => (ok!(::std::ffi::CString::new($string)));
);

macro_rules! hash_map(
    ($($key:expr => $value:expr,)*) => ({
        let mut map = HashMap::new();
        $(map.insert($key, $value);)*
        map
    });
);

// https://github.com/copies/mcpat/blob/master/main.cc
// https://github.com/copies/mcpat/blob/master/ProcessorDescriptionFiles/Xeon.xml
// https://github.com/copies/mcpat/blob/master/ExampleResults/Xeon
#[test]
fn main() {
    let filename = c_str!("build/source/ProcessorDescriptionFiles/Xeon.xml");

    unsafe {
        set_opt_for_clk(1);

        let parsexml = new_ParseXML();
        ParseXML_parse(parsexml, filename.as_ptr() as *mut _);

        let processor = new_Processor(parsexml);
        Processor_displayEnergy(processor, parsexml);

        delete_Processor(processor);
        delete_ParseXML(parsexml);
    }
}

unsafe fn Processor_displayEnergy(processor: *mut Processor, parsexml: *mut ParseXML) {
    use Action::*;

    let system = &*ParseXML_sys(parsexml);

    check(system, powerDef_readOp(Processor_power(processor)), hash_map!(
        "Peak Power" => CompareWith(134.938),
        "Total Leakage" => CompareWith(36.8319),
        "Peak Dynamic" => CompareWith(98.1063),
        "Subthreshold Leakage" => CompareWith(35.1632),
        "Subthreshold Leakage with power gating" => CompareWith(16.3977),
        "Gate Leakage" => CompareWith(1.66871),
    ));

    check(system, powerDef_readOp(Processor_rt_power(processor)), hash_map!(
        "Runtime Dynamic" => CompareWith(72.9199),
    ));

    let numCore = Processor_numCore(processor);
    assert_eq!(numCore, 1);

    let numL2 = Processor_numL2(processor);
    assert_eq!(numL2, 1);

    let numL3 = Processor_numL3(processor);
    assert_eq!(numL3, 1);

    let core = Processor_cores(processor, 0);

    let clockRate = Core_clockRate(core);
    check(system, powerDef_readOp(Core_power(core)), hash_map!(
        "Peak Dynamic" => CompareWithProcessed(39.2989, Box::new(move|v| v * clockRate)),
        "Subthreshold Leakage" => CompareWith(12.0565),
        "Subthreshold Leakage with power gating" => CompareWith(5.15028),
        "Gate Leakage" => CompareWith(0.74513),
    ));

    let executionTime = Core_executionTime(core);
    check(system, powerDef_readOp(Core_rt_power(core)), hash_map!(
        "Runtime Dynamic" => CompareWithProcessed(55.7891, Box::new(move|v| v / executionTime)),
    ));

    assert!(system.Private_L2 > 0);
    let l2cache = Core_l2cache(core);

    let clockRate = CacheDynParam_clockRate(SharedCache_cachep(l2cache));
    check(system, powerDef_readOp(SharedCache_power(l2cache)), hash_map!(
        "Peak Dynamic" => CompareWithProcessed(3.16559, Box::new(move|v| v * clockRate)),
        "Subthreshold Leakage" => CompareWith(2.73387),
        "Subthreshold Leakage with power gating" => CompareWith(1.3859),
        "Gate Leakage" => CompareWith(0.0221925),
    ));

    let executionTime = CacheDynParam_executionTime(SharedCache_cachep(l2cache));
    check(system, powerDef_readOp(SharedCache_rt_power(l2cache)), hash_map!(
        "Runtime Dynamic" => CompareWithProcessed(7.23071, Box::new(move|v| v / executionTime)),
    ));

    let l3 = Processor_l3(processor);

    check(system, powerDef_readOp(Component_power(l3)), hash_map!(
        "Peak Dynamic" => CompareWith(6.70159),
        "Subthreshold Leakage" => CompareWith(10.9824),
        "Subthreshold Leakage with power gating" => CompareWith(6.06659),
        "Gate Leakage" => CompareWith(0.165767),
    ));

    check(system, powerDef_readOp(Component_rt_power(l3)), hash_map!(
        "Runtime Dynamic" => CompareWith(4.32382),
    ));
}

unsafe fn check(system: &root_system, readOp: *mut powerComponents, map: HashMap<&str, Action>) {
    use Action::*;

    let long_channel = system.longer_channel_device != 0;
    let power_gating = system.power_gating != 0;

    let dynamic = powerComponents_dynamic(readOp);
    let leakage = powerComponents_leakage(readOp);
    let gate_leakage = powerComponents_gate_leakage(readOp);
    let longer_channel_leakage = powerComponents_longer_channel_leakage(readOp);
    let power_gated_leakage = powerComponents_power_gated_leakage(readOp);
    let power_gated_with_long_channel_leakage = powerComponents_power_gated_with_long_channel_leakage(readOp);

    let subthreshold_leakage = if long_channel { longer_channel_leakage } else { leakage };
    let total_leakage = subthreshold_leakage + gate_leakage;

    for (key, action) in map {
        let actual = match key {
            "Peak Power" => dynamic + total_leakage,
            "Total Leakage" => total_leakage,
            "Peak Dynamic" => dynamic,
            "Subthreshold Leakage" => subthreshold_leakage,
            "Subthreshold Leakage with power gating" => {
                assert!(power_gating);
                if long_channel {
                    power_gated_with_long_channel_leakage
                } else {
                    power_gated_leakage
                }
            },
            "Gate Leakage" => gate_leakage,
            "Runtime Dynamic" => dynamic,
            _ => panic!("encountered an unknown quantity"),
        };
        match action {
            CompareWith(expected) => equal(actual, expected),
            CompareWithProcessed(expected, process) => equal(process(actual), expected),
        }
    }
}

fn equal(actual: f64, expected: f64) {
    let (mut precision, mut scale) = (1i32, 1f64);
    loop {
        if (expected * scale).round() / scale == expected {
            break;
        }
        precision += 1;
        scale = 10f64.powi(precision);
        assert!(precision < 16);
    }
    assert_eq!((actual * scale).round() / scale, expected);
}
