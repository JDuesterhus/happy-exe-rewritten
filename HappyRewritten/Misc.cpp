#include "Misc.h"

CMisc Misc;


//proper autopistol takes too much cpu performance
//if (IsAttacking()) {
//	if (WeaponIsPistol(GetCurrentWeapon(Offsets.LocalBase))) {
//		while (GetAsyncKeyState(VK_LBUTTON)) {
//			int tickbase = Memory::Read<int>(Offsets.LocalBase + Offsets.m_nTickBase);
//			CGlobalVarsBase var = Memory::Read<CGlobalVarsBase>(Offsets.dwEngine + Offsets.dwGlobalVars);
//			float servertime = tickbase * var.interval_per_tick;
//			static float nextattack;
//			if (nextattack < servertime) {
//				Memory::Write<int>(Offsets.dwClient + Offsets.dwForceAttack, 6);
//				nextattack = Memory::Read<float>(GetWeaponEntity(Offsets.LocalBase) + Offsets.m_flNextPrimaryAttack);
//				std::cout << "shoot" << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
//				Sleep(10);
//			}
//			else {
//				Sleep(10);
//			}
//		}
//	}
//	Sleep(1);
//}

void CMisc::Autopistol() {
	if (IsAttacking()) {
		if (WeaponIsPistol(GetCurrentWeapon(Offsets.LocalBase))) {
			while (GetAsyncKeyState(VK_LBUTTON)) {
				int AttackState;
				if (GetShotsFired(Offsets.LocalBase) == 0)
					AttackState = 5;
				if (GetShotsFired(Offsets.LocalBase) >= 1)
					AttackState = 4;
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack, AttackState);
				Sleep(10);
			}
		}
		//if (WeaponIsSniper(GetCurrentWeapon(Offsets.LocalBase))) {
		//	if (GetShotsFired(Offsets.LocalBase) >= 1) {
		//		Console("lastinv"); //slot3
		//		Sleep(32);
		//		Console("slot1");
		//	}
		//}
	}
	//if (IsReloading(Offsets.LocalBase)) {
	//	int clip = Memory::Read<int>(Misc.GetWeaponEntity(Offsets.LocalBase) + Offsets.m_iClip1);
	//	static int clipold = clip;
	//	if (clip > clipold) {
	//		Console("lastinv");
	//		Sleep(32);
	//		Console("lastinv");
	//	}
	//	Sleep(10);
	//	clipold = clip;
	//}
}

void CMisc::BunnyHop() {
	if (IsJumping()) {
		while (GetAsyncKeyState(Settings.Hotkey.Hold_Bunnyhop) & Pressed) {
			int JumpState;
			if (CanJump(GetFlags(Offsets.LocalBase), Settings.Misc.Bunnyhop_Crouch))
				JumpState = 7;
			else
				JumpState = 4;
			if (Settings.Misc.Fakelag && JumpState == 7)
				Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, true);
			Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceJump, JumpState);
			Sleep(1);
		}
	}
}


void CMisc::AutoStrafe() {
	static bool movementfix = false;
	if (Misc.GetSpeed2D() >= 35) { //replace >= 0 with old one
		static Vector PrevViewAngle;
		Vector StrafeAngles = Memory::Read<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles);
		if (GetFlags(Offsets.LocalBase) == FL_IN_AIR_STAND || GetFlags(Offsets.LocalBase) == FL_IN_AIR_CROUCHED) {
			if (StrafeAngles.y > PrevViewAngle.y && !GetAsyncKeyState(0x44)) {
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceLeft, 1);
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceRight, 6);
			}
			if (StrafeAngles.y < PrevViewAngle.y && !GetAsyncKeyState(0x41)) {
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceRight, 1);
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceLeft, 6);
			}
			if (StrafeAngles.y == PrevViewAngle.y) {
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceLeft, 6);
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceRight, 6);
			}
			movementfix = true;
		}
		if (CanJump(GetFlags(Offsets.LocalBase), true) && movementfix) {
			if (GetAsyncKeyState(0x41))
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceLeft, 1);
			if (!GetAsyncKeyState(0x41))
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceLeft, 6);
			if (GetAsyncKeyState(0x44))
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceRight, 1);
			if (!GetAsyncKeyState(0x44))
				Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceRight, 6);
			movementfix = false;
		}
		PrevViewAngle = StrafeAngles;
	}
}

