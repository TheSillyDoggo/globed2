use globed_shared::UserEntry;

use crate::{data::*, managers::RoleManager};

#[derive(Clone, Encodable, Decodable, StaticSize, DynamicSize)]
#[dynamic_size(as_static = true)]
pub struct PlayerIconData {
    pub cube: i16,
    pub ship: i16,
    pub ball: i16,
    pub ufo: i16,
    pub wave: i16,
    pub robot: i16,
    pub spider: i16,
    pub swing: i16,
    pub jetpack: i16,
    pub death_effect: i16,
    pub color1: i16,
    pub color2: i16,
    pub glow_color: i16,
}

impl Default for PlayerIconData {
    fn default() -> Self {
        Self {
            cube: 1,
            ship: 1,
            ball: 1,
            ufo: 1,
            wave: 1,
            robot: 1,
            spider: 1,
            swing: 1,
            jetpack: 1,
            death_effect: 1,
            color1: 1,
            color2: 3,
            glow_color: -1, // -1 is glow disabled
        }
    }
}

impl PlayerIconData {
    pub const fn is_valid(&self) -> bool {
        true
    }
}

/* SpecialUserData */

#[derive(Clone, Default, Encodable, Decodable, StaticSize, DynamicSize)]
pub struct SpecialUserData {
    pub roles: Option<FastVec<u8, 16>>,
}

impl SpecialUserData {
    pub fn from_user_entry(user_entry: &UserEntry, role_manager: &RoleManager) -> Self {
        if user_entry.user_roles.is_empty() {
            Self { roles: None }
        } else {
            let roles = role_manager.role_ids_to_int_ids(&user_entry.user_roles);

            Self { roles: Some(roles) }
        }
    }
}

/* PlayerAccountData */

#[derive(Clone, Default, Encodable, Decodable, StaticSize, DynamicSize)]
pub struct PlayerAccountData {
    pub account_id: i32,
    pub user_id: i32,
    pub name: InlineString<MAX_NAME_SIZE>,
    pub icons: PlayerIconData,
    pub special_user_data: SpecialUserData,
}

impl PlayerAccountData {
    pub fn make_room_preview(&self, level_id: LevelId) -> PlayerRoomPreviewAccountData {
        PlayerRoomPreviewAccountData {
            account_id: self.account_id,
            user_id: self.user_id,
            name: self.name.clone(),
            cube: self.icons.cube,
            color1: self.icons.color1,
            color2: self.icons.color2,
            glow_color: self.icons.glow_color,
            level_id,
            special_user_data: self.special_user_data.clone(),
        }
    }

    pub fn make_preview(&self) -> PlayerPreviewAccountData {
        PlayerPreviewAccountData {
            account_id: self.account_id,
            user_id: self.user_id,
            name: self.name.clone(),
            cube: self.icons.cube,
            color1: self.icons.color1,
            color2: self.icons.color2,
            glow_color: self.icons.glow_color,
            special_user_data: self.special_user_data.clone(),
        }
    }
}

/* PlayerPreviewAccountData - like PlayerAccountData but more limited, for the total player list */

#[derive(Clone, Default, Encodable, Decodable, StaticSize, DynamicSize)]
pub struct PlayerPreviewAccountData {
    pub account_id: i32,
    pub user_id: i32,
    pub name: InlineString<MAX_NAME_SIZE>,
    pub cube: i16,
    pub color1: i16,
    pub color2: i16,
    pub glow_color: i16,
    pub special_user_data: SpecialUserData,
}

/* PlayerRoomPreviewAccountData - similar to previous one but for rooms, the only difference is that it includes a level ID */

#[derive(Clone, Default, Encodable, Decodable, StaticSize, DynamicSize)]
pub struct PlayerRoomPreviewAccountData {
    pub account_id: i32,
    pub user_id: i32,
    pub name: InlineString<MAX_NAME_SIZE>,
    pub cube: i16,
    pub color1: i16,
    pub color2: i16,
    pub glow_color: i16,
    pub level_id: LevelId,
    pub special_user_data: SpecialUserData,
}

/* AssociatedPlayerData */

#[derive(Clone, Default, Encodable, Decodable, StaticSize, DynamicSize)]
pub struct AssociatedPlayerData {
    pub account_id: i32,
    pub data: PlayerData,
}

/* AssociatedPlayerMetadata */

#[derive(Clone, Default, Encodable, Decodable, StaticSize, DynamicSize)]
#[dynamic_size(as_static = true)]
pub struct AssociatedPlayerMetadata {
    pub account_id: i32,
    pub data: PlayerMetadata,
}

/* :fire: */

#[derive(Clone, Encodable)]
pub struct BorrowedAssociatedPlayerData<'a> {
    pub account_id: i32,
    pub data: &'a PlayerData,
}

#[derive(Clone, Encodable)]
pub struct BorrowedAssociatedPlayerMetadata<'a> {
    pub account_id: i32,
    pub data: &'a PlayerMetadata,
}
