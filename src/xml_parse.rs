use libc::c_char;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct ParseXML;

extern "C" {
    pub fn new_ParseXML() -> *mut ParseXML;
    pub fn delete_ParseXML(parsexml: *mut ParseXML);
    pub fn ParseXML_parse(parsexml: *mut ParseXML, filename: *mut c_char);
}
