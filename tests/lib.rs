#![allow(non_snake_case)]

extern crate mcpat_sys;

use mcpat_sys::*;
use std::collections::HashMap;

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
    let system = &*ParseXML_sys(parsexml);

    check(system, powerDef_readOp(Processor_power(processor)), hash_map!(
        "Peak Power" => 134.938,
        "Total Leakage" => 36.8319,
        "Peak Dynamic" => 98.1063,
        "Subthreshold Leakage" => 35.1632,
        "Subthreshold Leakage with power gating" => 16.3977,
        "Gate Leakage" => 1.66871,
    ));

    check(system, powerDef_readOp(Processor_rt_power(processor)), hash_map!(
        "Runtime Dynamic" => 72.9199,
    ));

    let numCore = Processor_numCore(processor);
    assert_eq!(numCore, 1);

    let numL2 = Processor_numL2(processor);
    assert_eq!(numL2, 1);

    let numL3 = Processor_numL3(processor);
    assert_eq!(numL3, 1);
}

unsafe fn check(system: &root_system, readOp: *mut powerComponents, map: HashMap<&str, f64>) {
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
    let subthreshold_leakage_with_power_gating = if long_channel {
                                                     power_gated_with_long_channel_leakage
                                                 } else {
                                                     power_gated_leakage
                                                 };

    for (key, value) in map {
        match key {
            "Peak Power" => {
                equal(value, dynamic + total_leakage);
            },
            "Total Leakage" => {
                equal(value, total_leakage);
            },
            "Peak Dynamic" => {
                equal(value, dynamic);
            },
            "Subthreshold Leakage" => {
                equal(value, subthreshold_leakage);
            },
            "Subthreshold Leakage with power gating" => {
                assert!(power_gating);
                equal(value, subthreshold_leakage_with_power_gating);
            },
            "Gate Leakage" => {
                equal(value, gate_leakage);
            },
            "Runtime Dynamic" => {
                equal(value, dynamic);
            },
            _ => {
                assert!(false);
            },
        }
    }
}

fn equal(expected: f64, actual: f64) {
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
