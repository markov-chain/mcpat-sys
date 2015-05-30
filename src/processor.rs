use cacti::cacti_interface::powerDef;
use xml_parse::ParseXML;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct Processor;

extern "C" {
    pub fn new_Processor(parsexml: *mut ParseXML) -> *mut Processor;
    pub fn delete_Processor(this: *mut Processor);
    pub fn Processor_power(this: *mut Processor) -> *mut powerDef;
}
