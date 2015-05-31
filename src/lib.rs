#![allow(non_snake_case)]

extern crate libc;

use libc::c_int;

mod cacti;
mod core;
mod processor;
mod xml_parse;

pub use cacti::cacti_interface::*;
pub use core::*;
pub use processor::*;
pub use xml_parse::*;

extern "C" {
    pub fn set_opt_for_clk(value: c_int);
}
