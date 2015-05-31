use cacti::cacti_interface::powerDef;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct Component;

extern "C" {
    pub fn Component_power(this: *mut Component) -> *mut powerDef;
    pub fn Component_rt_power(this: *mut Component) -> *mut powerDef;
}
