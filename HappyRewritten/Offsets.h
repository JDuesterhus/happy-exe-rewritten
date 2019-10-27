#pragma once

#include <iostream>
#include <Windows.h>
#include <wininet.h>
#include "IniReader.h"


class COffsets
{
public:

	DWORD dwClient;
	DWORD dwClientSize;
	DWORD dwEngine;
	DWORD dwEngineSize;

	void DownloadOffsets();
	DWORD cs_gamerules_data = 0x0;
	DWORD m_ArmorValue = 0xB328;
	DWORD m_Collision = 0x31C;
	DWORD m_CollisionGroup = 0x474;
	DWORD m_Local = 0x2FBC;
	DWORD m_MoveType = 0x25C;
	DWORD m_OriginalOwnerXuidHigh = 0x31B4;
	DWORD m_OriginalOwnerXuidLow = 0x31B0;
	DWORD m_SurvivalGameRuleDecisionTypes = 0x1318;
	DWORD m_SurvivalRules = 0xCF0;
	DWORD m_aimPunchAngle = 0x302C;
	DWORD m_aimPunchAngleVel = 0x3038;
	DWORD m_angEyeAnglesX = 0xB32C;
	DWORD m_angEyeAnglesY = 0xB330;
	DWORD m_bBombPlanted = 0x99D;
	DWORD m_bFreezePeriod = 0x20;
	DWORD m_bGunGameImmunity = 0x3928;
	DWORD m_bHasDefuser = 0xB338;
	DWORD m_bHasHelmet = 0xB31C;
	DWORD m_bInReload = 0x3285;
	DWORD m_bIsDefusing = 0x3914;
	DWORD m_bIsGrabbingHostage = 0x3915;
	DWORD m_bIsQueuedMatchmaking = 0x74;
	DWORD m_bIsScoped = 0x390A;
	DWORD m_bIsValveDS = 0x75;
	DWORD m_bSpotted = 0x93D;
	DWORD m_bSpottedByMask = 0x980;
	DWORD m_clrRender = 0x70;
	DWORD m_dwBoneMatrix = 0x26A8;
	DWORD m_fAccuracyPenalty = 0x3304;
	DWORD m_fFlags = 0x104;
	DWORD m_flC4Blow = 0x2990;
	DWORD m_flDefuseCountDown = 0x29AC;
	DWORD m_flDefuseLength = 0x29A8;
	DWORD m_flFallbackWear = 0x31C0;
	DWORD m_flFlashDuration = 0xA3E0;
	DWORD m_flFlashMaxAlpha = 0xA3DC;
	DWORD m_flLastBoneSetupTime = 0x2924;
	DWORD m_flLowerBodyYawTarget = 0x3A74;
	DWORD m_flNextAttack = 0x2D70;
	DWORD m_flNextPrimaryAttack = 0x3218;
	DWORD m_flSimulationTime = 0x268;
	DWORD m_flTimerLength = 0x2994;
	DWORD m_hActiveWeapon = 0x2EF8;
	DWORD m_hMyWeapons = 0x2DF8;
	DWORD m_hObserverTarget = 0x3388;
	DWORD m_hOwner = 0x29CC;
	DWORD m_hOwnerEntity = 0x14C;
	DWORD m_iAccountID = 0x2FC8;
	DWORD m_iClip1 = 0x3244;
	DWORD m_iCompetitiveRanking = 0x1A84;
	DWORD m_iCompetitiveWins = 0x1B88;
	DWORD m_iCrosshairId = 0xB394;
	DWORD m_iEntityQuality = 0x2FAC;
	DWORD m_iFOV = 0x31E4;
	DWORD m_iFOVStart = 0x31E8;
	DWORD m_iGlowIndex = 0xA3F8;
	DWORD m_iHealth = 0x100;
	DWORD m_iItemDefinitionIndex = 0x2FAA;
	DWORD m_iItemIDHigh = 0x2FC0;
	DWORD m_iMostRecentModelBoneCounter = 0x2690;
	DWORD m_iObserverMode = 0x3374;
	DWORD m_iShotsFired = 0xA370;
	DWORD m_iState = 0x3238;
	DWORD m_iTeamNum = 0xF4;
	DWORD m_lifeState = 0x25F;
	DWORD m_nFallbackPaintKit = 0x31B8;
	DWORD m_nFallbackSeed = 0x31BC;
	DWORD m_nFallbackStatTrak = 0x31C4;
	DWORD m_nForceBone = 0x268C;
	DWORD m_nTickBase = 0x342C;
	DWORD m_rgflCoordinateFrame = 0x444;
	DWORD m_szCustomName = 0x303C;
	DWORD m_szLastPlaceName = 0x35B0;
	DWORD m_thirdPersonViewAngles = 0x31D8;
	DWORD m_vecOrigin = 0x138;
	DWORD m_vecVelocity = 0x114;
	DWORD m_vecViewOffset = 0x108;
	DWORD m_viewPunchAngle = 0x3020;