//void AutoStrafe() {
//	if (mySpeed >= 55) {
//		static Vector3 prevViewAngle;
//		Vector3 strafeAngles = Memory::Read<Vector3>(EngineBase + m_dwViewAngles);
//		if (fflag == FL_IN_AIR_STAND || fflag == FL_IN_AIR_CROUCHED) {
//			if (strafeAngles.y > prevViewAngle.y && !GetAsyncKeyState(0x41)) {
//				Mem.Write<int>(Client.dwBase + m_dwMoveLeft, 6);
//			}
//			if (strafeAngles.y < prevViewAngle.y && !GetAsyncKeyState(0x44)) {
//				Mem.Write<int>(Client.dwBase + m_dwMoveRight, 6);
//			}
//		}
//		Sleep(4);
//		prevViewAngle = strafeAngles;
//	}
//}

//void CMisc::Fakelag() {
//	CGlobalVarsBase var = Memory::Read<CGlobalVarsBase>(Offsets.dwEngine + Offsets.dwGlobalVars);
//	int tick = var.tickcount;
//	Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, false);
//	do {
//		Sleep(3);
//		var = Memory::Read<CGlobalVarsBase>(Offsets.dwEngine + Offsets.dwGlobalVars);
//	} while (var.tickcount < (tick + Settings.Misc.Fakelag_Ticks));
//	tick = var.tickcount;
//	Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, true);
//	do {
//		Sleep(3);
//		var = Memory::Read<CGlobalVarsBase>(Offsets.dwEngine + Offsets.dwGlobalVars);
//	} while (var.tickcount < (tick + Settings.Misc.Fakelag_Ticks));
//}


void CMisc::Fakelag() {
	Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, false);
	Sleep(15.625 * Settings.Misc.Fakelag_Ticks);
	Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, true);
	Sleep(15.625 * Settings.Misc.Fakelag_Ticks);
}

void CMisc::FakelagFix() {
	static int prevWeapon;
	static int prevShots;
	//PREVENTS WEAPON SWITCH FAILING/GLITCHING
	if (GetCurrentWeapon(Offsets.LocalBase) != prevWeapon) {
		Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, true);
	}
	//PREVENTS RCS FUCKING UP
	if (GetShotsFired(Offsets.LocalBase) != prevShots) {
		Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, true);
	}
	prevShots = GetShotsFired(Offsets.LocalBase);
	prevWeapon = GetCurrentWeapon(Offsets.LocalBase);
}

void CMisc::ChatSpam() {
	std::vector<std::string> text_file;
	std::string line;
	int line_counter = 0;
	std::ifstream myfile(Settings.Misc.Spammer_Path);

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			text_file.push_back(line);
			line_counter++;
		}
		if (line_counter > 0) {
			static int line = 0;
			if (Settings.Misc.Spammer_Random) {
				line = rand() % line_counter;
			}
			//std::cout << text_file[line] << std::endl;
			std::string sayspam = u8"say " + text_file[line];
			const char* spam = sayspam.c_str();
			Console(spam);
			text_file.erase(text_file.begin() + line);
			if (!Settings.Misc.Spammer_Random) {
				line++;
				if (line_counter <= line) {
					line = 0;
				}
			}
		}
		myfile.close();
	}
	Sleep(750 + Settings.Misc.Spammer_Delay);
}

