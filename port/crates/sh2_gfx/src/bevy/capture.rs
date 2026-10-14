//! Screenshot-to-PNG helper so the viewer can be verified without a human.

use ::bevy::app::AppExit;
use ::bevy::prelude::*;
use ::bevy::render::view::screenshot::{save_to_disk, Screenshot};
use std::path::PathBuf;

/// Insert this resource to capture the primary window after `after_frames` frames and (optionally) exit.
#[derive(Resource, Clone, Debug)]
pub struct ScreenshotJob {
    pub path: PathBuf,
    pub after_frames: u32,
    pub exit_when_done: bool,
}

#[derive(Default)]
pub struct JobState {
    frame: u32,
    requested_at: Option<u32>,
}

pub fn screenshot_system(job: Option<Res<ScreenshotJob>>, mut st: Local<JobState>, mut commands: Commands, mut exit: MessageWriter<AppExit>) {
    let Some(job) = job else { return };
    st.frame += 1;
    if st.requested_at.is_none() && st.frame >= job.after_frames {
        if let Some(dir) = job.path.parent() {
            let _ = std::fs::create_dir_all(dir);
        }
        let _ = std::fs::remove_file(&job.path);
        commands.spawn(Screenshot::primary_window()).observe(save_to_disk(job.path.clone()));
        st.requested_at = Some(st.frame);
        info!("screenshot requested -> {}", job.path.display());
    } else if let Some(at) = st.requested_at {
        let written = std::fs::metadata(&job.path).map(|m| m.len() > 0).unwrap_or(false);
        if job.exit_when_done && (written && st.frame > at + 2 || st.frame > at + 300) {
            if !written {
                error!("screenshot was not written");
            }
            exit.write(AppExit::Success);
        }
    }
}

pub struct ScreenshotPlugin;
impl Plugin for ScreenshotPlugin {
    fn build(&self, app: &mut App) {
        app.add_systems(Update, screenshot_system);
    }
}
