//! sh2_field — FIELD.BIN overlay (section G): field exploration, world map, shops, Solomon, in-game menus.
//! See sh2-decomp/docs/OUTLINE.md and sh2-decomp/notes/G/.
//!
//! Modules:
//! * [`pkb_compat`] / [`mps`] — PKFINFO.TBL adapter over `sh2_core::fileio` (section A) and the MPS/SDB map-package parser.
//! * [`floor`], [`event`], [`camera`] — `CFloorMan`, `CFieldEvent`, `CFieldCamera` + CAMERA table evaluation.
//! * [`movement`] — pad->heading (`MakeMoveControl`), slope slow-down and wall-sliding floor collision.
//! * [`field`], [`socket`] — `CField` state/logic and `CFieldSocket` phases / faders.
//! * [`cmd`], [`registry`], `classes_*` — in-game menu pages and generated class tables (menu, shop, Solomon, world map, tailor).
//! * [`overlay_data`] — reader for the static message/data tables inside an overlay image.
//! * [`fld_ops`] — field script command table.
//! * [`compat`] — thin `[f32; 3]` adapters over `sh2_formats::math` (section C) plus angle helpers.

pub mod actors;
pub mod bevy;
pub mod autopilot;
pub mod camera;
pub mod classes_cmd;
pub mod classes_shop;
pub mod classes_solomon;
pub mod classes_tailor;
pub mod classes_world;
pub mod cmd;
pub mod cmd_common;
pub mod cmd_equip;
pub mod cmd_crest;
pub mod cmd_data;
pub mod data_screen;
pub mod title_options;
pub mod cmd_form;
pub mod cmd_item;
pub mod cmd_magic;
pub mod cmd_misc;
pub mod cmd_option;
pub mod cmd_status;
pub mod cmd_page;
pub mod cmd_ring;
pub mod cmd_pages;
pub mod cmd_top;
pub mod cmd_ui;
pub mod cmd_view;
pub mod compat;
pub mod cutscene;
pub mod cutscene_plugin;
pub mod event;
pub mod field;
pub mod host;
pub mod fld_ops;
pub mod fscreen;
pub mod floor;
pub mod menu_overlay;
pub mod movement;
pub mod mps;
pub mod navimap;
pub mod navimap_plugin;
pub mod navimap_render;
pub mod overlay_data;
pub mod overlay_data_syms;
pub mod pkb_compat;
pub mod plugin;
pub mod points;
pub mod registry;
pub mod retail;
pub mod screens_dev;
pub mod script_actors;
pub mod shop;
pub mod solomon;
pub mod script_ui;
pub mod sim;
pub mod socket;
pub mod tailor;
pub mod worldmap;
pub mod worldmap_plugin;
