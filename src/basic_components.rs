use libc::c_double;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct CacheDynParam;

extern "C" {
    pub fn CacheDynParam_clockRate(this: *mut CacheDynParam) -> c_double;
    pub fn CacheDynParam_executionTime(this: *mut CacheDynParam) -> c_double;
}
