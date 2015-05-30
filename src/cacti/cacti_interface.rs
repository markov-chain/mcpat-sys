use libc::c_double;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct powerComponents;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct powerDef;

extern "C" {
    pub fn powerComponents_dynamic(this: *mut powerComponents) -> c_double;
    pub fn powerComponents_leakage(this: *mut powerComponents) -> c_double;
    pub fn powerComponents_gate_leakage(this: *mut powerComponents) -> c_double;
    pub fn powerComponents_short_circuit(this: *mut powerComponents) -> c_double;
    pub fn powerComponents_longer_channel_leakage(this: *mut powerComponents) -> c_double;
    pub fn powerComponents_power_gated_leakage(this: *mut powerComponents) -> c_double;
    pub fn powerComponents_power_gated_with_long_channel_leakage(this: *mut powerComponents) -> c_double;
}

extern "C" {
    pub fn powerDef_readOp(this: *mut powerDef) -> *mut powerComponents;
    pub fn powerDef_writeOp(this: *mut powerDef) -> *mut powerComponents;
    pub fn powerDef_searchOp(this: *mut powerDef) -> *mut powerComponents;
}
