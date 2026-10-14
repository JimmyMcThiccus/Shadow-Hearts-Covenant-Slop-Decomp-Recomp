//! The title's **Options** screen on the retail disc: `OptionMenu` (OPENING.BIN 0x468e80, created with first scene 0x10) is the `OPTION.MSD` scene -- the same
//! one the in-game Option page ([`crate::cmd_option::OptionPage`]) is built from -- listing four items (vibration / sound / brightness / subtitles) over the
//! title's mist background.  It runs as a field screen so it can use the page, the title log, the note window and the button report of the command menu;
//! the title (`sh2_menu::title_retail_plugin`) delegates to it through [`sh2_menu::title_retail_plugin::DataScreenLink`].
//!
//! **Approximated**: the original builds its own `MenuScene` graph (`PictureScene` / `HelpScene` / `PanelScene`); the placement of the title picture, the help line
//! and the hints is the in-game page's, not measured against the retail title.

use sh2_menu::gfx::{MenuGfx, TextureId};

use crate::cmd_option::OptionPage;
use crate::cmd_page::{draw_buttons, CmdScenes, Env, Flow, Note, Page, TitleLog};
use crate::cmd_ui::{blit, SCREEN_H, SCREEN_W};
use crate::fscreen::{FieldScreen, ScreenFlow, ScreenIo};
use sh2_menu::gfx::Rgba;

use std::sync::Arc;

pub struct TitleOptionsScreen {
    sc: Arc<CmdScenes>,
    page: OptionPage,
    log: TitleLog,
    note: Note,
    mist: Option<TextureId>,
    cover: f32,
    closing: bool,
}

impl TitleOptionsScreen {
    pub fn new(env: &mut Env) -> Option<Self> {
        use sh2_menu::disc::FileSource;
        let sc = env.scenes()?;
        let page = OptionPage::new_title(env)?;
        let log = TitleLog::new(&sc, page.title(), page.title_image());
        let note = Note::new(&sc);
        // the title's mist (`OPENING/OPENING.DAT` #1, 640 x 448)
        let mist = env.assets.disc.as_ref().and_then(|d| d.read("OPENING/OPENING.DAT")).and_then(|b| {
            let off = u32::from_le_bytes(b.get(12 + 8..16 + 8)?.try_into().ok()?) as usize;
            let img = sh2_gfx::texture::decode_menu_texture(&b, off).ok()?;
            env.reg.add(&img)
        });
        Some(TitleOptionsScreen { sc, page, log, note, mist, cover: 128.0, closing: false })
    }
}

impl FieldScreen for TitleOptionsScreen {
    fn name(&self) -> &'static str {
        "titleOptions"
    }

    fn tick(&mut self, env: &mut Env, keys: u16, _press: u16, _io: &mut ScreenIo) -> ScreenFlow {
        if self.closing {
            self.cover = (self.cover + 16.0).min(128.0);
            return if self.cover >= 128.0 { ScreenFlow::Done } else { ScreenFlow::Stay };
        }
        self.cover = (self.cover - 16.0).max(0.0);
        self.log.slide.tick(1000.0 / 60.0);
        self.note.slide.tick(1000.0 / 60.0);
        if matches!(self.page.tick(env, keys), Flow::Back | Flow::Close) {
            self.closing = true;
        }
        self.note.text = self.page.note();
        ScreenFlow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        blit(g, self.mist, 0.0, 0.0, SCREEN_W, SCREEN_H, (0.0, 0.0, 640.0, 448.0), Rgba::new(0x80, 0x80, 0x80, 0x80));
        // the mist is pale: dim it so the white menu text reads (the title's Options scene draws over a darkened backdrop)
        crate::cmd_ui::fill(g, 0.0, 0.0, SCREEN_W, SCREEN_H, Rgba::new(0, 0, 0, 0x34));
        self.log.draw(g, &self.sc);
        self.page.draw(g);
        self.note.draw(g, &self.sc);
        draw_buttons(g, &self.sc.cmn, &self.page.buttons(), SCREEN_H - 18.0, 0x80);
        if self.cover > 0.0 {
            crate::cmd_ui::fill(g, 0.0, 0.0, SCREEN_W, SCREEN_H, Rgba::new(0, 0, 0, self.cover as u8));
        }
    }

    fn state(&self) -> String {
        "options".into()
    }
}
