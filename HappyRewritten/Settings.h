#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <streambuf>
#include "IniReader.h"
#include "XorStr.h"
//#include "json11.hpp"

class CSettings
{
public:
	void LoadConfig(char* path);
	std::string text;

	struct {
		bool Glow = true;
		bool Glow_Enemy = true;
		bool Glow_Ally = true;
		bool Glow_Item = false;
		bool Glow_Highlight_God = false;
		bool Glow_Highlight_Scoped = false;
		bool Glow_Highlight_Flashed = false;
		bool Glow_Highlight_Defuser = false;
		bool Glow_Highlight_Planter = false;
		bool Glow_Item_Pistol = true;
		bool Glow_Item_SMG = true;
		bool Glow_Item_Shotgun = true;
		bool Glow_Item_Rifle = true;
		bool Glow_Item_Sniper = true;
		bool Glow_Item_Grenade = true;
		bool Glow_Item_Bomb = true;
		bool Glow_Item_Other = true;
		int Glow_Custom_Color = 1;
		int Glow_Style = 0;
		float Glow_Alpha = 255;
		bool Chams = false;
		bool Chams_Enemy = true;
		bool Chams_Ally = true;
		bool Chams_Viewmodel = false;
		bool Chams_Highlight_God = false;
		bool Chams_Highlight_Scoped = false;
		bool Chams_Highlight_Flashed = false;
		bool Chams_Highlight_Defuser = false;
		bool Chams_Highlight_Planter = false;
		int Chams_Custom_Color = 1;
		float Chams_Alpha = 255;
	} ESP;

	struct {
		bool Aimbot = true;
		bool Aimbot_Hotkey = true;
		//bool Aimbot_Silent = false;
		//int Aimbot_Silent_Strength = 80;
		int Aimbot_Bone = 8;
		int Aimbot_Bone2 = 7;
		int Aimbot_Bone2_AfterShots = 4;
		int Aimbot_Bone2_OnHealth = 20;
		bool Aimbot_RCS = true;
		float Aimbot_FOV = 5;
		int Aimbot_Delay = 0;
		int Aimbot_Delay_Kill = 250;
		float Aimbot_Smooth_Pitch = 8;
		float Aimbot_Smooth_Yaw = 4;
		bool Aimbot_Ignore_God = false;
		bool Aimbot_Ignore_Ally = true;
		bool Aimbot_Ignore_Jump = false;
		bool Aimbot_Check_Flash = false;
		bool Aimbot_Check_Visible = false;
		bool RCS = true; //x
		//float RCS_Smooth_Pitch; //x
		//float RCS_Smooth_Yaw; //x
		float RCS_Pitch = 100;
		float RCS_Yaw = 100;
		int RCS_AfterShots = 0;
	} Aimbot;
	
	struct {
		bool Triggerbot = true;
		bool Triggerbot_Hotkey = true;
		bool Triggerbot_Burst = false;
		int Triggerbot_Burst_Bullets = 2;
		bool Triggerbot_Dash = false;
		bool Triggerbot_Ignore_God = false;
		bool Triggerbot_Ignore_Ally = true;
		bool Triggerbot_Check_Flash = false;
		bool Triggerbot_Check_Zoom = false;
		bool Triggerbot_Delay_Random = false;
		int Triggerbot_Delay_Random_From = 10;
		int Triggerbot_Delay_Random_To = 50;
		int Triggerbot_Delay_First = 0;
		int Triggerbot_Delay_Burst = 180;
		int Triggerbot_Delay_Last = 400;
	} Triggerbot;

	struct {
		bool Autopistol = false;
		bool Radar = true;
		bool Bunnyhop = true;
		bool Bunnyhop_Crouch = true;
		bool Autostrafe = false;
		bool Spammer = false;
		bool Spammer_Random = false;
		int Spammer_Delay = 0;
		std::string Spammer_Path = XorStr(u8".\\config\\ezfrags.txt");
		bool Remove_Hands = false;
		bool Remove_Ragdoll = false;
		bool Remove_Fog = false;
		bool Remove_Smoke = false;
		bool Reduce_Flash = true;
		float Reduce_Flash_Alpha = 51;
		bool Overwrite_FOV = false;
		int Overwrite_FOV_Custom = 120;
		bool Nightmode = false;
		float Nightmode_Alpha = 51;
		bool Fakelag = false;
		bool Fakelag_Hotkey = false;
		int Fakelag_Ticks = 14;
		bool Bomb_Timer = false;
		bool Swap_Knife_Hand = false;
		int Weapon_Config = 0;
		std::string Offset_URL = XorStr(u8"https://raw.githubusercontent.com/Akandesh/blazedumper/master/csgo.json");
		int Window_Transparency = 255;
	} Misc;

