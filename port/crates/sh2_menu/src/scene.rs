//! `MenuScene` (a loaded `.MSD` plus the widgets built from it) and the `Menu` scene manager.
//!
//! JP: `MenuScene` 0x00279320..0x0027b330, `Menu` 0x00264de0..0x00265628.
//!
//! * `Menu` owns a list of scenes (linked list in the original, `+0x38`), one *active* scene
//!   (`+0x34`) and the pad state (`+0x48`). `Menu::Run` forwards to the active scene's `Run`.
//! * A scene is loaded with `OrderFile(path, menu)` (async DVD read -> `ReadScene` ->
//!   `MenuDataTable::Convert` -> `MenuScene::Initialize` which indexes the chunks by type into
//!   `scene+0x24..0x54`), then `GetReady()` (virtual) is polled until it returns true.
//! * `SetData(index, widget)` fills a freshly constructed widget from record `index` of the
//!   corresponding table — mirrored by the `build_*` methods.

use crate::cursor::Cursor;
use crate::disc::FileSource;
use crate::msd::{ChunkType, Msd, MsdError};
use crate::widget::Widget;
use crate::window::{dir, MenuRoot, Window};

/// PS2 pad bits as seen by the menu code (`CPad` core +0x6c trigger / +0x70 repeat).
pub mod pad {
    pub const SELECT: u16 = 0x0001;
    pub const START: u16 = 0x0008;
    pub const UP: u16 = 0x0010;
    pub const RIGHT: u16 = 0x0020;
    pub const DOWN: u16 = 0x0040;
    pub const LEFT: u16 = 0x0080;
    pub const L2: u16 = 0x0100;
    pub const R2: u16 = 0x0200;
    pub const L1: u16 = 0x0400;
    pub const R1: u16 = 0x0800;
    pub const TRIANGLE: u16 = 0x1000;
    /// OK / decide in the JP build
    pub const CIRCLE: u16 = 0x2000;
    /// cancel
    pub const CROSS: u16 = 0x4000;
    pub const SQUARE: u16 = 0x8000;

    /// JP: 0x00265530 Menu::GetKey — buttons come from the *trigger* word, d-pad from the *repeat* word.
    pub fn menu_keys(trigger: u16, repeat: u16) -> u16 {
        (trigger & 0xff0f) | (repeat & 0xf0)
    }
}

/// Scene life cycle (`MenuScene+0x23` flags in the original).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum SceneState {
    /// no data yet
    Empty,
    /// file requested (`OrderFile`)
    Loading,
    /// `Initialize` done, waiting for `get_ready`
    Initialised,
    Ready,
}

/// Behaviour hooks a concrete scene (GameOverScene, CmdMenu* in FIELD.BIN, ...) overrides.
pub trait SceneLogic {
    /// JP vtable +0x14 `GetReady` — build windows/places once the data is available.
    fn get_ready(&mut self, scene: &mut Scene, root: &mut MenuRoot) -> bool;
    /// JP +0x1c `Run` — called every frame while active; returns true to be called again this frame.
    fn run(&mut self, scene: &mut Scene, root: &mut MenuRoot, keys: u16) -> bool;
    /// JP +0x20 `Shutdown` / +0x24 `Restore` — sleep/wake when another scene takes over.
    fn shutdown(&mut self, _scene: &mut Scene, _root: &mut MenuRoot) {}
    fn restore(&mut self, _scene: &mut Scene, _root: &mut MenuRoot) {}
    /// JP +0x18 `Release`
    fn release(&mut self, _scene: &mut Scene, _root: &mut MenuRoot) {}
}

#[derive(Debug)]
pub struct Scene {
    pub id: i16,
    pub state: SceneState,
    pub msd: Option<Msd>,
    pub path: String,
    /// cursor shared by the scene (JP +0x18)
    pub cursor: Option<Cursor>,
}

impl Scene {
    pub fn new(id: i16) -> Self {
        Scene { id, state: SceneState::Empty, msd: None, path: String::new(), cursor: None }
    }

    /// JP: 0x002794f0 OrderFile + 0x00279320 ReadScene + 0x00279570 Initialize (synchronous here).
    pub fn load(&mut self, files: &dyn FileSource, path: &str) -> Result<(), SceneError> {
        self.state = SceneState::Loading;
        self.path = path.to_string();
        let data = files.read(path).ok_or_else(|| SceneError::Missing(path.to_string()))?;
        self.msd = Some(Msd::parse(data)?);
        self.state = SceneState::Initialised;
        Ok(())
    }

    pub fn msd(&self) -> &Msd {
        self.msd.as_ref().expect("scene not loaded")
    }

    /// JP: SetData(.., MenuWindow*) — decoration/places are added by the caller.
    pub fn build_window(&self, index: usize) -> Option<Window> {
        self.msd().window(index).map(|r| Window::from_rec(&r))
    }

    /// JP: SetData(.., MenuText*) — text string resolved through the type-1 table.
    pub fn build_text(&self, index: usize) -> Option<Widget> {
        let m = self.msd();
        let r = m.menu_text(index)?;
        let text = m.text(r.text_id as usize).map(|t| t.to_vec()).unwrap_or_default();
        Some(Widget::text_from_rec(&r, text))
    }

    pub fn build_sprite(&self, index: usize, tex: Option<u32>) -> Option<Widget> {
        self.msd().sprite(index).map(|r| Widget::sprite_from_rec(&r, tex))
    }

