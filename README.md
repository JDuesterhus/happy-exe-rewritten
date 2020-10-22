# happy-exe-re | CS Cheat



## Features

### ESP 👁‍🗨
* Glow Players
  * Enemies
  * Allies
* Glow Items 
  * Weapons
  * Grenades
  * Bombs
  * Other Items
* Glow Player Highlights
  * If Invincibile
  * If Scoped
  * If Blinded
  * If Defusing
* Glow Style
  * Glow Outline Through Walls
  * Glow Pulsating
  * Glow Inline
* Glow Alpha
* Chams Players
  * Enemies
  * Allies
* Chams Viewmodel
* Chams Player Highlights
  * If Invincibile
  * If Scoped
  * If Blinded
  * If Defusing
  
### Aimbot 🎯
* Bone
* Bone Secondary
  * After x Shots
  * On x Health
* Recoil Control System
  * Pitch
  * Yaw
  * After x Shots
* Field Of View
* Delay
  * Before
  * After Kill
* Smoothness
  * Pitch
  * Yaw
* Filter
  * If Invincibile
  * If Ally
  * If In Air
  * If Blinded
  * If Visible
  
  
### Triggerbot ⚠️
* Burst
  * Amount of Bullets
* Dash
* Filter
  * If Invincibile
  * If Ally
  * If Blinded
  * If Scoped
* Delay
  * Randomized Delay
  * First Delay
  * Burst Delay
  * Last Delay
  
### Miscellaneous 🌐
* Autopistol
* Radar
* Bunnyhop
  * While Crouching
* Autostrafe
* Chat Spammer
  * Random Line
  * Delay
  * Custom Text File
* Visuals
  * Remove Viewmodel Hands
  * Remove Ragdolls
  * Remove Fog
  * Remove Smokes
  * Reduce Flash
  * Overwrite Player Field Of View
  * Nightmode
  * Knife Swap
* Fakelag
  * Every x Ticks
* Weapon Config
  * For Weapon Group
  * For Each Weapon
* Automatic Updates
* Customizable Hotkeys
  * Toggle Keys For Most Features
  * Hold Keys For Some Features
  * Useful Bindings
  * Reload Config
  * Panic Exit
* Customizable Colors For ESP Features

## Config

### Default Config

Default Config Location: .\config\default.ini

Config Example:
```
[ESP]
glow=True
glow_enemy=True
glow_ally=True
glow_item=True
glow_highlight_god=False
glow_highlight_scoped=False
glow_highlight_flashed=False
glow_highlight_defuser=False
glow_highlight_planter=False
glow_item_pistol=True
glow_item_smg=True
glow_item_shotgun=True
glow_item_rifle=True
glow_item_sniper=True
glow_item_grenade=True
glow_item_bomb=True
glow_item_other=True
glow_custom_color=1
glow_style=0
glow_alpha=255
chams=True
chams_enemy=True
chams_ally=True
chams_viewmodel=False
chams_highlight_visible=False
chams_highlight_god=False
chams_highlight_scoped=False
chams_highlight_flashed=False
chams_highlight_defuser=False
chams_highlight_planter=False
chams_custom_color=1
chams_alpha=102

[Aimbot]
aimbot=True
aimbot_hotkey=True
aimbot_bone=8
aimbot_bone2=7
aimbot_bone2_aftershots=8
aimbot_bone2_onhealth=10
aimbot_rcs=True
aimbot_fov=3
aimbot_delay=0
aimbot_delay_kill=0
aimbot_smooth_pitch=20
aimbot_smooth_yaw=15
aimbot_ignore_god=False
aimbot_ignore_ally=True
aimbot_ignore_jump=False
aimbot_check_flash=False
aimbot_check_visible=False
rcs=True
rcs_pitch=102
rcs_yaw=90
rcs_aftershots=0

[Triggerbot]
triggerbot=True
triggerbot_hotkey=True
triggerbot_burst=False
triggerbot_burst_bullets=2
triggerbot_dash=True
triggerbot_ignore_god=True
triggerbot_ignore_ally=False
triggerbot_check_flash=False
triggerbot_check_zoom=False
triggerbot_delay_random=False
triggerbot_delay_random_from=10
triggerbot_delay_random_to=50
triggerbot_delay_first=0
triggerbot_delay_burst=180
triggerbot_delay_last=350

[Misc]
autopistol=True
radar=True
bunnyhop=True
bunnyhop_crouch=True
autostrafe=False
spammer=False
spammer_random=False
spammer_delay=0
spammer_path=.\\config\\spam\\clear.txt
remove_hands=False
remove_ragdoll=False
remove_fog=False
remove_smoke=False
reduce_flash=True
reduce_flash_alpha=204
overwrite_fov=False
overwrite_fov_custom=120
nightmode=False
nightmode_alpha=51
fakelag=False
fakelag_hotkey=True
fakelag_ticks=12
bomb_timer=False
swap_knife_hand=False
weapon_config=0
offset_url= ;put an url with updated offsets/netvars here
window_transparency=204

;use virtual key codes in decimal
[Hotkey]
toggle_glow=117
toggle_cham=118
toggle_aimbot=33
toggle_triggerbot=120
toggle_autopistol=122
toggle_radar=119
toggle_bunnyhop=36
toggle_autostrafe=35
toggle_spammer=0
toggle_remove_hands=0
toggle_remove_ragdoll=0
toggle_remove_fog=0
toggle_remove_smoke=0
toggle_reduce_flash=0
toggle_overwrite_fov=0
toggle_nightmode=0
toggle_fakelag=34
hold_aimbot=1
hold_triggerbot=18
hold_bunnyhop=32
hold_fakelag=18
bind_2hp=4
bind_180=0
bind_360=0
reload_config=45
panic_exit=0;46

[Color]
glow_enemy_r=128
glow_enemy_g=128
glow_enemy_b=0
glow_ally_r=51
glow_ally_g=51
glow_ally_b=51
glow_terrorist_r=118
glow_terrorist_g=92
glow_terrorist_b=45
glow_counterterrorist_r=59
glow_counterterrorist_g=81
glow_counterterrorist_b=115
glow_highlight_god_r=255
glow_highlight_god_g=255
glow_highlight_god_b=255
glow_highlight_scoped_r=85
glow_highlight_scoped_g=85
glow_highlight_scoped_b=85
glow_highlight_flashed_r=85
glow_highlight_flashed_g=85
glow_highlight_flashed_b=85
glow_highlight_defuser_r=255
glow_highlight_defuser_g=0
glow_highlight_defuser_b=0
glow_highlight_planter_r=255
glow_highlight_planter_g=0
glow_highlight_planter_b=0
glow_item_weapon_r=192
glow_item_weapon_g=64
glow_item_weapon_b=0
glow_item_grenade_r=192
glow_item_grenade_g=64
glow_item_grenade_b=0
glow_item_bomb_r=255
glow_item_bomb_g=0
glow_item_bomb_b=0
glow_item_other_r=0
glow_item_other_g=255
glow_item_other_b=0
chams_enemy_r=255
chams_enemy_g=0
chams_enemy_b=0
chams_ally_r=102
chams_ally_g=102
chams_ally_b=102
chams_terrorist_r=255
chams_terrorist_g=0
chams_terrorist_b=0
chams_counterterrorist_r=0
chams_counterterrorist_g=0
chams_counterterrorist_b=255
chams_viewmodel_r=102
chams_viewmodel_g=0
chams_viewmodel_b=102
chams_highlight_god_r=255
chams_highlight_god_g=255
chams_highlight_god_b=255
chams_highlight_scoped_r=85
chams_highlight_scoped_g=85
chams_highlight_scoped_b=85
chams_highlight_flashed_r=255
chams_highlight_flashed_g=255
chams_highlight_flashed_b=204
chams_highlight_defuser_r=255
chams_highlight_defuser_g=0
chams_highlight_defuser_b=0
chams_highlight_planter_r=255
chams_highlight_planter_g=0
chams_highlight_planter_b=0
```
### Weapon Configs

