use basic_components::CacheDynParam;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct SharedCache;

extern "C" {
    pub fn SharedCache_cachep(this: *mut SharedCache) -> *mut CacheDynParam;
}
