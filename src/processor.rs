use libc::c_int;

use cacti::component::Component;
use core::Core;
use sharedcache::SharedCache;
use xml_parse::ParseXML;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct Processor;

extern "C" {
    pub fn new_Processor(parsexml: *mut ParseXML) -> *mut Processor;
    pub fn delete_Processor(this: *mut Processor);
    pub fn Processor_cores(this: *mut Processor, i: c_int) -> *mut Core;
    pub fn Processor_l3array(this: *mut Processor, i: c_int) -> *mut SharedCache;
    pub fn Processor_l3(this: *mut Processor) -> *mut Component;
    pub fn Processor_numCore(this: *mut Processor) -> c_int;
    pub fn Processor_numL2(this: *mut Processor) -> c_int;
    pub fn Processor_numL3(this: *mut Processor) -> c_int;
    pub fn Processor_numNOC(this: *mut Processor) -> c_int;
    pub fn Processor_numL1Dir(this: *mut Processor) -> c_int;
    pub fn Processor_numL2Dir(this: *mut Processor) -> c_int;
}