Location for Weapon Groups: .\config\weapon_cfg_groups\

List of available Weapon Groups:
```
WEAPON_PISTOL.ini
WEAPON_RIFLE.ini
WEAPON_SHOTGUN.ini
WEAPON_SMG.ini
WEAPON_SNIPER.ini
```

Location for Individual Weapons: .\config\weapon_cfg_single\

List of available Individual Weapons:
```
WEAPON_DEAGLE.ini
WEAPON_ELITE.ini
WEAPON_FIVESEVEN.ini
WEAPON_GLOCK.ini
WEAPON_AK47.ini
WEAPON_AUG.ini
WEAPON_AWP.ini
WEAPON_FAMAS.ini
WEAPON_G3SG1.ini
WEAPON_GALIL.ini
WEAPON_M249.ini
WEAPON_M4A4.ini
WEAPON_MAC10.ini
WEAPON_P90.ini
WEAPON_MP5SD.ini
WEAPON_UMP45.ini
WEAPON_XM1014.ini
WEAPON_BIZON.ini
WEAPON_MAG7.ini
WEAPON_NEGEV.ini
WEAPON_SAWEDOFF.ini
WEAPON_TEC9.ini
WEAPON_P2000.ini
WEAPON_MP7.ini
WEAPON_MP9.ini
WEAPON_NOVA.ini
WEAPON_P250.ini
WEAPON_SCAR20.ini
WEAPON_SG553.ini
WEAPON_SSG08.ini
WEAPON_M4A1S.ini
WEAPON_USPS.ini
WEAPON_CZ75.ini
WEAPON_REVOLVER.ini
```
  
## FAQ
#### Q: Who made this?

#### A: Most code was written by me with the exception of some functions in Aimbot.cpp (AngleDiff, Dot, GetFov, CalcAngle, ClampAngle, NormalizeAngle, SmoothAngle, MakeVector) and a few minor things in vector.h.

#### Q: Why did you make this?

#### A: I made a cheat in 2015 that mostly consisted of copy pasted code and with terrible performance. I wanted to make something new so I started this project in late 2019 from scratch and tried to fix all the issues I previously had and make use of object oriented programming to clean up the code. The code is still messy and I could have made better use of object oriented classes (for example with reading/writing entities) but the readability still a lot better than "my" old project that had everything slammed into one file.

#### Q: How to build?

#### A: You can't because I left out some bigger files that stayed mostly untouched by me (IniReader, Memory Class, Json Parser). This was intentional because I didn't want to include already completed code that I didn't write myself and also to prevent people from spreading compiled versions of it on the forums.

#### Q: How is this useful then?

#### A: You'll probably find no use in this except if you can learn anything from it but you can probably find better code to learn from since this poorly written.
  
