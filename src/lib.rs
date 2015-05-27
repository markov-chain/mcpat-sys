#[repr(C)]
pub struct ParseXML;

extern "C" {
    pub fn ParseXML_new() -> *mut ParseXML;
    pub fn ParseXML_free(parsexml: *mut ParseXML);
}

#[cfg(test)]
mod tests {
    #[test]
    fn link() {
        unsafe { ::ParseXML_free(::ParseXML_new()) };
    }
}
