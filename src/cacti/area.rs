use libc::c_double;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct Area;

extern "C" {
    pub fn Area_get_w(this: *mut Area) -> c_double;
    pub fn Area_get_h(this: *mut Area) -> c_double;
    pub fn Area_get_area(this: *mut Area) -> c_double;
}
