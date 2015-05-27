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

        let system = &*ParseXML_sys(parsexml);
        assert_eq!(system.number_of_cores, 2);
        assert_eq!(system.L2[0].read_accesses, 200000.0);
        assert_eq!(system.L2[0].write_accesses, 27276.0);

        let processor = new_Processor(parsexml);

        delete_Processor(processor);
        delete_ParseXML(parsexml);
    }
}
