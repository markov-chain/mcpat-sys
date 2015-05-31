#![allow(non_snake_case)]

extern crate libc;

use libc::c_int;

mod basic_components;
mod cacti;
mod core;
mod processor;
mod sharedcache;
mod xml_parse;

pub use basic_components::*;
pub use cacti::cacti_interface::*;
pub use core::*;
pub use processor::*;
pub use sharedcache::*;
pub use xml_parse::*;

extern "C" {
    pub fn set_opt_for_clk(value: c_int);
}
