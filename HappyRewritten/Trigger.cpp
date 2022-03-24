#include "Trigger.h"

CTrigger Trigger;

//Don't change

void CTrigger::Run(){
	if (!Misc.IsAttacking()) {
		/*
		//TRIGGER HITCHANCE TEST
		if (Settings.Trigger.dash) {
			float Accuracy = (1 - Misc.GetWeaponAccuracy()) * 100.f - 0.0016f * powf(Misc.GetSpeed(), 2);
			//std::cout << "Acc: " << Accuracy << std::endl;
			if (Accuracy < Settings.Trigger.hitchance) {
				return;
			}
		}
		*/
		int weaponID = Misc.GetCurrentWeapon(Offsets.LocalBase);
		if (!Misc.WeaponValid(weaponID))
			return;

		if (Settings.Triggerbot.Triggerbot_Dash && weaponID != WEAPON_ZEUS) {
			if (Misc.GetSpeed3D() > DashSpeed())
				return;
		}
		if (Settings.Triggerbot.Triggerbot_Check_Flash) {
			float LocalFlashAlpha = Memory::Read<float>(Offsets.LocalBase + Offsets.m_flFlashMaxAlpha - 0x8);
			if (Settings.Misc.Reduce_Flash && LocalFlashAlpha >= Settings.Misc.Reduce_Flash_Alpha * 0.8 || !Settings.Misc.Reduce_Flash && LocalFlashAlpha >= 255 * 0.8) // '* 0.8' for 20% visibility
				return;
		}
		if (Settings.Triggerbot.Triggerbot_Check_Zoom) {
			if (Misc.WeaponIsSniper(weaponID) && !Misc.IsZooming(Offsets.LocalBase))
				return;
		}
		int chID = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iCrosshairId);
		DWORD chBase = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwEntityList + (chID - 1) * 0x10);
		if (!chBase)
			return;

		if (weaponID == WEAPON_ZEUS) {
			//check for bone pos instead
			Vector chEntityPos = Memory::Read<Vector>(chBase + Offsets.m_vecOrigin);
			Vector LocalPos = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_vecOrigin);
			float distance = abs(chEntityPos.x - LocalPos.x) + abs(chEntityPos.y - LocalPos.y) + abs(chEntityPos.z - LocalPos.z);
			if (distance > 195)
				return;
		}

		if (Settings.Triggerbot.Triggerbot_Ignore_Ally) {
			int chEntityTeam = Memory::Read<int>(chBase + Offsets.m_iTeamNum);
			int LocalTeam = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iTeamNum);
			if (chEntityTeam == LocalTeam)
				return;
		}
		if (Settings.Triggerbot.Triggerbot_Ignore_God) {
			float chEntityGodTime = Memory::Read<float>(chBase + Offsets.m_bGunGameImmunity - 0x8);
			if (chEntityGodTime > 0)
				return;
		}
		int chEntityHealth = Memory::Read<int>(chBase + Offsets.m_iHealth);
		if (chEntityHealth > 0) {
			TriggerBullets();
		}
	}
}

void CTrigger::TriggerShoot() {
	Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack, 5);
	Sleep(20);
	Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack, 4);
}

void CTrigger::TriggerBullets() {
	int b;
	if (Settings.Triggerbot.Triggerbot_Burst) {
		b = Settings.Triggerbot.Triggerbot_Burst_Bullets;
	}
	else {
		b = 1;
	}
	for (int x = 1; x <= b; x++) {
		// FIRST
		if (x == 1) {
			if (Settings.Triggerbot.Triggerbot_Delay_Random) {
				Sleep(rand() % (Settings.Triggerbot.Triggerbot_Delay_Random_To - (Settings.Triggerbot.Triggerbot_Delay_Random_From - 1)) + (Settings.Triggerbot.Triggerbot_Delay_Random_From));
			}
			else {
				//std::cout << "slept for " << Settings.Trigger.delay << std::endl;
				Sleep(Settings.Triggerbot.Triggerbot_Delay_First);
			}
			TriggerShoot();
			if (Settings.Triggerbot.Triggerbot_Burst) {
				Sleep(Settings.Triggerbot.Triggerbot_Delay_Burst);
			}
			else {
				Sleep(Settings.Triggerbot.Triggerbot_Delay_Last);
			}
		}
		if (Settings.Triggerbot.Triggerbot_Burst) {
			// MID
			if (x != 1 && x != b) {
				TriggerShoot();
				Sleep(Settings.Triggerbot.Triggerbot_Delay_Burst);

			}
			// LAST
			if (x == b) {
				TriggerShoot();
				Sleep(Settings.Triggerbot.Triggerbot_Delay_Last);
			}
		}
	}
}


