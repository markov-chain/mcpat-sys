use xml_parse::ParseXML;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct Processor;

extern "C" {
    pub fn new_Processor(parsexml: *mut ParseXML) -> *mut Processor;
    pub fn delete_Processor(processor: *mut Processor);
}
