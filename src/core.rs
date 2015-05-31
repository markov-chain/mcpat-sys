use libc::c_double;

use cacti::cacti_interface::powerDef;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct Core;

extern "C" {
    pub fn Core_power(this: *mut Core) -> *mut powerDef;
    pub fn Core_rt_power(this: *mut Core) -> *mut powerDef;
    pub fn Core_clockRate(this: *mut Core) -> c_double;
    pub fn Core_executionTime(this: *mut Core) -> c_double;
}
