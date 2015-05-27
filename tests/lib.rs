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

        delete_Processor(processor);
        delete_ParseXML(parsexml);
    }
}
