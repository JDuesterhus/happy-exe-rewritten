#include "Visuals.h"

CVisuals Visuals;

/* GLOW ESP AND RADAR */
void CVisuals::Glow() {
	int ObjectCount = Memory::Read<int>(Offsets.dwClient + Offsets.dwGlowObjectManager + 0xC); //0x4 all ent, 0xC current ent
	for (int i = 0; i <= ObjectCount; i++) {
		int GlowManager = Memory::Read<int>(Offsets.dwClient + Offsets.dwGlowObjectManager);
		DWORD pEntity = GlowManager + i * sizeof(csGlowEnt);
		sGlowEnt = Memory::Read<csGlowEnt>(GlowManager + i * sizeof(csGlowEnt));

		//ignore if dwBase is invalid
		if (sGlowEnt.dwBase == 0)
			continue;
		//ignore if dwBase is local player
		if (sGlowEnt.dwBase == Offsets.LocalBase)
			continue;

		int classID = GetClassID(sGlowEnt.dwBase);
		if (classID != CCSPlayer && !EntityIsPistol(classID) && !EntityIsSMG(classID) && !EntityIsShotgun(classID) && !EntityIsRifle(classID) && !EntityIsSniper(classID) && !EntityIsGrenade(classID) && !EntityIsBomb(classID) && !EntityIsOther(classID))
			continue;

		if (classID == CCSPlayer) {
			bool entityDormant = Memory::Read<bool>(sGlowEnt.dwBase + Offsets.m_bDormant);
			if (entityDormant)
				continue;

			int8_t entityLifeState = Memory::Read<int8_t>(sGlowEnt.dwBase + Offsets.m_lifeState);
			if (entityLifeState != LIFE_ALIVE)
				continue;

			int entityHealth = Memory::Read<int>(sGlowEnt.dwBase + Offsets.m_iHealth);
			if (entityHealth < 1)
				continue;

			bool entityGod = Memory::Read<bool>(sGlowEnt.dwBase + Offsets.m_bGunGameImmunity);
			if (entityGod)
				Memory::Write<bool>(sGlowEnt.dwBase + Offsets.m_bGunGameImmunity, false);

			int entityTeam = Memory::Read<int>(sGlowEnt.dwBase + Offsets.m_iTeamNum);
			int localTeam = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iTeamNum);

			/* INGAME RADAR */
			if (Settings.Misc.Radar) {
				bool entitySpotted = Memory::Read<bool>(sGlowEnt.dwBase + Offsets.m_bSpotted);
				if (!entitySpotted && entityTeam != localTeam) {
					Memory::Write<bool>(sGlowEnt.dwBase + Offsets.m_bSpotted, true);
				}
			}
			/* PLAYER GLOW */
			if (Settings.ESP.Glow) {
				float R, G, B;
				if (entityTeam == localTeam) {
					R = Settings.Color.Glow_Ally_R;
					G = Settings.Color.Glow_Ally_G;
					B = Settings.Color.Glow_Ally_B;
				}
				if (entityTeam != localTeam) {
					R = Settings.Color.Glow_Enemy_R;
					G = Settings.Color.Glow_Enemy_G;
					B = Settings.Color.Glow_Enemy_B;
				}
				//DEFAULT TERRORIST/COUNTER-TERRORIST COLOR
				if (Settings.ESP.Glow_Custom_Color == 0) {
					//TERRORIST
					if (entityTeam == 2) {
						R = 118.00f;
						G = 92.00f;
						B = 45.00f;
					}
					//COUNTER-TERRORIST
					if (entityTeam == 3) {
						R = 59.00f;
						G = 81.00f;
						B = 115.00f;
					}
				}
				//ENEMY/ALLY CONFIG COLOR
				if (Settings.ESP.Glow_Custom_Color == 1) {
					//ALLY
					if (entityTeam == localTeam) {
						R = Settings.Color.Glow_Ally_R;
						G = Settings.Color.Glow_Ally_G;
						B = Settings.Color.Glow_Ally_B;
					}
					//ENEMY
					if (entityTeam != localTeam) {
						R = Settings.Color.Glow_Enemy_R;
						G = Settings.Color.Glow_Enemy_G;
						B = Settings.Color.Glow_Enemy_B;
					}
				}
				//TERRORIST/COUNTER-TERRORIST CONFIG COLOR
				if (Settings.ESP.Glow_Custom_Color == 2) {
					//TERRORIST
					if (entityTeam == 2) {
						R = Settings.Color.Glow_Terrorist_R;
						G = Settings.Color.Glow_Terrorist_G;
						B = Settings.Color.Glow_Terrorist_B;
					}
					//COUNTER-TERRORIST
					if (entityTeam == 3) {
						R = Settings.Color.Glow_CounterTerrorist_R;
						G = Settings.Color.Glow_CounterTerrorist_G;
						B = Settings.Color.Glow_CounterTerrorist_B;
					}
				}
				//HEALTH BASED COLOR
				if (Settings.ESP.Glow_Custom_Color >= 3 && Settings.ESP.Glow_Custom_Color <= 5) {
					if (entityTeam != localTeam && Settings.ESP.Glow_Custom_Color == 3 || entityTeam == localTeam && Settings.ESP.Glow_Custom_Color == 4 || Settings.ESP.Glow_Custom_Color == 5) {
						G = entityHealth / 100.f * 255.f;
						R = 255.f - G;
						B = 0.f;
					}
				}
				//COMPETETIVE TEAM COLOR
				if (Settings.ESP.Glow_Custom_Color >= 6 && Settings.ESP.Glow_Custom_Color <= 8) {
					if (entityTeam != localTeam && Settings.ESP.Glow_Custom_Color == 6 || entityTeam == localTeam && Settings.ESP.Glow_Custom_Color == 7 || Settings.ESP.Glow_Custom_Color == 8) {
						//DWORD PlayerResource = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwPlayerResource);
						//int entityColor = Memory::Read<int>(sGlowEnt.dwBase + 0x2D74);
						//std::cout << "entityColor: " << entityColor << std::endl;
					}
				}
				//RGB FADE COLOR
				if (Settings.ESP.Glow_Custom_Color >= 9 && Settings.ESP.Glow_Custom_Color <= 11) {
					if (entityTeam != localTeam && Settings.ESP.Glow_Custom_Color == 9 || entityTeam == localTeam && Settings.ESP.Glow_Custom_Color == 10 || Settings.ESP.Glow_Custom_Color == 11) {
						static float red = 255;
						static float green = 0;
						static float blue = 0;
						if (red > 0 && blue == 0) {
							red -= 5;
							green += 5;
						}
						if (green > 0 && red == 0) {
							green -= 5;
							blue += 5;
						}
						if (blue > 0 && green == 0) {
							red += 5;
							blue -= 5;
						}
						R = red;
						G = green;
						B = blue;
					}
				}
				if (Settings.ESP.Glow_Custom_Color >= 12 && Settings.ESP.Glow_Custom_Color <= 14) {
					if (entityTeam != localTeam && Settings.ESP.Glow_Custom_Color == 12 || entityTeam == localTeam && Settings.ESP.Glow_Custom_Color == 13 || Settings.ESP.Glow_Custom_Color == 14) {
						R = (rand() % 255 + 0);
						int rest = 255 - R;
						G = (rand() % rest + 0);
						rest = 255 - (G + R);
						B = rest;
					}
				}
				if (entityTeam != localTeam && Settings.ESP.Glow_Enemy) {
					if (Settings.ESP.Glow_Highlight_God) {
						float entityGodTime = Memory::Read<float>(sGlowEnt.dwBase + Offsets.m_bGunGameImmunity - 0x8);
						if (entityGodTime > 0) {
							R = Settings.Color.Glow_Highlight_God_R;
							G = Settings.Color.Glow_Highlight_God_G;
							B = Settings.Color.Glow_Highlight_God_B;
						}

					}
					if (Settings.ESP.Glow_Highlight_Scoped) {
						bool entityScoped = Memory::Read<bool>(sGlowEnt.dwBase + Offsets.m_bIsScoped);
						if (entityScoped && Misc.WeaponIsSniper(Misc.GetCurrentWeapon(sGlowEnt.dwBase))) {
							R = Settings.Color.Glow_Highlight_Scoped_R;
							G = Settings.Color.Glow_Highlight_Scoped_G;
							B = Settings.Color.Glow_Highlight_Scoped_B;
						}

					}
					if (Settings.ESP.Glow_Highlight_Flashed) {
						float entityFlashTime = Memory::Read<float>(sGlowEnt.dwBase + Offsets.m_flFlashMaxAlpha - 0x8);
						if (entityFlashTime == 255) {
							R = Settings.Color.Glow_Highlight_Flashed_R;
							G = Settings.Color.Glow_Highlight_Flashed_G;
							B = Settings.Color.Glow_Highlight_Flashed_B;
						}
					}
					if (Settings.ESP.Glow_Highlight_Defuser) {
						bool entityDefusing = Memory::Read<bool>(sGlowEnt.dwBase + Offsets.m_bIsDefusing);
						bool entityGrabbingHostage = Memory::Read<bool>(sGlowEnt.dwBase + Offsets.m_bIsGrabbingHostage);
						if (entityDefusing || entityGrabbingHostage) {
							R = Settings.Color.Glow_Highlight_Defuser_R;
							G = Settings.Color.Glow_Highlight_Defuser_G;
							B = Settings.Color.Glow_Highlight_Defuser_B;
						}
					}
					if (Settings.ESP.Glow_Highlight_Planter) {
						DWORD weaponEntity = Misc.GetWeaponEntity(sGlowEnt.dwBase);
						int weaponID = Misc.GetCurrentWeapon(sGlowEnt.dwBase);
						if (weaponID == WEAPON_C4) {
							bool entityPlanting = Memory::Read<bool>(weaponEntity + 0x33D0); //m_bStartedArming
							if (entityPlanting) {
								R = Settings.Color.Glow_Highlight_Planter_R;
								G = Settings.Color.Glow_Highlight_Planter_G;
								B = Settings.Color.Glow_Highlight_Planter_B;
							}
						}
					}
				}

				//std::cout << "glowing player..." << std::endl;
				if (entityTeam == localTeam && Settings.ESP.Glow_Ally || entityTeam != localTeam && Settings.ESP.Glow_Enemy)
				GlowEntity(pEntity, R, G, B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
			}

		}
		//ignore if is already glowing
		if (sGlowEnt.m_bRenderWhenOccluded == true)
			continue;

		//BOMB RADAR
		if (Settings.Misc.Radar && EntityIsBomb(classID)) {
			Memory::Write<bool>(sGlowEnt.dwBase + Offsets.m_bSpotted, true);
		}

		if (Settings.ESP.Glow && Settings.ESP.Glow_Item) {
			/* PISTOL GLOW */
			if (EntityIsPistol(classID) && Settings.ESP.Glow_Item_Pistol) {
				GlowEntity(pEntity, Settings.Color.Glow_Item_Weapon_R, Settings.Color.Glow_Item_Weapon_G, Settings.Color.Glow_Item_Weapon_B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
				//std::cout << "glowing pistol..." << std::endl;
			}
			/* SMG GLOW */
			if (EntityIsSMG(classID) && Settings.ESP.Glow_Item_SMG) {
				GlowEntity(pEntity, Settings.Color.Glow_Item_Weapon_R, Settings.Color.Glow_Item_Weapon_G, Settings.Color.Glow_Item_Weapon_B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
				//std::cout << "glowing smg..." << std::endl;
			}
			/* SHOTGUN GLOW */
			if (EntityIsShotgun(classID) && Settings.ESP.Glow_Item_Shotgun) {
				GlowEntity(pEntity, Settings.Color.Glow_Item_Weapon_R, Settings.Color.Glow_Item_Weapon_G, Settings.Color.Glow_Item_Weapon_B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
				//std::cout << "glowing shotgun..." << std::endl;
			}
			/* RIFLE GLOW */
			if (EntityIsRifle(classID) && Settings.ESP.Glow_Item_Rifle) {
				GlowEntity(pEntity, Settings.Color.Glow_Item_Weapon_R, Settings.Color.Glow_Item_Weapon_G, Settings.Color.Glow_Item_Weapon_B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
				//std::cout << "glowing rifle..." << std::endl;
			}
			/* SNIPER GLOW */
			if (EntityIsSniper(classID) && Settings.ESP.Glow_Item_Sniper) {
				GlowEntity(pEntity, Settings.Color.Glow_Item_Weapon_R, Settings.Color.Glow_Item_Weapon_G, Settings.Color.Glow_Item_Weapon_B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
				//std::cout << "glowing sniper..." << std::endl;
			}
			/* GRENADE GLOW */
			if (EntityIsGrenade(classID) && Settings.ESP.Glow_Item_Grenade) {
				GlowEntity(pEntity, Settings.Color.Glow_Item_Grenade_R, Settings.Color.Glow_Item_Grenade_G, Settings.Color.Glow_Item_Grenade_B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
				//std::cout << "glowing greande..." << std::endl;
			}
			/* BOMB GLOW */
			if (EntityIsBomb(classID) && Settings.ESP.Glow_Item_Bomb) {
				GlowEntity(pEntity, Settings.Color.Glow_Item_Bomb_R, Settings.Color.Glow_Item_Bomb_G, Settings.Color.Glow_Item_Bomb_B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
				//std::cout << "glowing bomb..." << std::endl;
			}
			/* OTHER GLOW */
			if (EntityIsOther(classID) && Settings.ESP.Glow_Item_Other) {
				GlowEntity(pEntity, Settings.Color.Glow_Item_Other_R, Settings.Color.Glow_Item_Other_G, Settings.Color.Glow_Item_Other_B, Settings.ESP.Glow_Alpha, Settings.ESP.Glow_Style);
				//std::cout << "glowing other..." << std::endl;
			}
		}
	}
}



void CVisuals::Chams() {
	int ObjectCount = Memory::Read<int>(Offsets.dwClient + Offsets.dwEntityList + 0x20018) + 128; //0x4 all ent, 0xC current ent, 0x20018 ???
	for (int i = 0; i <= ObjectCount; i++) {
		DWORD EntityList = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwEntityList + i * 0x10);
		if (EntityList == 0)
			continue;

		int classID = GetClassID(EntityList);
		if (classID != CCSPlayer && classID != CPredictedViewModel && classID != CBaseViewModel)
			continue;

		/* PLAYER CHAMS */
		BYTE RGBfix = (Settings.ESP.Chams_Alpha == 0) ? 255 : (BYTE)(255.f / ((Settings.ESP.Chams_Alpha / 30 + 2) - 6));
		if (classID == CCSPlayer) {
			int entityTeam = Memory::Read<int>(EntityList + Offsets.m_iTeamNum);
			int localTeam = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iTeamNum);

			int entityHealth = Memory::Read<int>(EntityList + Offsets.m_iHealth);
			if (entityHealth < 1)
				continue;

			float R, G, B;
			if (entityTeam == localTeam) {
				R = Settings.Color.Chams_Ally_R;
				G = Settings.Color.Chams_Ally_G;
				B = Settings.Color.Chams_Ally_B;
			}
			if (entityTeam != localTeam) {
				R = Settings.Color.Chams_Enemy_R;
				G = Settings.Color.Chams_Enemy_G;
				B = Settings.Color.Chams_Enemy_B;
			}
			//DEFAULT TERRORIST/COUNTER-TERRORIST COLOR
			if (Settings.ESP.Chams_Custom_Color == 0) {
				//TERRORIST
				if (entityTeam == 2) {
					R = 118.00f;
					G = 92.00f;
					B = 45.00f;
				}
				//COUNTER-TERRORIST
				if (entityTeam == 3) {
					R = 59.00f;
					G = 81.00f;
					B = 115.00f;
				}
			}
			//ENEMY/ALLY CONFIG COLOR
			if (Settings.ESP.Chams_Custom_Color == 1) {
				//ALLY
				if (entityTeam == localTeam) {
					R = Settings.Color.Chams_Ally_R;
					G = Settings.Color.Chams_Ally_G;
					B = Settings.Color.Chams_Ally_B;
				}
				//ENEMY
				if (entityTeam != localTeam) {
					R = Settings.Color.Chams_Enemy_R;
					G = Settings.Color.Chams_Enemy_G;
					B = Settings.Color.Chams_Enemy_B;
				}
			}
			//TERRORIST/COUNTER-TERRORIST CONFIG COLOR
			if (Settings.ESP.Chams_Custom_Color == 2) {
				//TERRORIST
				if (entityTeam == 2) {
					R = Settings.Color.Chams_Terrorist_R;
					G = Settings.Color.Chams_Terrorist_G;
					B = Settings.Color.Chams_Terrorist_B;
				}
				//COUNTER-TERRORIST
				if (entityTeam == 3) {
					R = Settings.Color.Chams_CounterTerrorist_R;
					G = Settings.Color.Chams_CounterTerrorist_G;
					B = Settings.Color.Chams_CounterTerrorist_B;
				}
			}
			//HEALTH BASED COLOR
			if (Settings.ESP.Chams_Custom_Color >= 3 && Settings.ESP.Chams_Custom_Color <= 5) {
				if (entityTeam != localTeam && Settings.ESP.Chams_Custom_Color == 3 || entityTeam == localTeam && Settings.ESP.Chams_Custom_Color == 4 || Settings.ESP.Chams_Custom_Color == 5) {
					G = entityHealth / 100.f * 255.f;
					R = 255.f - G;
					B = 0.f;
				}
			}
			//COMPETETIVE TEAM COLOR
			if (Settings.ESP.Chams_Custom_Color >= 6 && Settings.ESP.Chams_Custom_Color <= 8) {
				if (entityTeam != localTeam && Settings.ESP.Chams_Custom_Color == 6 || entityTeam == localTeam && Settings.ESP.Chams_Custom_Color == 7 || Settings.ESP.Chams_Custom_Color == 8) {
					//DWORD PlayerResource = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwPlayerResource);
					//int entityColor = Memory::Read<int>(sGlowEnt.dwBase + 0x2D74);
					//std::cout << "entityColor: " << entityColor << std::endl;
				}
			}
			//RGB FADE COLOR
			if (Settings.ESP.Chams_Custom_Color >= 9 && Settings.ESP.Chams_Custom_Color <= 11) {
				if (entityTeam != localTeam && Settings.ESP.Chams_Custom_Color == 9 || entityTeam == localTeam && Settings.ESP.Chams_Custom_Color == 10 || Settings.ESP.Chams_Custom_Color == 11) {
					static float red = 255;
					static float green = 0;
					static float blue = 0;
					if (red > 0 && blue == 0) {
						red -= 5;
						green += 5;
					}
					if (green > 0 && red == 0) {
						green -= 5;
						blue += 5;
					}
					if (blue > 0 && green == 0) {
						red += 5;
						blue -= 5;
					}
					R = red;
					G = green;
					B = blue;
				}
			}
			if (Settings.ESP.Chams_Custom_Color >= 12 && Settings.ESP.Chams_Custom_Color <= 14) {
				if (entityTeam != localTeam && Settings.ESP.Chams_Custom_Color == 12 || entityTeam == localTeam && Settings.ESP.Chams_Custom_Color == 13 || Settings.ESP.Chams_Custom_Color == 14) {
					R = (rand() % 255 + 0);
					int rest = 255 - R;
					G = (rand() % rest + 0);
					rest = 255 - (G + R);
					B = rest;
				}
			}


			if (entityTeam != localTeam && Settings.ESP.Chams_Enemy) {
				if (Settings.ESP.Chams_Highlight_God) {
					float entityGodTime = Memory::Read<float>(EntityList + Offsets.m_bGunGameImmunity - 0x8);
					if (entityGodTime > 0) {
						R = Settings.Color.Chams_Highlight_God_R;
						G = Settings.Color.Chams_Highlight_God_G;
						B = Settings.Color.Chams_Highlight_God_B;
					}

				}
				if (Settings.ESP.Chams_Highlight_Scoped) {
					bool entityScoped = Memory::Read<bool>(EntityList + Offsets.m_bIsScoped);
					if (entityScoped && Misc.WeaponIsSniper(Misc.GetCurrentWeapon(EntityList))) {
						R = Settings.Color.Chams_Highlight_Scoped_R;
						G = Settings.Color.Chams_Highlight_Scoped_G;
						B = Settings.Color.Chams_Highlight_Scoped_B;
					}

				}
				if (Settings.ESP.Chams_Highlight_Flashed) {
					float entityFlashTime = Memory::Read<float>(EntityList + Offsets.m_flFlashMaxAlpha - 0x8);
					if (entityFlashTime == 255) {
						R = Settings.Color.Chams_Highlight_Flashed_R;
						G = Settings.Color.Chams_Highlight_Flashed_G;
						B = Settings.Color.Chams_Highlight_Flashed_B;
					}
				}
				if (Settings.ESP.Chams_Highlight_Defuser) {
					bool entityDefusing = Memory::Read<bool>(EntityList + Offsets.m_bIsDefusing);
					bool entityGrabbingHostage = Memory::Read<bool>(EntityList + Offsets.m_bIsGrabbingHostage);
					if (entityDefusing || entityGrabbingHostage) {
						R = Settings.Color.Chams_Highlight_Defuser_R;
						G = Settings.Color.Chams_Highlight_Defuser_G;
						B = Settings.Color.Chams_Highlight_Defuser_B;
					}
				}
				if (Settings.ESP.Chams_Highlight_Planter) {
					int weaponID = Misc.GetCurrentWeapon(EntityList);
					if (weaponID == WEAPON_C4) {
						DWORD weaponEntity = Misc.GetWeaponEntity(EntityList);
						bool entityPlanting = Memory::Read<bool>(weaponEntity + 0x33D0); //m_bStartedArming
						if (entityPlanting) {
							R = Settings.Color.Chams_Highlight_Planter_R;
							G = Settings.Color.Chams_Highlight_Planter_G;
							B = Settings.Color.Chams_Highlight_Planter_B;
						}
					}
				}
			}





			/* ALLY CHAMS */
			if (entityTeam == localTeam && Settings.ESP.Chams_Ally) {
				DyeEntity(EntityList, R, G, B);
			}
			if (entityTeam == localTeam && !Settings.ESP.Chams_Ally) {
				DyeEntity(EntityList, RGBfix, RGBfix, RGBfix);
			}
			/* ENEMY CHAMS */
			if (entityTeam != localTeam && Settings.ESP.Chams_Enemy) {
				DyeEntity(EntityList, R, G, B);
			}
			if (entityTeam != localTeam && !Settings.ESP.Chams_Enemy) {
				DyeEntity(EntityList, RGBfix, RGBfix, RGBfix);
			}
		}
		// VMODEL CHAMS
		if (classID == CPredictedViewModel || classID == CBaseViewModel) {
			if (Settings.ESP.Chams_Viewmodel) {
				DyeEntity(EntityList, Settings.Color.Chams_Viewmodel_R, Settings.Color.Chams_Viewmodel_G, Settings.Color.Chams_Viewmodel_B);
			}
			if (!Settings.ESP.Chams_Viewmodel) {
				DyeEntity(EntityList, RGBfix, RGBfix, RGBfix);
			}
		}
		// CHAMS ALPHA
		if (EntityList == Offsets.LocalBase) {
			float A = Settings.ESP.Chams_Alpha / 5;
			DWORD thisPtr = (int)(Offsets.dwEngine + Offsets.model_ambient_min - 0x2c);
			DWORD xored = *(DWORD*)&A ^ thisPtr;
			Memory::Write<DWORD>(Offsets.dwEngine + Offsets.model_ambient_min, xored);
		}
	}
	/*
	// misc model fix
	if (classID == CDynamicProp || classID == CCSRagdoll) {
	DyeEntity(EntityList, RGBfix, RGBfix, RGBfix);
	}
	*/
}

void CVisuals::Others() {
	int ObjectCount = Memory::Read<int>(Offsets.dwClient + Offsets.dwEntityList + 0x20018) + 128; //0x4 all ent, 0xC current ent, 0x20018 ??
	//std::cout << "ObjectCount " << ObjectCount << std::endl;
	for (int i = 0; i <= ObjectCount; i++) {
		DWORD EntityList = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwEntityList + i * 0x10);
		//if (EntityList == 0)
		//	continue;

		int classID = GetClassID(EntityList);
		if (classID != CCSPlayer && classID != CCSRagdoll && classID != CRagdollProp && classID != CRagdollPropAttached && classID != CSmokeGrenadeProjectile && classID != CFogController && classID != CPlantedC4)
			continue;

		//if (classID == CCSPlayer) {
		//	static int TotalDMG; 
		//	TotalDMG = Memory::Read<int>(Offsets.LocalBase + 0x3944); //m_unTotalRoundDamageDealt
		//	static int TotalDMGBefore = TotalDMG;
		//	//std::cout << "damage: " << TotalDMG << std::endl;
		//	//Memory::Write<bool>(Offsets.LocalBase + 0xA379, false); //m_bNightVisionOn
		//	std::cout << "TotalDMG " << TotalDMG << std::endl;
		//	std::cout << "TotalDMGBefore" << TotalDMGBefore << std::endl;
		//	if (TotalDMG > TotalDMGBefore && TotalDMG < 1000000000) {
		//		static int TotalHS, TotalHSBefore;
		//		TotalHS = Memory::Read<int>(Offsets.LocalBase + 0x3940); //m_iNumRoundKillsHeadshots
		//		if (TotalHS > TotalHSBefore && TotalHS < 1000000000) {
		//			std::cout << "TotalHS " << TotalHS << std::endl;
		//			std::cout << "TotalHSBefore" << TotalHSBefore << std::endl;
		//			std::cout << "headshot" << std::endl;
		//			PlaySound(MAKEINTRESOURCE(IDR_SOUND_HEADSHOT1), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
		//			TotalHSBefore = TotalHS;
		//		}
		//		else {
		//			std::cout << "hit" << std::endl;
		//			PlaySound(MAKEINTRESOURCE(IDR_SOUND_HITMARKER1), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
		//		}
		//		//Memory::Write<bool>(Offsets.LocalBase + 0xA379, true);
		//		//Sleep(100);
		//		TotalDMGBefore = TotalDMG;
		//	}
		//	//Sleep(10000);
		//}
		//struct EntityInfo {
		//	DWORD Base[65];
		//	bool Dormant[65];
		//	int8_t LifeState[65];
		//	int Spectating[65];
		//	int SpectatingOld[65];
		//}; EntityInfo Ent;
		//
		//
		//bool spectatorlist = true;
		//
		//
		//if (spectatorlist) {
		//	if (classID == CCSPlayer) {
		//		if (EntityList != Offsets.LocalBase && EntityList != 0) {
		//			//int LocalSpec = Memory::Read<int>(Offsets.LocalBase + Offsets.m_hObserverTarget) & 0xFFF;
		//
		//			int LocalIndex = Memory::Read<int>(Offsets.LocalBase + 0x64);
		//			int EntIndex = Memory::Read<int>(EntityList + 0x64);
		//			Ent.Dormant[EntIndex] = Memory::Read<int>(EntityList + Offsets.m_bDormant);
		//			Ent.LifeState[EntIndex] = Memory::Read<int8_t>(EntityList + Offsets.m_lifeState);
		//			if (Ent.Dormant[EntIndex] && Ent.LifeState[EntIndex] != LIFE_ALIVE) {
		//				Ent.Spectating[EntIndex] = Memory::Read<int>(EntityList + Offsets.m_hObserverTarget) & 0xFFF;
		//				if (Ent.Spectating[EntIndex] != 4095) {
		//					if (Ent.Spectating[EntIndex] == LocalIndex) {
		//						std::cout << "youre being observed by " << EntIndex << std::endl;
		//					}
		//					if (Ent.Spectating[EntIndex] != LocalIndex) {
		//						std::cout << "youre no longer observed by " << EntIndex << std::endl;
		//					}
		//					Ent.SpectatingOld[EntIndex] = Ent.Spectating[EntIndex];
		//				}
		//			}
		//			else {
		//				if (Ent.Spectating[EntIndex] != LocalIndex) {
		//					std::cout << "youre no longer observed by " << EntIndex << std::endl;
		//				}
		//			}
		//
		//			//std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
		//			//std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
		//			//std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
		//			//std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
		//			//std::cout << "LocalEnt: " << Offsets.LocalBase << std::endl;
		//			//std::cout << "LocalSpec: " << LocalSpec << std::endl;
		//			//std::cout << "LocalID: " << LocalIndex << std::endl;
		//			//std::cout << std::endl;
		//			//std::cout << std::endl;
		//			//std::cout << "EntEnt: " << EntityList << std::endl;
		//			//std::cout << "EntSpec: " << EntSpec << std::endl;
		//			//std::cout << "EntID: " << EntIndex << std::endl;
		//			Sleep(50);
		//		}
		//	}
		//}

		if (Settings.Misc.Overwrite_FOV) {
			if (EntityList == Offsets.LocalBase) {
				//bool LocalInZoom = Memory::Read<bool>(Offsets.LocalBase + Offsets.m_bIsScoped);
				//int LocalFov = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iFOV);
				int LocalFovDefault = Memory::Read<int>(Offsets.LocalBase + (Offsets.m_iFOV + 0x148));
				if (LocalFovDefault != Settings.Misc.Overwrite_FOV_Custom) {
					Memory::Write<int>(Offsets.LocalBase + 0x332C, Settings.Misc.Overwrite_FOV_Custom);
				}
				//if (!LocalInZoom && LocalFov != 0 && LocalFov != Settings.Misc.Overwrite_FOV_Custom) {
				//	LocalInZoom = Memory::Read<bool>(Offsets.LocalBase + Offsets.m_bIsScoped);
				//	LocalFov = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iFOV);
				//	Memory::Write<int>(Offsets.LocalBase + Offsets.m_iFOV, Settings.Misc.Overwrite_FOV_Custom);
				//	Memory::Write<int>(Offsets.LocalBase + Offsets.m_iFOVStart, Settings.Misc.Overwrite_FOV_Custom);
				//}
			}
		}
		//NO HAND
		if (Settings.Misc.Remove_Hands) {
			if (EntityList == Offsets.LocalBase) {
				DWORD GameRules = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwGameRulesProxy);
				int GameType = Memory::Read<int>(GameRules + Offsets.m_SurvivalGameRuleDecisionTypes);
				if (GameType != 4) {
					Memory::Write<bool>(EntityList + 0x258, false); //m_nModelIndex
					char nohands[256] = { 0 };
					Memory::Write<char[256]>(EntityList + 3973, nohands);
				}
			}
		}
		
		//NO RAGDOLLS
		if (Settings.Misc.Remove_Ragdoll) {
			if (classID == CCSRagdoll || classID == CRagdollProp || classID == CRagdollPropAttached) {
				Memory::Write<float>(EntityList + Offsets.m_flModelScale, 0);
			}
		}
		//NO SMOKE
		if (Settings.Misc.Remove_Smoke) {
			if (classID == CSmokeGrenadeProjectile) {
				Memory::Write<bool>(EntityList + 0x29E4 + 0xC, true); //m_bDidSmokeEffect
			}
		}
		//NO FOG
		if (Settings.Misc.Remove_Fog) {
			if (classID == CFogController) {
				Memory::Write<bool>(EntityList + 0xA1C, false); //m_fog.enable
			}
		}
		//NO FLASH
		if (Settings.Misc.Reduce_Flash) {
			if (classID == CCSPlayer) {
				if (GetFlashAlpha(EntityList) != Settings.Misc.Reduce_Flash_Alpha) {
					Memory::Write<float>(EntityList + Offsets.m_flFlashMaxAlpha, Settings.Misc.Reduce_Flash_Alpha);
				}
			}
		}
		//NIGHT MODE
		if (Settings.Misc.Nightmode) {
			if (EntityList == Offsets.LocalBase) {
				DWORD tmcIndex = Memory::Read<DWORD>(Offsets.LocalBase + Offsets.m_hTonemapController);
				tmcIndex &= 0xFFF;
				DWORD tmcHandle = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwEntityList + (tmcIndex - 1) * 0x10);;

				float ValueMin, ValueMax;
				static float ValueCustomMin, ValueCustomMax;
				ValueMin = Memory::Read<float>(tmcHandle + Offsets.m_flCustomAutoExposureMin);
				ValueMax = Memory::Read<float>(tmcHandle + Offsets.m_flCustomAutoExposureMax);
				if (ValueMin >= 0 && ValueMin <= 10) {
					if (ValueMax != ValueCustomMax || ValueMin != ValueCustomMin) {
						ValueCustomMin = Settings.Misc.Nightmode_Alpha / (255 / ValueMin);
						ValueCustomMax = Settings.Misc.Nightmode_Alpha / (255 / ValueMax);
						if (ValueCustomMin == 0) ValueCustomMin = ValueCustomMax;
						if (ValueCustomMax == 0) ValueCustomMax = ValueCustomMin;

						Memory::Write<bool>(tmcHandle + Offsets.m_bUseCustomAutoExposureMin, true);
						Memory::Write<bool>(tmcHandle + Offsets.m_bUseCustomAutoExposureMax, true);
						Memory::Write<float>(tmcHandle + Offsets.m_flCustomAutoExposureMin, ValueCustomMin);
						Memory::Write<float>(tmcHandle + Offsets.m_flCustomAutoExposureMax, ValueCustomMax);
					}
				}
			}
		}
		//FLIP KNIFE VMODEL
		if (Settings.Misc.Swap_Knife_Hand) {
			static bool flipped = false;
			if (Misc.WeaponIsKnife(Misc.GetCurrentWeapon(Offsets.LocalBase)) && !flipped) {
				Misc.Console("toggle cl_righthand");
				flipped = true;
			}
			if (!Misc.WeaponIsKnife(Misc.GetCurrentWeapon(Offsets.LocalBase)) && flipped) {
				Misc.Console("toggle cl_righthand");
				flipped = false;
			}
		}


		////THIRDPERSON
		//if (thirdperson) {
		//	static bool once = false;
		//	if (GetAsyncKeyState(VK_MENU) & Pressed) {
		//		Memory::Write<int>(Offsets.LocalBase + Offsets.m_iObserverMode, 1);
		//		once = true;
		//
		//		bool nope = true;
		//		bool yup = false;
		//
		//		float scale = 255;
		//		float min = 10;
		//		float max = 100;
		//		float size = 1;
		//
		//
		//		//WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.LocalBase + Offsets.m_flModelScale), &size, sizeof(size), NULL);
		//		//WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.LocalBase + 0x2FC), &scale, sizeof(scale), NULL);
		//		//WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.LocalBase + 0x2F4), &min, sizeof(min), NULL);
		//		//WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.LocalBase + 0x2F8), &max, sizeof(max), NULL);
		//
		//	}
		//	else if (once) {
		//		Memory::Write<int>(Offsets.LocalBase + Offsets.m_iObserverMode, 0);
		//	}
		//}

		//DWORD m_PlayerFog = 0x37B0;
		//DWORD m_bFogEnable = 0xA1C;
		//
		//DWORD fCtrlIndex, fCtrlHandle;
		//ReadProcessMemory(Offsets.handle, (LPVOID)(Offsets.LocalBase + m_PlayerFog), &fCtrlIndex, sizeof(fCtrlIndex), NULL);
		//fCtrlIndex &= 0xFFF;
		//ReadProcessMemory(Offsets.handle, (LPVOID)(Offsets.Client + Offsets.dwEntityList + (fCtrlIndex - 1) * 0x10), &fCtrlHandle, sizeof(fCtrlHandle), NULL);
		//bool disable = false;
		//WriteProcessMemory(Offsets.handle, (LPVOID)(fCtrlHandle + m_bFogEnable), &disable, sizeof(disable), NULL);

		//Smoke Sphere dust2
		//if (classID == CSmokeGrenadeProjectile) {
		//	float velocity2 = Memory::Read<float>(EntityList + 0x11C);;
		//	//bool smokepopped = true;
		//	//float fade = 1;
		//	//WriteProcessMemory(Offsets.handle, (LPVOID)(EntityList + 0x29E4 + 0x1), &smokepopped, sizeof(smokepopped), NULL); //disable smoke effect
		//	//WriteProcessMemory(Offsets.handle, (LPVOID)(EntityList + 0x2F4), &fade, sizeof(fade), NULL); //hide model
		//	//WriteProcessMemory(Offsets.handle, (LPVOID)(sGlowEnt.dwBase + 0x2F8), &fade, sizeof(fade), NULL);
		//	// GLOW SPHERE IF NOT MOVING
		//	if (velocity2 == 0) {
		//		int item = 419; //531 = football
		//		float size = 19; 
		//
		//		Memory::Write<float>(EntityList + 0x2F4, 1);
		//		Memory::Write<int>(EntityList + 0x258, item);
		//		Memory::Write<float>(EntityList + Offsets.m_flModelScale, 40);
		//	}
		//}
		/*
		//3D fog edit
		if (classID == CCSPlayer) {
		int one = 1;
		float density = 10;
		//WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.LocalBase + 0x3148), &one, sizeof(one), NULL); //enable fog (m_skybox3d.fog.enable)
		//WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.LocalBase + 0x3149), &one, sizeof(one), NULL); //weisser nebel? (m_skybox3d.fog.blend)
		//WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.LocalBase + 0x3130), &density, sizeof(density), NULL); //nebelmenge (m_skybox3d.fog.maxdensity)
		//std::cout << "density : " << density << std::endl;
		}
		*/
	}
}

float round(float f, float prec) {
	return (floor(f*(1.0f / prec) + 0.5) / (1.0f / prec)) + 0.00001;
}

void CVisuals::BombTimer() {
	int ObjectCount = Memory::Read<int>(Offsets.dwClient + Offsets.dwEntityList + 0x20018) + 128;
	for (int i = 0; i <= ObjectCount; i++) {
		DWORD EntityList = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwEntityList + i * 0x10);
		//if (EntityList == 0)
		//	continue;

		int classID = GetClassID(EntityList);
		if (classID != CPlantedC4) 
			continue;

		static bool TimerEnd = true;
		bool BombDefused = Memory::Read<bool>(EntityList + 0x29B0); //m_bBombDefused
		if (BombDefused) {
			TimerEnd = true;
			Misc.Console("cmd2 [Cheeto] Bomb Timer: DEFUSED!;cmd2 [Cheeto] Bomb Timer: DEFUSED!;cmd2 [Cheeto] Bomb Timer: DEFUSED!");
			Sleep(20000);
			continue;
		}
		bool BombTicking = Memory::Read<bool>(EntityList + 0x2980); //m_bBombDefused
		if (!BombTicking) {
			TimerEnd = true;
			continue;
		}

		static float TimerStart = 40;
		static float TimerBefore = 0;

		float BombTimer = Memory::Read<float>(EntityList + 0x2990); //m_flC4Blow
		CGlobalVarsBase var = Memory::Read<CGlobalVarsBase>(Offsets.dwEngine + Offsets.dwGlobalVars);
		float Timer = round(((var.curtime - BombTimer) * -1) - 0.2, 0.2f);

		//std::cout << "BombDefused: " << BombDefused << std::endl;
		//std::cout << "BombTicking: " << BombTicking << std::endl;
		//std::cout << "BombTimer: " << Timer << std::endl;
		//std::cout << "BombTimerEnd: " << TimerEnd << std::endl;
		//std::cout << "BombTimerStart: " << TimerStart << std::endl;

		if (Timer >= TimerBefore && TimerEnd) {
			Misc.Console("developer 1; con_filter_text [Cheeto]; con_filter_enable 2; cmd2 [Cheeto] Bomb Timer Started!");
			TimerStart = Timer;
			TimerEnd = false;
		}
		if (Timer != TimerBefore) {
			if (Timer > 0 && Timer <= TimerStart) {
				char bombalert[200];
				sprintf(bombalert, "cmd2 [Cheeto] Bomb Timer: %.1f", Timer); //cool formatting
				Misc.Console(bombalert);
			}
			if (Timer <= 0) {
				TimerEnd = true;
				Sleep(200);
				Misc.Console("cmd2 [Cheeto] Bomb Timer: B00M!;cmd2 [Cheeto] Bomb Timer: B00M!;cmd2 [Cheeto] Bomb Timer: B00M!");
				Sleep(20000);
			}
		}
		TimerBefore = Timer;
	}
	Sleep(190);
}



float CVisuals::GetFlashAlpha(DWORD base) {
	float FlashAlpha = Memory::Read<float>(base + Offsets.m_flFlashMaxAlpha);
	return FlashAlpha;
}

int CVisuals::GetClassID(DWORD Entity) {
	DWORD ClientNetworkable = Memory::Read<DWORD>(Entity + 0x8);
	DWORD GetClientClassFn = Memory::Read<DWORD>(ClientNetworkable + 2 * 0x4);
	DWORD EntityClientClass = Memory::Read<DWORD>(GetClientClassFn + 1);
	int ClassID = Memory::Read<int>(EntityClientClass + 20);
	return ClassID;
}

void CVisuals::GlowEntity(DWORD Entity, float r, float g, float b, float a, int style) {
	sGlowEnt = Memory::Read<csGlowEnt>(Entity); //might fix the crash problem
	sGlowEnt.r = r / 500;
	sGlowEnt.g = g / 500;
	sGlowEnt.b = b / 500;
	sGlowEnt.m_flGlowAlpha = a / 100;
	sGlowEnt.m_bRenderWhenOccluded = true;
	sGlowEnt.m_bRenderWhenUnoccluded = false;
	sGlowEnt.m_nGlowStyle = style;
	Memory::Write<csGlowEnt>(Entity, sGlowEnt);
}

void CVisuals::DyeEntity(DWORD Entity, BYTE r, BYTE g, BYTE b) {
	Memory::Write<BYTE>(Entity + Offsets.m_clrRender, r);
	Memory::Write<BYTE>(Entity + Offsets.m_clrRender + 0x1, g);
	Memory::Write<BYTE>(Entity + Offsets.m_clrRender + 0x2, b);
}

bool CVisuals::EntityIsPistol(int id) {
	switch (id) {
	case CDEagle:
	case CWeaponElite:
	case CWeaponFiveSeven:
	case CWeaponGlock:
	case CWeaponHKP2000:
	case CWeaponP250:
	case CWeaponTec9:
	case CWeaponUSP:
		return true;
	default:
		return false;
	}
}

bool CVisuals::EntityIsSMG(int id) {
	switch (id) {
	case CWeaponBizon:
	case CWeaponMAC10:
	case CWeaponMP5Navy:
	case CWeaponMP7:
	case CWeaponMP9:
	case CWeaponP90:
	case CWeaponUMP45:
		return true;
	default:
		return false;
	}
}

bool CVisuals::EntityIsShotgun(int id) {
	switch (id) {
	case CWeaponMag7:
	case CWeaponNOVA:
	case CWeaponSawedoff:
	case CWeaponXM1014:
		return true;
	default:
		return false;
	}
}

bool CVisuals::EntityIsRifle(int id) {
	switch (id) {
	case CAK47:
	case CWeaponAug:
	case CWeaponFamas:
	case CWeaponGalilAR:
	case CWeaponM249:
	case CWeaponM4A1:
	case CWeaponNegev:
	case CWeaponSG556:
		return true;
	default:
		return false;
	}
}

bool CVisuals::EntityIsSniper(int id) {
	switch (id) {
	case CWeaponAWP:
	case CWeaponG3SG1:
	case CWeaponSCAR20:
	case CWeaponSSG08:
		return true;
	default:
		return false;
	}
}

bool CVisuals::EntityIsGrenade(int id) {
	switch (id) {
	case CBaseCSGrenadeProjectile:
	case CDecoyGrenade:
	case CDecoyProjectile:
	case CFlashbang:
	case CHEGrenade:
	case CIncendiaryGrenade:
	case CMolotovGrenade:
	case CMolotovProjectile:
	case CSensorGrenade:
	case CSensorGrenadeProjectile:
	case CSmokeGrenade:
	case CSmokeGrenadeProjectile:
		return true;
	default:
		return false;
	}
}

bool CVisuals::EntityIsBomb(int id) {
	switch (id) {
	case CC4:
	case CPlantedC4:
	case CBreachCharge:
	case CBreachChargeProjectile:
		return true;
	default:
		return false;
	}
}

bool CVisuals::EntityIsOther(int id) {
	switch (id) {
	case CItem_Healthshot:
	case CItemCash:
	//case CItemDogtags: //idk if crash
	//case CKnife: //todo: only if in dangerzone
	case CMelee:
	case CTablet:
	case CWeaponTaser:
		return true;
	default:
		return false;
	}
}