	DWORD clientstate_choked_commands = 0x4D28;
	DWORD clientstate_delta_ticks = 0x174;
	DWORD clientstate_last_outgoing_command = 0x4D24;
	DWORD clientstate_net_channel = 0x9C;
	DWORD convar_name_hash_table = 0x2F0F8;
	DWORD dwClientState = 0x58BCFC;
	DWORD dwClientState_GetLocalPlayer = 0x180;
	DWORD dwClientState_IsHLTV = 0x4D40;
	DWORD dwClientState_Map = 0x28C;
	DWORD dwClientState_MapDirectory = 0x188;
	DWORD dwClientState_MaxPlayer = 0x388;
	DWORD dwClientState_PlayerInfo = 0x52B8;
	DWORD dwClientState_State = 0x108;
	DWORD dwClientState_ViewAngles = 0x4D88;
	DWORD dwEntityList = 0x4CE34FC;
	DWORD dwForceAttack = 0x3114BC4;
	DWORD dwForceAttack2 = 0x3114BD0;
	DWORD dwForceBackward = 0x3114C18;
	DWORD dwForceForward = 0x3114BF4;
	DWORD dwForceJump = 0x5186998;
	DWORD dwForceLeft = 0x3114C0C;
	DWORD dwForceRight = 0x3114C30;
	DWORD dwGameDir = 0x631F70;
	DWORD dwGameRulesProxy = 0x51F8CD4;
	DWORD dwGetAllClasses = 0xCF6BC4;
	DWORD dwGlobalVars = 0x58BA00;
	DWORD dwGlowObjectManager = 0x5223740;
	DWORD dwInput = 0x512E510;
	DWORD dwInterfaceLinkList = 0x8AFF44;
	DWORD dwLocalPlayer = 0xCD2764;
	DWORD dwMouseEnable = 0xCD82B0;
	DWORD dwMouseEnablePtr = 0xCD8280;
	DWORD dwPlayerResource = 0x3112F5C;
	DWORD dwRadarBase = 0x511823C;
	DWORD dwSensitivity = 0xCD814C;
	DWORD dwSensitivityPtr = 0xCD8120;
	DWORD dwSetClanTag = 0x896A0;
	DWORD dwViewMatrix = 0x4CD4F14;
	DWORD dwWeaponTable = 0x512EFD8;
	DWORD dwWeaponTableIndex = 0x323C;
	DWORD dwYawPtr = 0xCD7F10;
	DWORD dwZoomSensitivityRatioPtr = 0xCDD150;
	DWORD dwbSendPackets = 0xD243A;
	DWORD dwppDirect3DDevice9 = 0xA6020;
	DWORD force_update_spectator_glow = 0x38DE82;
	DWORD interface_engine_cvar = 0x3E9EC;
	DWORD is_c4_owner = 0x399F60;
	DWORD m_bDormant = 0xED;
	DWORD m_pStudioHdr = 0x294C;
	DWORD m_pitchClassPtr = 0x51184F0;
	DWORD m_yawClassPtr = 0xCD7F10;
	DWORD model_ambient_min = 0x58ED1C;
	DWORD set_abs_angles = 0x1C7C70;
	DWORD set_abs_origin = 0x1C7AB0;

	//DWORD m_AttributeManager = 0x2D80;
	//DWORD m_Item = 0x40;
	//DWORD m_iItemDefinitionIndex = 0x1EA;
	//= 0x2FAA

	//DWORD m_iPlayerC4 = 0x165C;
	DWORD m_PlayerFog = 0x37B0;
	DWORD m_hPostProcessCtrl = 0x37A4;

	//DT_CSPlayer
	DWORD m_hTonemapController = 0x31CC; 

	//DT_EnvTonemapController
	DWORD m_bUseCustomAutoExposureMin = 0x9D8; //(byte)
	DWORD m_bUseCustomAutoExposureMax = 0x9D9; //(byte)
	DWORD m_bUseCustomBloomScale = 0x9DA; //(byte)
	DWORD m_flCustomAutoExposureMin = 0x9DC; //(float)
	DWORD m_flCustomAutoExposureMax = 0x9E0; //(float)
	DWORD m_flCustomBloomScale = 0x9E4; //(float)
	DWORD m_flCustomBloomScaleMinimum = 0x9E8; //(float)
	DWORD m_flBloomExponent = 0x9EC; //(float)
	DWORD m_flBloomSaturation = 0x9F0; //(float)
	DWORD m_flTonemapPercentTarget = 0x9F4; //(float)
	DWORD m_flTonemapPercentBrightPixels = 0x9F8; //(float)
	DWORD m_flTonemapMinAvgLum = 0x9FC; //(float)
	DWORD m_flTonemapRate = 0xA00; //(float)


	DWORD m_flModelScale = 0x2748; //m_flModelScale


	DWORD ClientCMD;
	DWORD ClientCMDArray;

	DWORD EngineBase;
	DWORD LocalBase;
};

extern COffsets Offsets;