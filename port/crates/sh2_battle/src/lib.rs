//! sh2_battle — battle system of Shadow Hearts: Covenant (section H in docs/OUTLINE.md).
//!
//! * [`rules`]   – pure battle rules (stats, turn order, damage, rewards, levelling)
//! * [`structs`] – memory layouts of `CBattle`, the 0x4f0 byte battle character, parameter records
//! * [`data`]    – parsers for `COMMON/SSHDAT.JPN` (battle tables) and monster sets
//! * [`pkb_compat`] – aliases over the canonical `sh2_core::fileio` `PKFINFO.TBL` + `*.PKB` reader
//! * [`flow`]    – the `CBattle` phase state machine and the command menu state machine
//!
//! JP addresses in comments refer to `BATTLE.BIN` (load address 0x00430a00) unless noted.

pub mod actions;
pub mod area;
pub mod attribute_glow;
pub mod ai;
pub mod bridge;
pub mod camera;
pub mod choreo;
pub mod combo_form;
pub mod data;
pub mod death_glow;
pub mod down_smoke;
pub mod devdrive;
pub mod effects_bridge;
pub mod break_effects;
pub mod bullets;
pub mod flow;
pub mod formation;
pub mod headless;
pub mod host;
pub mod hit_impact;
pub mod hud;
pub mod hud_hits;
pub mod hud_result;
pub mod hud_target;
pub mod hud_turn;
pub mod menu_data;
pub mod models;
pub mod pkb_compat;
pub mod plugin;
pub mod ring;
pub mod rules;
pub mod shortcut;
pub mod stage;
pub mod structs;
pub mod tarot;
pub mod ui;
pub mod wall_involve;
pub mod warp;
