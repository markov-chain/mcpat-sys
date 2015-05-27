#[repr(C)]
pub struct ParseXML;

extern "C" {
    pub fn new_ParseXML() -> *mut ParseXML;
    pub fn delete_ParseXML(parsexml: *mut ParseXML);
}

#[cfg(test)]
mod tests {
    #[test]
    fn link() {
        unsafe { ::delete_ParseXML(::new_ParseXML()) };
    }
}