    pub fn build_polygon(&self, index: usize, tex: Option<u32>) -> Option<Widget> {
        self.msd().polygon(index).map(|r| Widget::polygon_from_rec(&r, tex))
    }

    pub fn build_group(&self, index: usize) -> Option<Widget> {
        self.msd().group(index).map(|r| Widget::group_from_rec(&r))
    }

    pub fn build_cursor(&self, index: usize) -> Option<Cursor> {
        self.msd().cursor(index).map(|r| Cursor::from_rec(&r))
    }

    /// JP: 0x002797d0 FindAttachFile — embedded blob by id.
    pub fn find_attach(&self, id: i32) -> Option<&[u8]> {
        let m = self.msd();
        m.attach_files().into_iter().find(|a| a.id == id).and_then(|a| m.data.get(a.offset as usize..(a.offset + a.size) as usize))
    }

    /// JP: 0x00279650 MoveVertical — handle UP/DOWN (and L2/R2 page skips) for the scene cursor.
    pub fn move_vertical(&mut self, root: &mut MenuRoot, keys: u16, allow_skip: bool) {
        let Some(c) = self.cursor.as_mut() else { return };
        if keys & pad::UP != 0 {
            c.move_cursor(root, dir::UP, None);
        } else if keys & pad::DOWN != 0 {
            c.move_cursor(root, dir::DOWN, None);
        } else if allow_skip {
            let has_marks = c.place.and_then(|p| root.get(p.win)).and_then(|w| w.mark.as_ref()).map(|m| m.show != 0).unwrap_or(false);
            if has_marks {
                if keys & pad::L2 != 0 {
                    c.skip_cursor(root, dir::UP, None);
                } else if keys & pad::R2 != 0 {
                    c.skip_cursor(root, dir::DOWN, None);
                }
            }
        }
    }

    pub fn count(&self, kind: ChunkType) -> usize {
        self.msd.as_ref().map(|m| m.count(kind)).unwrap_or(0)
    }
}

#[derive(Debug, thiserror::Error)]
pub enum SceneError {
    #[error("file not found: {0}")]
    Missing(String),
    #[error(transparent)]
    Msd(#[from] MsdError),
}

struct Slot {
    scene: Scene,
    logic: Box<dyn SceneLogic>,
}

/// JP `Menu` (CPolObj subclass registered with `CPoller` priority 0x80).
#[derive(Default)]
pub struct Menu {
    slots: Vec<Slot>,
    /// index of the active scene (JP +0x34)
    active: Option<usize>,
    /// JP +0x48 key word
    pub keys: u16,
}

impl Menu {
    pub fn new() -> Self {
        Self::default()
    }

    /// JP: 0x002651c0 AddScene
    pub fn add_scene(&mut self, scene: Scene, logic: Box<dyn SceneLogic>) {
        self.slots.push(Slot { scene, logic });
    }

    /// JP: 0x00265360 GetScene
    pub fn scene(&mut self, id: i16) -> Option<&mut Scene> {
        self.slots.iter_mut().map(|s| &mut s.scene).find(|s| s.id == id)
    }

    /// JP: 0x002654c0 Active — make a scene current and run it once.
    pub fn activate(&mut self, id: i16, root: &mut MenuRoot) -> bool {
        self.active = self.slots.iter().position(|s| s.scene.id == id);
        if self.active.is_some() {
            self.run(root);
            true
        } else {
            false
        }
    }

    /// JP: 0x00264fa0 Run
    pub fn run(&mut self, root: &mut MenuRoot) {
        let keys = self.keys;
        let Some(i) = self.active else { return };
        let slot = &mut self.slots[i];
        if slot.scene.state == SceneState::Initialised && slot.logic.get_ready(&mut slot.scene, root) {
            slot.scene.state = SceneState::Ready;
        }
        if slot.scene.state == SceneState::Ready {
            while slot.logic.run(&mut slot.scene, root, keys) {}
        }
    }

    /// JP: 0x00265020 Shutdown / 0x002650a0 Restore — put every *other* scene to sleep / wake it.
    pub fn shutdown_others(&mut self, root: &mut MenuRoot) {
        for (i, s) in self.slots.iter_mut().enumerate() {
            if Some(i) != self.active {
                s.logic.shutdown(&mut s.scene, root);
            }
        }
    }
    pub fn restore_others(&mut self, root: &mut MenuRoot) {
        for (i, s) in self.slots.iter_mut().enumerate() {
            if Some(i) != self.active {
                s.logic.restore(&mut s.scene, root);
            }
        }
    }

    /// JP: 0x002653f0 DestroyScene
    pub fn destroy_scene(&mut self, id: i16, root: &mut MenuRoot) {
        if let Some(i) = self.slots.iter().position(|s| s.scene.id == id) {
            let mut s = self.slots.remove(i);
            s.logic.release(&mut s.scene, root);
            self.active = match self.active {
                Some(a) if a == i => None,
                Some(a) if a > i => Some(a - 1),
                o => o,
            };
        }
    }

    /// JP: 0x00265120 DestroyList
    pub fn destroy_all(&mut self, root: &mut MenuRoot) {
        for mut s in self.slots.drain(..) {
            s.logic.release(&mut s.scene, root);
        }
        self.active = None;
    }

    /// JP: 0x00265530 GetKey — poll the pad into `keys`.
    pub fn update_keys(&mut self, trigger: u16, repeat: u16) {
        self.keys = pad::menu_keys(trigger, repeat);
    }
}
