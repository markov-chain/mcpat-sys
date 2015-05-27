use libc::c_char;

#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct ParseXML;

extern "C" {
    pub fn ParseXML_new() -> *mut ParseXML;
    pub fn ParseXML_free(parsexml: *mut ParseXML);
    pub fn ParseXML_parse(parsexml: *mut ParseXML, filename: *mut c_char);
}

#[cfg(test)]
mod tests {
    macro_rules! ok(
        ($result:expr) => ($result.unwrap());
    );

    macro_rules! to_c_str(
        ($string:expr) => (ok!(::std::ffi::CString::new($string)));
    );

    #[test]
    fn parse() {
        let filename = to_c_str!("build/source/ProcessorDescriptionFiles/Xeon.xml");

        unsafe {
            let parsexml = ::ParseXML_new();
            ::ParseXML_parse(parsexml, filename.as_ptr() as *mut _);
            ::ParseXML_free(parsexml);
        }
    }
}