void CMisc::WeaponConfig() {
	char* cfgpath = "";
	bool loadcfg = true;
	static int PreviousWeapon = 0;
	int CurrentWeapon = GetCurrentWeapon(Offsets.LocalBase);
	//std::cout << "wepid: " << CurrentWeapon << std::endl;
	//std::cout << "pwepid: " << PreviousWeapon << std::endl;
	if (CurrentWeapon != PreviousWeapon) {
		//CONFIG FOR WEAPON GROUPS
		if (Settings.Misc.Weapon_Config == 1) {
			switch (CurrentWeapon) {
			case WEAPON_CZ75:
			case WEAPON_DEAGLE:
			case WEAPON_ELITE:
			case WEAPON_FIVESEVEN:
			case WEAPON_GLOCK:
			case WEAPON_P2000:
			case WEAPON_P250:
			case WEAPON_REVOLVER:
			case WEAPON_TEC9:
			case WEAPON_USPS:
				cfgpath = ".\\config\\weapon_cfg_groups\\WEAPON_PISTOL.ini";
				loadcfg = true;
				break;
			case WEAPON_AK47:
			case WEAPON_AUG:
			case WEAPON_FAMAS:
			case WEAPON_GALIL:
			case WEAPON_M249:
			case WEAPON_M4A1S:
			case WEAPON_M4A4:
			case WEAPON_NEGEV:
			case WEAPON_SG553:
				cfgpath = ".\\config\\weapon_cfg_groups\\WEAPON_RIFLE.ini";
				loadcfg = true;
				break;
			case WEAPON_MAG7:
			case WEAPON_NOVA:
			case WEAPON_SAWEDOFF:
			case WEAPON_XM1014:
				cfgpath = ".\\config\\weapon_cfg_groups\\Weapon_SHOTGUN.ini";
				loadcfg = true;
				break;
			case WEAPON_BIZON:
			case WEAPON_MAC10:
			case WEAPON_MP5SD:
			case WEAPON_MP7:
			case WEAPON_MP9:
			case WEAPON_P90:
			case WEAPON_UMP45:
				cfgpath = ".\\config\\weapon_cfg_groups\\Weapon_SMG.ini";
				loadcfg = true;
				break;
			case WEAPON_AWP:
			case CWeaponG3SG1:
			case WEAPON_SCAR20:
			case WEAPON_SSG08:
				cfgpath = ".\\config\\weapon_cfg_groups\\Weapon_SNIPER.ini";
				loadcfg = true;
				break;
			default:
				cfgpath = "";
				loadcfg = false;
				break;
			}
		}
		//CONFIG FOR SINGLE WEAPON
		if (Settings.Misc.Weapon_Config == 2) {
			switch (CurrentWeapon) {
			case WEAPON_DEAGLE:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_DEAGLE.ini";
				loadcfg = true;
				break;
			case WEAPON_ELITE:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_ELITE.ini";
				loadcfg = true;
				break;
			case WEAPON_FIVESEVEN:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_FIVESEVEN.ini";
				loadcfg = true;
				break;
			case WEAPON_GLOCK:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_GLOCK.ini";
				loadcfg = true;
				break;
			case WEAPON_AK47:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_AK47.ini";
				loadcfg = true;
				break;
			case WEAPON_AUG:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_AUG.ini";
				loadcfg = true;
				break;
			case WEAPON_AWP:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_AWP.ini";
				loadcfg = true;
				break;
			case WEAPON_FAMAS:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_FAMAS.ini";
				loadcfg = true;
				break;
			case WEAPON_G3SG1:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_G3SG1.ini";
				loadcfg = true;
				break;
			case WEAPON_GALIL:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_GALIL.ini";
				loadcfg = true;
				break;
			case WEAPON_M249:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_M249.ini";
				loadcfg = true;
				break;
			case WEAPON_M4A4:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_M4A4.ini";
				loadcfg = true;
				break;
			case WEAPON_MAC10:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_MAC10.ini";
				loadcfg = true;
				break;
			case WEAPON_P90:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_P90.ini";
				loadcfg = true;
				break;
			case WEAPON_MP5SD:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_MP5SD.ini";
				loadcfg = true;
				break;
			case WEAPON_UMP45:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_UMP45.ini";
				loadcfg = true;
				break;
			case WEAPON_XM1014:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_XM1014.ini";
				loadcfg = true;
				break;
			case WEAPON_BIZON:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_BIZON.ini";
				loadcfg = true;
				break;
			case WEAPON_MAG7:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_MAG7.ini";
				loadcfg = true;
				break;
			case WEAPON_NEGEV:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_NEGEV.ini";
				loadcfg = true;
				break;
			case WEAPON_SAWEDOFF:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_SAWEDOFF.ini";
				loadcfg = true;
				break;
			case WEAPON_TEC9:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_TEC9.ini";
				loadcfg = true;
				break;
			case WEAPON_P2000:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_P2000.ini";
				loadcfg = true;
				break;
			case WEAPON_MP7:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_MP7.ini";
				loadcfg = true;
				break;
			case WEAPON_MP9:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_MP9.ini";
				loadcfg = true;
				break;
			case WEAPON_NOVA:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_NOVA.ini";
				loadcfg = true;
				break;
			case WEAPON_P250:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_P250.ini";
				loadcfg = true;
				break;
			case WEAPON_SCAR20:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_SCAR20.ini";
				loadcfg = true;
				break;
			case WEAPON_SG553:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_SG553.ini";
				loadcfg = true;
				break;
			case WEAPON_SSG08:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_SSG08.ini";
				loadcfg = true;
				break;
			case WEAPON_M4A1S:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_M4A1S.ini";
				loadcfg = true;
				break;
			case WEAPON_USPS:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_USPS.ini";
				loadcfg = true;
				break;
			case WEAPON_CZ75:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_CZ75.ini";
				loadcfg = true;
				break;
			case WEAPON_REVOLVER:
				cfgpath = ".\\config\\weapon_cfg_single\\WEAPON_REVOLVER.ini";
				loadcfg = true;
				break;
			default:
				cfgpath = "";
				loadcfg = false;
				break;
			}

		}
		if (loadcfg) {
			Settings.LoadConfig(cfgpath);
			//std::cout << "Loaded CFG" << std::endl;
			//std::cout << "WepID: " << GetCurrentWeapon(Offsets.LocalBase) << std::endl;
			//std::cout << "Path: " << cfgpath << std::endl;
		}
	}
	Sleep(100);
	PreviousWeapon = CurrentWeapon;
}

