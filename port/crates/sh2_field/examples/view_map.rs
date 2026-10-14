//! Renderer-fidelity harness: the stand-alone viewer of `sh2_app` built from this crate only (so it compiles while other
//! workspace members are in flux).  `cargo run -p sh2_field --example view_map -- --view-map AP_00_U --screenshot out.png`.
#[path = "../../sh2_app/src/viewer.rs"]
mod viewer;

fn main() {
    let opts = viewer::ViewerOptions::from_args(std::env::args().skip(1)).expect("pass --view-map NAME or --view-model");
    viewer::run(opts);
}
