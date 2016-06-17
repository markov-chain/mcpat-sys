#![allow(improper_ctypes, non_snake_case)]

extern crate libc;

use libc::c_int;

#[cfg(feature = "caching")]
use libc::c_char;

mod basic_components;
mod cacti;
mod core;
mod processor;
mod sharedcache;
mod xml_parse;

pub use basic_components::*;
pub use cacti::area::*;
pub use cacti::cacti_interface::*;
pub use cacti::component::*;
pub use core::*;
pub use processor::*;
pub use sharedcache::*;
pub use xml_parse::*;

extern "C" {
    pub fn opt_for_clk_set(value: c_int);
}

#[cfg(feature = "caching")]
extern "C" {
    pub fn cache_activate(host: *const c_char, port: c_int) -> c_int;
    pub fn cache_deactivate();
}
