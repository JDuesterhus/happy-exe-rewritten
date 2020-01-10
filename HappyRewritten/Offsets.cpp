#include "Offsets.h"

COffsets Offsets;

using namespace json11;

void COffsets::DownloadOffsets() {
	//DOWNLOADING FRESH OFFSETS
	char downloadUrl[512];
	strcpy(downloadUrl, Settings.Misc.Offset_URL.c_str());
	char downloadFileName[64] = ".\\offsets.json";
	URLDownloadToFile(0, downloadUrl, downloadFileName, 0, 0);
	DeleteUrlCacheEntry(downloadUrl);

	//FILE TO STRING
	std::ifstream downloadFile(downloadFileName);
	std::string downloadFileString((std::istreambuf_iterator<char>(downloadFile)), std::istreambuf_iterator<char>());
	text = downloadFileString;

	//PARSING JSON STRING
	const auto offsets = Json::parse(text, text);

	clientstate_choked_commands =		offsets["signatures"]["clientstate_choked_commands"].int_value(); //isint
	clientstate_delta_ticks =			offsets["signatures"]["clientstate_delta_ticks"].int_value();
	clientstate_last_outgoing_command = offsets["signatures"]["clientstate_last_outgoing_command"].int_value();
	clientstate_net_channel =			offsets["signatures"]["clientstate_net_channel"].int_value();
	convar_name_hash_table =			offsets["signatures"]["convar_name_hash_table"].int_value();
	dwClientState =						offsets["signatures"]["dwClientState"].int_value();
	dwClientState_GetLocalPlayer =		offsets["signatures"]["dwClientState_GetLocalPlayer"].int_value();
	dwClientState_IsHLTV =				offsets["signatures"]["dwClientState_IsHLTV"].int_value();
	dwClientState_Map =					offsets["signatures"]["dwClientState_Map"].int_value();
	dwClientState_MapDirectory =		offsets["signatures"]["dwClientState_MapDirectory"].int_value();
	dwClientState_MaxPlayer =			offsets["signatures"]["dwClientState_MaxPlayer"].int_value();
	dwClientState_PlayerInfo =			offsets["signatures"]["dwClientState_PlayerInfo"].int_value();
	dwClientState_State =				offsets["signatures"]["dwClientState_State"].int_value();
	dwClientState_ViewAngles =			offsets["signatures"]["dwClientState_ViewAngles"].int_value();
	dwEntityList =						offsets["signatures"]["dwEntityList"].int_value();
	dwForceAttack =						offsets["signatures"]["dwForceAttack"].int_value();
	dwForceAttack2 =					offsets["signatures"]["dwForceAttack2"].int_value();
	dwForceBackward =					offsets["signatures"]["dwForceBackward"].int_value();
	dwForceForward =					offsets["signatures"]["dwForceForward"].int_value();
	dwForceJump =						offsets["signatures"]["dwForceJump"].int_value();
	dwForceLeft =						offsets["signatures"]["dwForceLeft"].int_value();
	dwForceRight =						offsets["signatures"]["dwForceRight"].int_value();
	dwGameDir =							offsets["signatures"]["dwGameDir"].int_value();
	dwGameRulesProxy =					offsets["signatures"]["dwGameRulesProxy"].int_value();
	dwGetAllClasses =					offsets["signatures"]["dwGetAllClasses"].int_value();
	dwGlobalVars =						offsets["signatures"]["dwGlobalVars"].int_value();
	dwGlowObjectManager =				offsets["signatures"]["dwGlowObjectManager"].int_value();
	dwInput =							offsets["signatures"]["dwInput"].int_value();
	dwInterfaceLinkList =				offsets["signatures"]["dwInterfaceLinkList"].int_value();
	dwLocalPlayer =						offsets["signatures"]["dwLocalPlayer"].int_value();
	dwMouseEnable =						offsets["signatures"]["dwMouseEnable"].int_value();
	dwMouseEnablePtr =					offsets["signatures"]["dwMouseEnablePtr"].int_value();
	dwPlayerResource =					offsets["signatures"]["dwPlayerResource"].int_value();
	dwRadarBase =						offsets["signatures"]["dwRadarBase"].int_value();
	dwSensitivity =						offsets["signatures"]["dwSensitivity"].int_value();
	dwSensitivityPtr =					offsets["signatures"]["dwSensitivityPtr"].int_value();
	dwSetClanTag =						offsets["signatures"]["dwSetClanTag"].int_value();
	dwViewMatrix =						offsets["signatures"]["dwViewMatrix"].int_value();
	dwWeaponTable =						offsets["signatures"]["dwWeaponTable"].int_value();
	dwWeaponTableIndex =				offsets["signatures"]["dwWeaponTableIndex"].int_value();
	dwYawPtr =							offsets["signatures"]["dwYawPtr"].int_value();
	dwZoomSensitivityRatioPtr =			offsets["signatures"]["dwZoomSensitivityRatioPtr"].int_value();
	dwbSendPackets =					offsets["signatures"]["dwbSendPackets"].int_value();
	dwppDirect3DDevice9 =				offsets["signatures"]["dwppDirect3DDevice9"].int_value();
	force_update_spectator_glow =		offsets["signatures"]["force_update_spectator_glow"].int_value();
	interface_engine_cvar =				offsets["signatures"]["interface_engine_cvar"].int_value();
	is_c4_owner =						offsets["signatures"]["is_c4_owner"].int_value();
	m_bDormant =						offsets["signatures"]["m_bDormant"].int_value();
	m_pStudioHdr =						offsets["signatures"]["m_pStudioHdr"].int_value();
	m_pitchClassPtr =					offsets["signatures"]["m_pitchClassPtr"].int_value();
	m_yawClassPtr =						offsets["signatures"]["m_yawClassPtr"].int_value();
	model_ambient_min =					offsets["signatures"]["model_ambient_min"].int_value();
	set_abs_angles =					offsets["signatures"]["set_abs_angles"].int_value();
	set_abs_origin =					offsets["signatures"]["set_abs_origin"].int_value();
	cs_gamerules_data =					offsets["netvars"]["cs_gamerules_data"].int_value();
	m_ArmorValue =						offsets["netvars"]["m_ArmorValue"].int_value();
	m_Collision =						offsets["netvars"]["m_Collision"].int_value();
	m_CollisionGroup =					offsets["netvars"]["m_CollisionGroup"].int_value();
	m_Local =							offsets["netvars"]["m_Local"].int_value();
	m_MoveType =						offsets["netvars"]["m_MoveType"].int_value();
	m_OriginalOwnerXuidHigh =			offsets["netvars"]["m_OriginalOwnerXuidHigh"].int_value();
	m_OriginalOwnerXuidLow =			offsets["netvars"]["m_OriginalOwnerXuidLow"].int_value();
	m_SurvivalGameRuleDecisionTypes =	offsets["netvars"]["m_SurvivalGameRuleDecisionTypes"].int_value();
	m_SurvivalRules =					offsets["netvars"]["m_SurvivalRules"].int_value();
	m_aimPunchAngle =					offsets["netvars"]["m_aimPunchAngle"].int_value();
	m_aimPunchAngleVel =				offsets["netvars"]["m_aimPunchAngleVel"].int_value();
	m_angEyeAnglesX =					offsets["netvars"]["m_angEyeAnglesX"].int_value();
	m_angEyeAnglesY =					offsets["netvars"]["m_angEyeAnglesY"].int_value();
	m_bBombPlanted =					offsets["netvars"]["m_bBombPlanted"].int_value();
	m_bFreezePeriod =					offsets["netvars"]["m_bFreezePeriod"].int_value();
	m_bGunGameImmunity =				offsets["netvars"]["m_bGunGameImmunity"].int_value();
	m_bHasDefuser =						offsets["netvars"]["m_bHasDefuser"].int_value();
	m_bHasHelmet =						offsets["netvars"]["m_bHasHelmet"].int_value();
	m_bInReload =						offsets["netvars"]["m_bInReload"].int_value();
	m_bIsDefusing =						offsets["netvars"]["m_bIsDefusing"].int_value();
	m_bIsGrabbingHostage =				offsets["netvars"]["m_bIsGrabbingHostage"].int_value();
	m_bIsQueuedMatchmaking =			offsets["netvars"]["m_bIsQueuedMatchmaking"].int_value();
	m_bIsScoped =						offsets["netvars"]["m_bIsScoped"].int_value();
	m_bIsValveDS =						offsets["netvars"]["m_bIsValveDS"].int_value();
	m_bSpotted =						offsets["netvars"]["m_bSpotted"].int_value();
	m_bSpottedByMask =					offsets["netvars"]["m_bSpottedByMask"].int_value();
	m_clrRender =						offsets["netvars"]["m_clrRender"].int_value();
	m_dwBoneMatrix =					offsets["netvars"]["m_dwBoneMatrix"].int_value();
	m_fAccuracyPenalty =				offsets["netvars"]["m_fAccuracyPenalty"].int_value();
	m_fFlags =							offsets["netvars"]["m_fFlags"].int_value();
	m_flC4Blow =						offsets["netvars"]["m_flC4Blow"].int_value();
	m_flDefuseCountDown =				offsets["netvars"]["m_flDefuseCountDown"].int_value();
	m_flDefuseLength =					offsets["netvars"]["m_flDefuseLength"].int_value();
	m_flFallbackWear =					offsets["netvars"]["m_flFallbackWear"].int_value();
	m_flFlashDuration =					offsets["netvars"]["m_flFlashDuration"].int_value();
	m_flFlashMaxAlpha =					offsets["netvars"]["m_flFlashMaxAlpha"].int_value();
	m_flLastBoneSetupTime =				offsets["netvars"]["m_flLastBoneSetupTime"].int_value();
	m_flLowerBodyYawTarget =			offsets["netvars"]["m_flLowerBodyYawTarget"].int_value();
	m_flNextAttack =					offsets["netvars"]["m_flNextAttack"].int_value();
	m_flNextPrimaryAttack =				offsets["netvars"]["m_flNextPrimaryAttack"].int_value();
	m_flSimulationTime =				offsets["netvars"]["m_flSimulationTime"].int_value();
	m_flTimerLength =					offsets["netvars"]["m_flTimerLength"].int_value();
	m_hActiveWeapon =					offsets["netvars"]["m_hActiveWeapon"].int_value();
	m_hMyWeapons =						offsets["netvars"]["m_hMyWeapons"].int_value();
	m_hObserverTarget =					offsets["netvars"]["m_hObserverTarget"].int_value();
	m_hOwner =							offsets["netvars"]["m_hOwner"].int_value();
	m_hOwnerEntity =					offsets["netvars"]["m_hOwnerEntity"].int_value();
	m_iAccountID =						offsets["netvars"]["m_iAccountID"].int_value();
	m_iClip1 =							offsets["netvars"]["m_iClip1"].int_value();
	m_iCompetitiveRanking =				offsets["netvars"]["m_iCompetitiveRanking"].int_value();
	m_iCompetitiveWins =				offsets["netvars"]["m_iCompetitiveWins"].int_value();
	m_iCrosshairId =					offsets["netvars"]["m_iCrosshairId"].int_value();
	m_iEntityQuality =					offsets["netvars"]["m_iEntityQuality"].int_value();
	m_iFOV =							offsets["netvars"]["m_iFOV"].int_value();
	m_iFOVStart =						offsets["netvars"]["m_iFOVStart"].int_value();
	m_iGlowIndex =						offsets["netvars"]["m_iGlowIndex"].int_value();
	m_iHealth =							offsets["netvars"]["m_iHealth"].int_value();
	m_iItemDefinitionIndex =			offsets["netvars"]["m_iItemDefinitionIndex"].int_value();
	m_iItemIDHigh =						offsets["netvars"]["m_iItemIDHigh"].int_value();
	m_iMostRecentModelBoneCounter =		offsets["netvars"]["m_iMostRecentModelBoneCounter"].int_value();
	m_iObserverMode =					offsets["netvars"]["m_iObserverMode"].int_value();
	m_iShotsFired =						offsets["netvars"]["m_iShotsFired"].int_value();
	m_iState =							offsets["netvars"]["m_iState"].int_value();
	m_iTeamNum =						offsets["netvars"]["m_iTeamNum"].int_value();
	m_lifeState =						offsets["netvars"]["m_lifeState"].int_value();
	m_nFallbackPaintKit =				offsets["netvars"]["m_nFallbackPaintKit"].int_value();
	m_nFallbackSeed =					offsets["netvars"]["m_nFallbackSeed"].int_value();
	m_nFallbackStatTrak =				offsets["netvars"]["m_nFallbackStatTrak"].int_value();
	m_nForceBone =						offsets["netvars"]["m_nForceBone"].int_value();
	m_nTickBase =						offsets["netvars"]["m_nTickBase"].int_value();
	m_rgflCoordinateFrame =				offsets["netvars"]["m_rgflCoordinateFrame"].int_value();
	m_szCustomName =					offsets["netvars"]["m_szCustomName"].int_value();
	m_szLastPlaceName =					offsets["netvars"]["m_szLastPlaceName"].int_value();
	m_thirdPersonViewAngles =			offsets["netvars"]["m_thirdPersonViewAngles"].int_value();
	m_vecOrigin =						offsets["netvars"]["m_vecOrigin"].int_value();
	m_vecVelocity =						offsets["netvars"]["m_vecVelocity"].int_value();
	m_vecViewOffset =					offsets["netvars"]["m_vecViewOffset"].int_value();
	m_viewPunchAngle =					offsets["netvars"]["m_viewPunchAngle"].int_value();
}