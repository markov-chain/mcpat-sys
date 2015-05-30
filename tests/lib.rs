#![allow(non_snake_case)]

extern crate mcpat_sys;

use mcpat_sys::*;

macro_rules! ok(
    ($result:expr) => ($result.unwrap());
);

macro_rules! to_c_str(
    ($string:expr) => (ok!(::std::ffi::CString::new($string)));
);

// https://github.com/copies/mcpat/blob/master/main.cc
#[test]
fn main() {
    let filename = to_c_str!("build/source/ProcessorDescriptionFiles/Xeon.xml");

    unsafe {
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

    let (dynamic, longer_channel_leakage, leakage, gate_leakage) = (
        powerComponents_dynamic(readOp),
        powerComponents_longer_channel_leakage(readOp),
        powerComponents_leakage(readOp),
        powerComponents_gate_leakage(readOp),
    );

    assert_eq!(dynamic, 9.810634623075116e+01);
    assert_eq!(134.938, dynamic +
                        if long_channel { longer_channel_leakage } else { leakage } +
                        gate_leakage);
}
