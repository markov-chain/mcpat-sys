use basic_components::CacheDynParam;
use cacti::cacti_interface::powerDef;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct SharedCache;

extern "C" {
    pub fn SharedCache_power(this: *mut SharedCache) -> *mut powerDef;
    pub fn SharedCache_rt_power(this: *mut SharedCache) -> *mut powerDef;
    pub fn SharedCache_cachep(this: *mut SharedCache) -> *mut CacheDynParam;
}