bool CMisc::IsJumping() {
	int inJump = Memory::Read<BYTE>(Offsets.dwClient + Offsets.dwForceJump);
	switch (inJump) {
	case 1:
	case 5:
	case 6:
	case 7:
		return true;
	default:
		return false;
	}
}

bool CMisc::CanJump(int flag, bool crouch) {
	if (crouch) {
		switch (flag) {
		case FL_ON_GROUND:
		case FL_IN_PUDDLE:
		case FL_ON_GROUND_CROUCHED:
		case FL_IN_PUDDLE_CROUCHED:
		case FL_ON_GROUND_MOVING_TO_STAND:
		case FL_ON_GROUND_MOVING_TO_CROUCH:
			return true;
		default:
			return false;
		}
	}
	else {
		switch (flag) {
		case FL_ON_GROUND:
		case FL_IN_PUDDLE:
		case FL_ON_GROUND_MOVING_TO_STAND:
		case FL_ON_GROUND_MOVING_TO_CROUCH:
			return true;
		default:
			return false;
		}
	}
}

int CMisc::GetFlags(DWORD base) {
	int fflag = Memory::Read<int>(base + Offsets.m_fFlags);
	return fflag;
}


DWORD CMisc::GetWeaponEntity(DWORD base) {
	DWORD weaponIndex = Memory::Read<DWORD>(base + Offsets.m_hActiveWeapon) & 0xFFF;
	DWORD weaponEntity = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwEntityList + (weaponIndex - 1) * 0x10);
	return weaponEntity;
}

int CMisc::GetCurrentWeapon(DWORD base) {
	int weaponID = Memory::Read<int>(GetWeaponEntity(base) + Offsets.m_iItemDefinitionIndex); //
	if (weaponID >= 262144) weaponID -= 262144; //weird skin "bugfix"
	return weaponID;
}

bool CMisc::IsReloading(DWORD base) {
	bool inReload = Memory::Read<bool>(GetWeaponEntity(base) + Offsets.m_bInReload);
	return inReload;
}

float CMisc::GetWeaponAccuracy(DWORD base) {
	float weaponAccuracy = Memory::Read<float>(GetWeaponEntity(base) + Offsets.m_fAccuracyPenalty);
	return weaponAccuracy;
}

bool CMisc::IsAttacking() {
	int inAttack = Memory::Read<BYTE>(Offsets.dwClient + Offsets.dwForceAttack);
	switch (inAttack) {
	case 1:
	case 5:
	//case 6:
	case 7:
		return true;
	default:
		return false;
	}
}

bool CMisc::IsAttacking2() {
	int inAttack2 = Memory::Read<BYTE>(Offsets.dwClient + Offsets.dwForceAttack - 0x54);
	switch (inAttack2) {
	case 1:
	case 5:
	//case 6:
	case 7:
		return true;
	default:
		return false;
	}
}

int CMisc::GetShotsFired(DWORD base) {
	int shotsFired = Memory::Read<int>(base + Offsets.m_iShotsFired);
	return shotsFired;
}

//WALKING AND FALLING SPEED
float CMisc::GetSpeed3D() {
	Vector velocity = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_vecVelocity);
	float speed = FASTSQRT(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
	return speed;
}

//WALKING SPEED
float CMisc::GetSpeed2D() {
	Vector velocity = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_vecVelocity);
	float speed = FASTSQRT(velocity.x * velocity.x + velocity.y * velocity.y);
	return speed;
}

