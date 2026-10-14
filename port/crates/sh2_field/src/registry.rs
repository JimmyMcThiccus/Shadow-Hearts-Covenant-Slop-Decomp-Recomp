//! Class registry types shared by the generated `classes_*.rs` tables (menu / shop / Solomon / world map / tailor classes).

/// A method of a recovered class (`jp_addr` = address in the JP FIELD.BIN overlay).
#[derive(Debug, Clone, Copy)]
pub struct Method {
    pub jp_addr: u32,
    pub size: u32,
    pub name: &'static str,
}

/// Static description of a FIELD.BIN class: base class, allocation size (0 when unknown), embedded sub-objects
/// `(byte offset, class)`, vtable stores `(byte offset, vtable symbol)` and methods.
#[derive(Debug, Clone, Copy)]
pub struct ClassInfo {
    pub name: &'static str,
    pub base: &'static str,
    pub size: u32,
    pub ctor_jp: u32,
    pub members: &'static [(u32, &'static str)],
    pub vtables: &'static [(u32, &'static str)],
    pub methods: &'static [Method],
}

pub fn find<'a>(table: &'a [ClassInfo], name: &str) -> Option<&'a ClassInfo> {
    table.iter().find(|c| c.name == name)
}