/*

void TriggerShot() {
	if (!triggerWPM) {
		if (!triggerDelayRand && !triggerBurst) {
			Sleep(triggerDelay);
		}
		if (triggerDelayRand && !triggerBurst) {
			Sleep(rand() % (triggerDelayTo - (triggerDelayFrom - 1)) + (triggerDelayFrom));
		}
		//if (fakelagON) Mem.Write<bool>(Engine.dwBase + m_bSendPackets, true);
		mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
		Sleep(10);
		mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
		if (!triggerBurst) {
			Sleep(triggerDelayEnd);
		}
	}
	if (triggerWPM) {
		if (!triggerDelayRand && !triggerBurst) {
			Sleep(triggerDelay);
		}
		if (triggerDelayRand && !triggerBurst) {
			Sleep(rand() % (triggerDelayTo - (triggerDelayFrom - 1)) + (triggerDelayFrom));
		}
		//if (fakelagON) Mem.Write<bool>(Engine.dwBase + m_bSendPackets, true);
		Mem.Write<int>(Client.dwBase + m_dwForceAttack, 5);
		Sleep(20);
		Mem.Write<int>(Client.dwBase + m_dwForceAttack, 4);
		if (!triggerBurst) {
			Sleep(triggerDelayEnd);
		}
	}
}


void TriggerBurst() {
	for (int b = 0; b < triggerBurstBullets; b++) {
		if (b == 0) {
			if (!triggerDelayRand) {
				Sleep(triggerDelay);
			}
			if (triggerDelayRand) {
				Sleep(rand() % (triggerDelayTo - (triggerDelayFrom - 1)) + (triggerDelayFrom));
			}
			TriggerShot();
			Sleep(triggerDelayBurst);

		}
		if (b != 0 && b != triggerBurstBullets - 1) {
			TriggerShot();
			Sleep(triggerDelayBurst);

		}
		if (b == triggerBurstBullets - 1) {
			TriggerShot();
			Sleep(triggerDelayEnd);
		}
	}
}







void Trigger() {
	if (!Misc.IsAttacking()) {
		if (Settings.Trigger.dash && Misc.GetSpeed(local) <= DashSpeed(local) || !Settings.Trigger.dash) {
			int inCross = Mem.Read<int>(LocalBase + m_iCrossHairID);
			DWORD TEntity = Mem.Read<DWORD>(Client.dwBase + m_dwEntityList + ((inCross - 1) * 16));
			int TTeamID = Mem.Read<int>(TEntity + m_iTeamNum);
			if (triggerGod) TGodMode = Mem.Read<bool>(TEntity + m_bGunGameImmunity);
			if (weaponIsShootable()) {
				if (TTeamID != myTeam && TTeamID != 0 && inCross > 0 && inCross <= 64) {
					if (triggerGod && !TGodMode || !triggerGod) {
						if (!triggerKey) {
							if (triggerBurst) {
								TriggerBurst();
							}
							if (!triggerBurst) {
								TriggerShot();
							}
						}
						if (triggerKey) {
							if (GetAsyncKeyState(keyTriggerHold) & Pressed) {
								if (triggerBurst) {
									TriggerBurst();
								}
								if (!triggerBurst) {
									TriggerShot();
								}
							}
						}
					}
				}
			}
		}
	Sleep(1);
	}
	//return NULL;
}
*/


float CTrigger::DashSpeed() {

	if (Misc.CanJump(Misc.GetFlags(Offsets.LocalBase), true)) {
		if (Misc.IsZooming(Offsets.LocalBase)) {
			switch (Misc.GetCurrentWeapon(Offsets.LocalBase)) {
			case WEAPON_SSG08:
				return 78.2f;
			case WEAPON_SG553:
			case WEAPON_AUG:
				return 51.f;
			case WEAPON_G3SG1:
			case WEAPON_SCAR20:
				return 40.8f;
			case WEAPON_AWP:
				return 34.0f;
			default:
				return 34.0f;
			}
		}
		else {
			switch (Misc.GetCurrentWeapon(Offsets.LocalBase)) {
			case WEAPON_GLOCK:
			case WEAPON_P2000:
			case WEAPON_USPS:
			case WEAPON_ELITE:
			case WEAPON_P250:
			case WEAPON_FIVESEVEN:
			case WEAPON_TEC9:
			case WEAPON_CZ75:
			case WEAPON_MAC10:
			case WEAPON_MP9:
			case WEAPON_BIZON:
				return 81.6f;
			case WEAPON_MP5SD:
				return 79.9f;
			case WEAPON_DEAGLE:
			case WEAPON_UMP45:
			case WEAPON_P90:
			case WEAPON_SSG08:
				return 78.2f;
			case WEAPON_MAG7:
			case WEAPON_M4A4:
			case WEAPON_M4A1S:
				return 76.5f;
			case WEAPON_REVOLVER:
			case WEAPON_NOVA:
			case WEAPON_MP7:
			case WEAPON_FAMAS:
				return 74.8f;
			case WEAPON_G3SG1:
			case WEAPON_SCAR20:
			case WEAPON_XM1014:
			case WEAPON_GALIL:
			case WEAPON_AK47:
				return 73.1f;
			case WEAPON_SAWEDOFF:
			case WEAPON_AUG:
			case WEAPON_SG553:
				return 71.4f;
			case WEAPON_AWP:
				return 68.0f;
			case WEAPON_M249:
				return 66.3f;
			case WEAPON_NEGEV:
				return 51.0f;
			default:
				return 51.0f;
			}
		}
	}
	else return 34.0f;
}