//FALLING/JUMPING SPEED
float CMisc::GetSpeed1D() {
	Vector velocity = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_vecVelocity);
	float speed = FASTSQRT(velocity.z * velocity.z);
	return speed;
}

bool CMisc::WeaponCanShoot(int id) {
	switch (id) {
	case WEAPON_DEAGLE:
	case WEAPON_ELITE:
	case WEAPON_FIVESEVEN:
	case WEAPON_GLOCK:
	case WEAPON_AK47:
	case WEAPON_AUG:
	case WEAPON_AWP:
	case WEAPON_FAMAS:
	case WEAPON_G3SG1:
	case WEAPON_GALIL:
	case WEAPON_M249:
	case WEAPON_M4A4:
	case WEAPON_MAC10:
	case WEAPON_P90:
	case WEAPON_MP5SD:
	case WEAPON_UMP45:
	case WEAPON_XM1014:
	case WEAPON_BIZON:
	case WEAPON_MAG7:
	case WEAPON_NEGEV:
	case WEAPON_SAWEDOFF:
	case WEAPON_TEC9:
	case WEAPON_ZEUS:
	case WEAPON_P2000:
	case WEAPON_MP7:
	case WEAPON_MP9:
	case WEAPON_NOVA:
	case WEAPON_P250:
	case WEAPON_SCAR20:
	case WEAPON_SG553:
	case WEAPON_SSG08:
	case WEAPON_M4A1S:
	case WEAPON_USPS:
	case WEAPON_CZ75:
	case WEAPON_REVOLVER:
		return true;
	default:
		return false;
	}
}

bool CMisc::WeaponIsPistol(int id) {
	switch (id) {
	case WEAPON_DEAGLE:
	case WEAPON_ELITE:
	case WEAPON_FIVESEVEN:
	case WEAPON_GLOCK:
	case WEAPON_TEC9:
	case WEAPON_P2000:
	case WEAPON_P250:
	case WEAPON_USPS:
	//case Weapon_Revolver:
		return true;
	default:
		return false;
	}
}

bool CMisc::WeaponIsSniper(int id) {
	switch (id) {
	case WEAPON_AWP:
	case WEAPON_G3SG1:
	case WEAPON_SCAR20:
	case WEAPON_SSG08:
		return true;
	default:
		return false;
	}
}

bool CMisc::WeaponIsKnife(int id) {
	switch (id) {
	case WEAPON_KNIFEGG:
	case WEAPON_KNIFE:
	case WEAPON_KNIFE_T:
	case WEAPON_FISTS:
	case WEAPON_MELEE:
	case WEAPON_AXE:
	case WEAPON_HAMMER:
	case WEAPON_SPANNER:
	case WEAPON_KNIFE_GHOST:
	case WEAPON_KNIFE_BAYONET:
	case WEAPON_KNIFE_CLASSIC:
	case WEAPON_KNIFE_FLIP:
	case WEAPON_KNIFE_GUT:
	case WEAPON_KNIFE_KARAMBIT:
	case WEAPON_KNIFE_M9_BAYONET:
	case WEAPON_KNIFE_TACTICAL:
	case WEAPON_KNIFE_FALCHION:
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
	case WEAPON_KNIFE_BUTTERFLY:
	case WEAPON_KNIFE_PUSH:
	case WEAPON_KNIFE_URSUS:
	case WEAPON_KNIFE_GYPSY_JACKKNIFE:
	case WEAPON_KNIFE_STILETTO:
	case WEAPON_KNIFE_WIDOWMAKER:
		return true;
	default:
		return false;
	}
}

void CMisc::Console(const char* command) {
	static int count = 0;
	ClientCmd_Unrestricted_t args;

	strcpy(args.command, command);
	args.delay = false;

	LPVOID addr = (LPVOID)Offsets.ClientCMDArray;
	LPVOID vArgs = (LPVOID)VirtualAllocEx(Memory::hProc, NULL, sizeof(args), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(Memory::hProc, vArgs, (LPCVOID)&args, sizeof(args), NULL);
	HANDLE hThread = CreateRemoteThread(Memory::hProc, NULL, NULL, (LPTHREAD_START_ROUTINE)addr, vArgs, NULL, NULL);
	WaitForSingleObject(hThread, INFINITE);
	VirtualFreeEx(Memory::hProc, vArgs, sizeof(args), MEM_RELEASE);
	CloseHandle(hThread);
	count++;
	//std::cout << "ClientCmd amount: " << count << std::endl;
}