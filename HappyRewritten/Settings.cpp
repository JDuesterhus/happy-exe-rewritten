#include "Settings.h"

CSettings Settings;


void CSettings::LoadConfig(char* path) {
	CIniReader iniReader(path);
	//std::cout << "LOADING 'default.ini'" << std::endl;

		//[ESP]
	ESP.Glow =									iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow"),							ESP.Glow);
	ESP.Glow_Enemy =							iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_enemy"),					ESP.Glow_Enemy);
	ESP.Glow_Ally =								iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_ally"),					ESP.Glow_Ally);
	ESP.Glow_Item =								iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item"),					ESP.Glow_Item);
	ESP.Glow_Highlight_God =					iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_highlight_god"),			ESP.Glow_Highlight_God);
	ESP.Glow_Highlight_Scoped =					iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_highlight_scoped"),		ESP.Glow_Highlight_Scoped);
	ESP.Glow_Highlight_Flashed =				iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_highlight_flashed"),		ESP.Glow_Highlight_Flashed);
	ESP.Glow_Highlight_Defuser =				iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_highlight_defuser"),		ESP.Glow_Highlight_Defuser);
	ESP.Glow_Highlight_Planter =				iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_highlight_planter"),		ESP.Glow_Highlight_Planter);
	ESP.Glow_Item_Pistol =						iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item_pistol"),				ESP.Glow_Item_Pistol);
	ESP.Glow_Item_SMG =							iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item_smg"),				ESP.Glow_Item_SMG);
	ESP.Glow_Item_Shotgun =						iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item_shotgun"),			ESP.Glow_Item_Shotgun);
	ESP.Glow_Item_Rifle =						iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item_rifle"),				ESP.Glow_Item_Rifle);
	ESP.Glow_Item_Sniper =						iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item_sniper"),				ESP.Glow_Item_Sniper);
	ESP.Glow_Item_Grenade =						iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item_grenade"),			ESP.Glow_Item_Grenade);
	ESP.Glow_Item_Bomb =						iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item_bomb"),				ESP.Glow_Item_Bomb);
	ESP.Glow_Item_Other =						iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("glow_item_other"),				ESP.Glow_Item_Other);
	ESP.Glow_Custom_Color =						iniReader.ReadInteger	(XorStr("ESP"),			XorStr("glow_custom_color"),			ESP.Glow_Custom_Color);
	ESP.Glow_Style =							iniReader.ReadInteger	(XorStr("ESP"),			XorStr("glow_style"),					ESP.Glow_Style);
	ESP.Glow_Alpha =							iniReader.ReadFloat		(XorStr("ESP"),			XorStr("glow_alpha"),					ESP.Glow_Alpha);
	ESP.Chams =									iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams"),						ESP.Chams);
	ESP.Chams_Enemy =							iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams_enemy"),					ESP.Chams_Enemy);
	ESP.Chams_Ally =							iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams_ally"),					ESP.Chams_Ally);
	ESP.Chams_Viewmodel =						iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams_viewmodel"),				ESP.Chams_Viewmodel);
	ESP.Chams_Highlight_God =					iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams_highlight_god"),			ESP.Chams_Highlight_God);
	ESP.Chams_Highlight_Scoped =				iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams_highlight_scoped"),		ESP.Chams_Highlight_Scoped);
	ESP.Chams_Highlight_Flashed =				iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams_highlight_flashed"),		ESP.Chams_Highlight_Flashed);
	ESP.Chams_Highlight_Defuser =				iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams_highlight_defuser"),		ESP.Chams_Highlight_Defuser);
	ESP.Chams_Highlight_Planter =				iniReader.ReadBoolean	(XorStr("ESP"),			XorStr("chams_highlight_planter"),		ESP.Chams_Highlight_Planter);
	ESP.Chams_Custom_Color =					iniReader.ReadInteger	(XorStr("ESP"),			XorStr("chams_custom_color"),			ESP.Chams_Custom_Color);
	ESP.Chams_Alpha =							iniReader.ReadFloat		(XorStr("ESP"),			XorStr("chams_alpha"),					ESP.Chams_Alpha);
	//[Aimbot]
	Aimbot.Aimbot =								iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("aimbot"),						Aimbot.Aimbot);
	Aimbot.Aimbot_Hotkey =						iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("aimbot_hotkey"),				Aimbot.Aimbot_Hotkey);
	Aimbot.Aimbot_Bone =						iniReader.ReadInteger	(XorStr("Aimbot"),		XorStr("aimbot_bone"),					Aimbot.Aimbot_Bone);
	Aimbot.Aimbot_Bone2 =						iniReader.ReadInteger	(XorStr("Aimbot"),		XorStr("aimbot_bone2"),					Aimbot.Aimbot_Bone2);
	Aimbot.Aimbot_Bone2_AfterShots =			iniReader.ReadInteger	(XorStr("Aimbot"),		XorStr("aimbot_bone2_aftershots"),		Aimbot.Aimbot_Bone2_AfterShots);
	Aimbot.Aimbot_Bone2_OnHealth =				iniReader.ReadInteger	(XorStr("Aimbot"),		XorStr("aimbot_bone2_onhealth"),		Aimbot.Aimbot_Bone2_OnHealth);
	Aimbot.Aimbot_RCS =							iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("aimbot_rcs"),					Aimbot.Aimbot_RCS);
	Aimbot.Aimbot_FOV =							iniReader.ReadFloat		(XorStr("Aimbot"),		XorStr("aimbot_fov"),					Aimbot.Aimbot_FOV);
	Aimbot.Aimbot_Delay =						iniReader.ReadInteger	(XorStr("Aimbot"),		XorStr("aimbot_delay"),					Aimbot.Aimbot_Delay);
	Aimbot.Aimbot_Delay_Kill =					iniReader.ReadInteger	(XorStr("Aimbot"),		XorStr("aimbot_delay_kill"),			Aimbot.Aimbot_Delay_Kill);
	Aimbot.Aimbot_Smooth_Pitch =				iniReader.ReadFloat		(XorStr("Aimbot"),		XorStr("aimbot_smooth_pitch"),			Aimbot.Aimbot_Smooth_Pitch);
	Aimbot.Aimbot_Smooth_Yaw =					iniReader.ReadFloat		(XorStr("Aimbot"),		XorStr("aimbot_smooth_yaw"),			Aimbot.Aimbot_Smooth_Yaw);
	Aimbot.Aimbot_Ignore_God =					iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("aimbot_ignore_god"),			Aimbot.Aimbot_Ignore_God);
	Aimbot.Aimbot_Ignore_Ally =					iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("aimbot_ignore_ally"),			Aimbot.Aimbot_Ignore_Ally);
	Aimbot.Aimbot_Ignore_Jump =					iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("aimbot_ignore_jump"),			Aimbot.Aimbot_Ignore_Jump);
	Aimbot.Aimbot_Check_Flash =					iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("aimbot_check_flash"),			Aimbot.Aimbot_Check_Flash);
	Aimbot.Aimbot_Check_Visible =				iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("aimbot_check_visible"),			Aimbot.Aimbot_Check_Visible);
	Aimbot.RCS =								iniReader.ReadBoolean	(XorStr("Aimbot"),		XorStr("rcs"),							Aimbot.RCS); //still unused x
	Aimbot.RCS_Pitch =							iniReader.ReadFloat		(XorStr("Aimbot"),		XorStr("rcs_pitch"),					Aimbot.RCS_Pitch);
	Aimbot.RCS_Yaw =							iniReader.ReadFloat		(XorStr("Aimbot"),		XorStr("rcs_yaw"),						Aimbot.RCS_Yaw);
	Aimbot.RCS_AfterShots =						iniReader.ReadInteger	(XorStr("Aimbot"),		XorStr("rcs_aftershots"),				Aimbot.RCS_AfterShots);
	//[Triggerbot]
	Triggerbot.Triggerbot =						iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot"),					Triggerbot.Triggerbot);
	Triggerbot.Triggerbot_Hotkey =				iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot_hotkey"),			Triggerbot.Triggerbot_Hotkey);
	Triggerbot.Triggerbot_Burst =				iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot_burst"),				Triggerbot.Triggerbot_Burst);
	Triggerbot.Triggerbot_Burst_Bullets =		iniReader.ReadInteger	(XorStr("Triggerbot"),	XorStr("triggerbot_burst_bullets"),		Triggerbot.Triggerbot_Burst_Bullets);
	Triggerbot.Triggerbot_Dash =				iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot_dash"),				Triggerbot.Triggerbot_Dash);
	Triggerbot.Triggerbot_Ignore_God =			iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot_ignore_god"),		Triggerbot.Triggerbot_Ignore_God);
	Triggerbot.Triggerbot_Ignore_Ally =			iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot_ignore_ally"),		Triggerbot.Triggerbot_Ignore_Ally);
	Triggerbot.Triggerbot_Check_Flash =			iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot_check_flash"),		Triggerbot.Triggerbot_Check_Flash);
	Triggerbot.Triggerbot_Check_Zoom =			iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot_check_zoom"),		Triggerbot.Triggerbot_Check_Zoom);
	Triggerbot.Triggerbot_Delay_Random =		iniReader.ReadBoolean	(XorStr("Triggerbot"),	XorStr("triggerbot_delay_random"),		Triggerbot.Triggerbot_Delay_Random);
	Triggerbot.Triggerbot_Delay_Random_From =	iniReader.ReadInteger	(XorStr("Triggerbot"),	XorStr("triggerbot_delay_random_from"),	Triggerbot.Triggerbot_Delay_Random_From);
	Triggerbot.Triggerbot_Delay_Random_To =		iniReader.ReadInteger	(XorStr("Triggerbot"),	XorStr("triggerbot_delay_random_to"),	Triggerbot.Triggerbot_Delay_Random_To);
	Triggerbot.Triggerbot_Delay_First =			iniReader.ReadInteger	(XorStr("Triggerbot"),	XorStr("triggerbot_delay_first"),		Triggerbot.Triggerbot_Delay_First);
	Triggerbot.Triggerbot_Delay_Burst =			iniReader.ReadInteger	(XorStr("Triggerbot"),	XorStr("triggerbot_delay_burst"),		Triggerbot.Triggerbot_Delay_Burst);
	Triggerbot.Triggerbot_Delay_Last =			iniReader.ReadInteger	(XorStr("Triggerbot"),	XorStr("triggerbot_delay_last"),		Triggerbot.Triggerbot_Delay_Last);
	//[Misc]
	Misc.Autopistol =							iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("autopistol"),					Misc.Autopistol);
	Misc.Radar =								iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("radar"),						Misc.Radar);
	Misc.Bunnyhop =								iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("bunnyhop"),						Misc.Bunnyhop);
	Misc.Bunnyhop_Crouch =						iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("bunnyhop_crouch"),				Misc.Bunnyhop_Crouch);
	Misc.Autostrafe =							iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("autostrafe"),					Misc.Autostrafe);
	Misc.Spammer =								iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("spammer"),						Misc.Spammer);
	Misc.Spammer_Random =						iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("spammer_random"),				Misc.Spammer_Random);
	Misc.Spammer_Delay =						iniReader.ReadInteger	(XorStr("Misc"),		XorStr("spammer_delay"),				Misc.Spammer_Delay);
	Misc.Spammer_Path =							iniReader.ReadString	(XorStr("Misc"),		XorStr("spammer_path"),					""); //fix later
	Misc.Remove_Hands =							iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("remove_hands"),					Misc.Remove_Hands);
	Misc.Remove_Ragdoll =						iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("remove_ragdoll"),				Misc.Remove_Ragdoll);
	Misc.Remove_Fog =							iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("remove_fog"),					Misc.Remove_Fog);
	Misc.Remove_Smoke =							iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("remove_smoke"),					Misc.Remove_Smoke);
	Misc.Reduce_Flash =							iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("reduce_flash"),					Misc.Reduce_Flash);
	Misc.Reduce_Flash_Alpha =					iniReader.ReadFloat		(XorStr("Misc"),		XorStr("reduce_flash_alpha"),			Misc.Reduce_Flash_Alpha);
	Misc.Overwrite_FOV =						iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("overwrite_fov"),				Misc.Overwrite_FOV);
	Misc.Overwrite_FOV_Custom =					iniReader.ReadInteger	(XorStr("Misc"),		XorStr("overwrite_fov_custom"),			Misc.Overwrite_FOV_Custom);
	Misc.Nightmode =							iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("nightmode"),					Misc.Nightmode);
	Misc.Nightmode_Alpha =						iniReader.ReadFloat		(XorStr("Misc"),		XorStr("nightmode_alpha"),				Misc.Nightmode_Alpha);
	Misc.Fakelag =								iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("fakelag"),						Misc.Fakelag);
	Misc.Fakelag_Hotkey =						iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("fakelag_hotkey"),				Misc.Fakelag_Hotkey);
	Misc.Fakelag_Ticks =						iniReader.ReadInteger	(XorStr("Misc"),		XorStr("fakelag_ticks"),				Misc.Fakelag_Ticks);
	Misc.Bomb_Timer =							iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("bomb_timer"),					Misc.Bomb_Timer);
	Misc.Swap_Knife_Hand =						iniReader.ReadBoolean	(XorStr("Misc"),		XorStr("swap_knife_hand"),				Misc.Swap_Knife_Hand);
	Misc.Weapon_Config =						iniReader.ReadInteger	(XorStr("Misc"),		XorStr("weapon_config"),				Misc.Weapon_Config);
	Misc.Offset_URL =							iniReader.ReadString	(XorStr("Misc"),		XorStr("offset_url"),					""); //fix later
	Misc.Window_Transparency =					iniReader.ReadInteger	(XorStr("Misc"),		XorStr("window_transparency"),			Misc.Window_Transparency);
	//[Hotkey]
	Hotkey.Toggle_Glow =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_glow"),					Hotkey.Toggle_Glow);
	Hotkey.Toggle_Chams =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_cham"),					Hotkey.Toggle_Chams);
	Hotkey.Toggle_Aimbot =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_aimbot"),				Hotkey.Toggle_Aimbot);
	Hotkey.Toggle_Triggerbot =					iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_triggerbot"),			Hotkey.Toggle_Triggerbot);
	Hotkey.Toggle_Autopistol =					iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_autopistol"),			Hotkey.Toggle_Autopistol);
	Hotkey.Toggle_Radar =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_radar"),					Hotkey.Toggle_Radar);
	Hotkey.Toggle_Bunnyhop =					iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_bunnyhop"),				Hotkey.Toggle_Bunnyhop);
	Hotkey.Toggle_Autostrafe =					iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_autostrafe"),			Hotkey.Toggle_Autostrafe);
	Hotkey.Toggle_Spammer =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_spammer"),				Hotkey.Toggle_Spammer);
	Hotkey.Toggle_Remove_Hands =				iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_remove_hands"),			Hotkey.Toggle_Remove_Hands);
	Hotkey.Toggle_Remove_Ragdoll =				iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_remove_ragdoll"),		Hotkey.Toggle_Remove_Ragdoll);
	Hotkey.Toggle_Remove_Fog =					iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_remove_fog"),			Hotkey.Toggle_Remove_Fog);
	Hotkey.Toggle_Remove_Smoke =				iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_remove_smoke"),			Hotkey.Toggle_Remove_Smoke);
	Hotkey.Toggle_Reduce_Flash =				iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_reduce_flash"),			Hotkey.Toggle_Reduce_Flash);
	Hotkey.Toggle_Overwrite_FOV =				iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_overwrite_fov"),			Hotkey.Toggle_Overwrite_FOV);
	Hotkey.Toggle_Nightmode =					iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_nightmode"),				Hotkey.Toggle_Nightmode);
	Hotkey.Toggle_Fakelag =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("toggle_fakelag"),				Hotkey.Toggle_Fakelag);
	Hotkey.Hold_Aimbot =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("hold_aimbot"),					Hotkey.Hold_Aimbot);
	Hotkey.Hold_TriggerBot =					iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("hold_triggerbot"),				Hotkey.Hold_TriggerBot);
	Hotkey.Hold_Bunnyhop =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("hold_bunnyhop"),				Hotkey.Hold_Bunnyhop);
	Hotkey.Hold_Fakelag =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("hold_fakelag"),					Hotkey.Hold_Fakelag);
	Hotkey.Bind_2HP =							iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("bind_2hp"),						Hotkey.Bind_2HP);
	Hotkey.Bind_180 =							iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("bind_180"),						Hotkey.Bind_180);
	Hotkey.Bind_360 =							iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("bind_360"),						Hotkey.Bind_360);
	Hotkey.Reload_Config =						iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("reload_config"),				Hotkey.Reload_Config);
	Hotkey.Panic_Exit =							iniReader.ReadInteger	(XorStr("Hotkey"),		XorStr("panic_exit"),					Hotkey.Panic_Exit);
	//[Color]
	Color.Glow_Enemy_R =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_enemy_r"),					Color.Glow_Enemy_R);
	Color.Glow_Enemy_G =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_enemy_g"),					Color.Glow_Enemy_G);
	Color.Glow_Enemy_B =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_enemy_b"),					Color.Glow_Enemy_B);
	Color.Glow_Ally_R =							iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_ally_r"),					Color.Glow_Ally_R);
	Color.Glow_Ally_G =							iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_ally_g"),					Color.Glow_Ally_G);
	Color.Glow_Ally_B =							iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_ally_b"),					Color.Glow_Ally_B);
	Color.Glow_Terrorist_R =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_terrorist_r"),				Color.Glow_Terrorist_R);
	Color.Glow_Terrorist_G =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_terrorist_g"),				Color.Glow_Terrorist_G);
	Color.Glow_Terrorist_B =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_terrorist_b"),				Color.Glow_Terrorist_B);
	Color.Glow_CounterTerrorist_R =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_counterterrorist_r"),		Color.Glow_CounterTerrorist_R);
	Color.Glow_CounterTerrorist_G =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_counterterrorist_g"),		Color.Glow_CounterTerrorist_G);
	Color.Glow_CounterTerrorist_B =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_counterterrorist_b"),		Color.Glow_CounterTerrorist_B);
	Color.Glow_Highlight_God_R =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_god_r"),			Color.Glow_Highlight_God_R);
	Color.Glow_Highlight_God_G =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_god_g"),			Color.Glow_Highlight_God_G);
	Color.Glow_Highlight_God_B =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_god_b"),			Color.Glow_Highlight_God_B);
	Color.Glow_Highlight_Scoped_R =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_scoped_r"),		Color.Glow_Highlight_Scoped_R);
	Color.Glow_Highlight_Scoped_G =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_scoped_g"),		Color.Glow_Highlight_Scoped_G);
	Color.Glow_Highlight_Scoped_B =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_scoped_b"),		Color.Glow_Highlight_Scoped_B);
	Color.Glow_Highlight_Flashed_R =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_flashed_r"),		Color.Glow_Highlight_Flashed_R);
	Color.Glow_Highlight_Flashed_G =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_flashed_g"),		Color.Glow_Highlight_Flashed_G);
	Color.Glow_Highlight_Flashed_B =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_flashed_b"),		Color.Glow_Highlight_Flashed_B);
	Color.Glow_Highlight_Defuser_R =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_defuser_r"),		Color.Glow_Highlight_Defuser_R);
	Color.Glow_Highlight_Defuser_G =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_defuser_g"),		Color.Glow_Highlight_Defuser_G);
	Color.Glow_Highlight_Defuser_B =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_defuser_b"),		Color.Glow_Highlight_Defuser_B);
	Color.Glow_Highlight_Planter_R =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_planter_r"),		Color.Glow_Highlight_Planter_R);
	Color.Glow_Highlight_Planter_G =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_planter_g"),		Color.Glow_Highlight_Planter_G);
	Color.Glow_Highlight_Planter_B =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_highlight_planter_b"),		Color.Glow_Highlight_Planter_B);
	Color.Glow_Item_Weapon_R =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_weapon_r"),			Color.Glow_Item_Weapon_R);
	Color.Glow_Item_Weapon_G =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_weapon_g"),			Color.Glow_Item_Weapon_G);
	Color.Glow_Item_Weapon_B =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_weapon_b"),			Color.Glow_Item_Weapon_B);
	Color.Glow_Item_Grenade_R =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_grenade_r"),			Color.Glow_Item_Grenade_R);
	Color.Glow_Item_Grenade_G =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_grenade_g"),			Color.Glow_Item_Grenade_G);
	Color.Glow_Item_Grenade_B =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_grenade_b"),			Color.Glow_Item_Grenade_B);
	Color.Glow_Item_Bomb_R =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_bomb_r"),				Color.Glow_Item_Bomb_R);
	Color.Glow_Item_Bomb_G =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_bomb_g"),				Color.Glow_Item_Bomb_G);
	Color.Glow_Item_Bomb_B =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_bomb_b"),				Color.Glow_Item_Bomb_B);
	Color.Glow_Item_Other_R =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_other_r"),			Color.Glow_Item_Other_R);
	Color.Glow_Item_Other_G =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_other_g"),			Color.Glow_Item_Other_G);
	Color.Glow_Item_Other_B =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("glow_item_other_b"),			Color.Glow_Item_Other_B);
	Color.Chams_Enemy_R =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_enemy_r"),				Color.Chams_Enemy_R);
	Color.Chams_Enemy_G =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_enemy_g"),				Color.Chams_Enemy_G);
	Color.Chams_Enemy_B =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_enemy_b"),				Color.Chams_Enemy_B);
	Color.Chams_Ally_R =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_ally_r"),					Color.Chams_Ally_R);
	Color.Chams_Ally_G =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_ally_g"),					Color.Chams_Ally_G);
	Color.Chams_Ally_B =						iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_ally_b"),					Color.Chams_Ally_B);
	Color.Chams_Terrorist_R =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_terrorist_r"),			Color.Chams_Terrorist_R);
	Color.Chams_Terrorist_G =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_terrorist_g"),			Color.Chams_Terrorist_G);
	Color.Chams_Terrorist_B =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_terrorist_b"),			Color.Chams_Terrorist_B);
	Color.Chams_CounterTerrorist_R =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_counterterrorist_r"),		Color.Chams_CounterTerrorist_R);
	Color.Chams_CounterTerrorist_G =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_counterterrorist_g"),		Color.Chams_CounterTerrorist_G);
	Color.Chams_CounterTerrorist_B =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_counterterrorist_b"),		Color.Chams_CounterTerrorist_B);
	Color.Chams_Highlight_God_R =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_god_r"),		Color.Chams_Highlight_God_R);
	Color.Chams_Highlight_God_G =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_god_g"),		Color.Chams_Highlight_God_G);
	Color.Chams_Highlight_God_B =				iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_god_b"),		Color.Chams_Highlight_God_B);
	Color.Chams_Highlight_Scoped_R =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_scoped_r"),		Color.Chams_Highlight_Scoped_R);
	Color.Chams_Highlight_Scoped_G =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_scoped_g"),		Color.Chams_Highlight_Scoped_G);
	Color.Chams_Highlight_Scoped_B =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_scoped_b"),		Color.Chams_Highlight_Scoped_B);
	Color.Chams_Highlight_Flashed_R =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_flashed_r"),	Color.Chams_Highlight_Flashed_R);
	Color.Chams_Highlight_Flashed_G =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_flashed_g"),	Color.Chams_Highlight_Flashed_G);
	Color.Chams_Highlight_Flashed_B =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_flashed_b"),	Color.Chams_Highlight_Flashed_B);
	Color.Chams_Highlight_Defuser_R =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_defuser_r"),	Color.Chams_Highlight_Defuser_R);
	Color.Chams_Highlight_Defuser_G =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_defuser_g"),	Color.Chams_Highlight_Defuser_G);
	Color.Chams_Highlight_Defuser_B =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_defuser_b"),	Color.Chams_Highlight_Defuser_B);
	Color.Chams_Highlight_Planter_R =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_planter_r"),	Color.Chams_Highlight_Planter_R);
	Color.Chams_Highlight_Planter_G =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_planter_g"),	Color.Chams_Highlight_Planter_G);
	Color.Chams_Highlight_Planter_B =			iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_highlight_planter_b"),	Color.Chams_Highlight_Planter_B);
	Color.Chams_Viewmodel_R =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_viewmodel_r"),			Color.Chams_Viewmodel_R);
	Color.Chams_Viewmodel_G =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_viewmodel_g"),			Color.Chams_Viewmodel_G);
	Color.Chams_Viewmodel_B =					iniReader.ReadFloat		(XorStr("Color"),		XorStr("chams_viewmodel_b"),			Color.Chams_Viewmodel_B);
	
	if (Aimbot.Aimbot_Bone > 80 || Aimbot.Aimbot_Bone < 0)
		Aimbot.Aimbot_Bone = 8;

	if (Aimbot.Aimbot_Smooth_Pitch < 0)
		Aimbot.Aimbot_Smooth_Pitch = 0;

	if (Aimbot.Aimbot_Smooth_Yaw < 0)
		Aimbot.Aimbot_Smooth_Yaw = 0;

	if (Misc.Reduce_Flash_Alpha <= 0)
		Misc.Reduce_Flash_Alpha = 1;

}