	struct {
		int Toggle_Glow = VK_F6;
		int Toggle_Chams = VK_F7;
		int Toggle_Aimbot = VK_PRIOR;
		int Toggle_Triggerbot = VK_F9;
		int Toggle_Autopistol = VK_F11;
		int Toggle_Radar = VK_F8;
		int Toggle_Bunnyhop = VK_HOME;
		int Toggle_Autostrafe = 0;
		int Toggle_Spammer = 0;
		int Toggle_Remove_Hands = 0;
		int Toggle_Remove_Ragdoll = 0;
		int Toggle_Remove_Fog = 0;
		int Toggle_Remove_Smoke = 0;
		int Toggle_Reduce_Flash = 0;
		int Toggle_Overwrite_FOV = 0;
		int Toggle_Nightmode = 0;
		int Toggle_Fakelag = VK_NEXT;
		int Hold_Aimbot = VK_LBUTTON;
		int Hold_TriggerBot = VK_MENU;
		int Hold_Bunnyhop = VK_SPACE;
		int Hold_Fakelag = VK_SHIFT;
		int Bind_2HP = 0;
		int Bind_180 = 0;
		int Bind_360 = 0;
		int Reload_Config = VK_INSERT;
		int Panic_Exit = VK_DELETE;
	} Hotkey;

	struct {
		float Glow_Enemy_R = 128;
		float Glow_Enemy_G = 128;
		float Glow_Enemy_B = 0;
		float Glow_Ally_R = 0;
		float Glow_Ally_G = 128;
		float Glow_Ally_B = 128;
		float Glow_Terrorist_R = 118;
		float Glow_Terrorist_G = 92;
		float Glow_Terrorist_B = 45;
		float Glow_CounterTerrorist_R = 59;
		float Glow_CounterTerrorist_G = 81;
		float Glow_CounterTerrorist_B = 115;
		float Glow_Highlight_God_R = 85;
		float Glow_Highlight_God_G = 85;
		float Glow_Highlight_God_B = 85;
		float Glow_Highlight_Scoped_R = 85;
		float Glow_Highlight_Scoped_G = 85;
		float Glow_Highlight_Scoped_B = 85;
		float Glow_Highlight_Flashed_R = 85;
		float Glow_Highlight_Flashed_G = 85;
		float Glow_Highlight_Flashed_B = 85;
		float Glow_Highlight_Defuser_R = 255;
		float Glow_Highlight_Defuser_G = 0;
		float Glow_Highlight_Defuser_B = 0;
		float Glow_Highlight_Planter_R = 255;
		float Glow_Highlight_Planter_G = 0;
		float Glow_Highlight_Planter_B = 0;
		float Glow_Item_Weapon_R = 192;
		float Glow_Item_Weapon_G = 64;
		float Glow_Item_Weapon_B = 0;
		float Glow_Item_Grenade_R = 192;
		float Glow_Item_Grenade_G = 64;
		float Glow_Item_Grenade_B = 0;
		float Glow_Item_Bomb_R = 255;
		float Glow_Item_Bomb_G = 0;
		float Glow_Item_Bomb_B = 0;
		float Glow_Item_Other_R = 0;
		float Glow_Item_Other_G = 255;
		float Glow_Item_Other_B = 0;
		float Chams_Enemy_R = 255;
		float Chams_Enemy_G = 0;
		float Chams_Enemy_B = 0;
		float Chams_Ally_R = 0;
		float Chams_Ally_G = 0;
		float Chams_Ally_B = 255;
		float Chams_Terrorist_R = 118;
		float Chams_Terrorist_G = 92;
		float Chams_Terrorist_B = 45;
		float Chams_CounterTerrorist_R = 59;
		float Chams_CounterTerrorist_G = 81;
		float Chams_CounterTerrorist_B = 115;
		float Chams_Highlight_God_R = 85;
		float Chams_Highlight_God_G = 85;
		float Chams_Highlight_God_B = 85;
		float Chams_Highlight_Scoped_R = 85;
		float Chams_Highlight_Scoped_G = 85;
		float Chams_Highlight_Scoped_B = 85;
		float Chams_Highlight_Flashed_R = 85;
		float Chams_Highlight_Flashed_G = 85;
		float Chams_Highlight_Flashed_B = 85;
		float Chams_Highlight_Defuser_R = 255;
		float Chams_Highlight_Defuser_G = 0;
		float Chams_Highlight_Defuser_B = 0;
		float Chams_Highlight_Planter_R = 255;
		float Chams_Highlight_Planter_G = 0;
		float Chams_Highlight_Planter_B = 0;
		float Chams_Viewmodel_R = 51;
		float Chams_Viewmodel_G = 153;
		float Chams_Viewmodel_B = 51;
	} Color;
};

extern CSettings Settings;