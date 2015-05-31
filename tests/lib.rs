#![allow(non_snake_case)]

extern crate mcpat_sys;

use mcpat_sys::*;

macro_rules! ok(
    ($result:expr) => ($result.unwrap());
);

macro_rules! to_c_str(
    ($string:expr) => (ok!(::std::ffi::CString::new($string)));
);

macro_rules! round(
    ($value:expr, $precision:expr) => ({
        let scale = 10f64.powi($precision);
        ($value * scale).round() / scale
    });
);

// https://github.com/copies/mcpat/blob/master/main.cc
#[test]
fn main() {
    let filename = to_c_str!("build/source/ProcessorDescriptionFiles/Xeon.xml");

    unsafe {
        set_opt_for_clk(1);

        let parsexml = new_ParseXML();
        ParseXML_parse(parsexml, filename.as_ptr() as *mut _);

        let processor = new_Processor(parsexml);
        display_energy(parsexml, processor);

        delete_Processor(processor);
        delete_ParseXML(parsexml);
    }
}

unsafe fn display_energy(parsexml: *mut ParseXML, processor: *mut Processor) {
    let system = &*ParseXML_sys(parsexml);

    let long_channel = system.longer_channel_device != 0;
    let power_gating = system.power_gating != 0;

    let power = Processor_power(processor);
    let readOp = powerDef_readOp(power);

    let dynamic = powerComponents_dynamic(readOp);
    let leakage = powerComponents_leakage(readOp);
    let gate_leakage = powerComponents_gate_leakage(readOp);
    let longer_channel_leakage = powerComponents_longer_channel_leakage(readOp);
    let power_gated_leakage = powerComponents_power_gated_leakage(readOp);
    let power_gated_with_long_channel_leakage = powerComponents_power_gated_with_long_channel_leakage(readOp);

    let peak_dynamic = dynamic;
    let subthreshold_leakage = if long_channel { longer_channel_leakage } else { leakage };
    let total_leakage = subthreshold_leakage + gate_leakage;
    let peak_power = peak_dynamic + total_leakage;
    let subthreshold_leakage_with_power_gating = if long_channel {
                                                     power_gated_with_long_channel_leakage
                                                 } else {
                                                     power_gated_leakage
                                                 };

    assert_eq!(round!(peak_power, 3), 134.938);
    assert_eq!(round!(total_leakage, 4), 36.8319);
    assert_eq!(round!(peak_dynamic, 4), 98.1063);
    assert_eq!(round!(subthreshold_leakage, 4), 35.1632);
    if power_gating {
        assert_eq!(round!(subthreshold_leakage_with_power_gating, 4), 16.3977);
    }
    assert_eq!(round!(gate_leakage, 5), 1.66871);
}
