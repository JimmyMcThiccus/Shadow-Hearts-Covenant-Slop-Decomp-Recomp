//! sh2_menu — see sh2-decomp/docs/OUTLINE.md for the subsystem this crate ports.
//!
//! Section F: menu widget toolkit (`Menu*`), save system (`SaveData*`), title/opening and game over.
pub mod bevy_ui;
pub mod btlsave;
pub mod cmnframe;
pub mod cursor;
pub mod dataaccess;
pub mod disc;
pub mod gamefont;
pub mod gameover;
pub mod gfx;
pub mod hifont;
pub mod memcard;
pub mod message;
pub mod movie;
pub mod msd;
pub mod plugin;
pub mod ringcustom;
pub mod save;
pub mod session;
pub mod story_flags;
pub mod sjis;
mod sjis_table;
pub mod scene;
pub mod score;
pub mod storage;
pub mod title;
pub mod title_retail_plugin;
pub mod vibration;
pub mod widget;
pub mod window;
