#pragma once

#include <iomanip>
#include <string>

#define Pressed 0x8000

//Flags
#define FL_ON_GROUND 257 //769
#define FL_ON_GROUND_CROUCHED 263 //775
#define FL_ON_GROUND_MOVING_TO_STAND 259
#define FL_ON_GROUND_MOVING_TO_CROUCH 261 //773
#define FL_IN_PUDDLE 1281
#define FL_IN_PUDDLE_CROUCHED 1287
#define FL_IN_WATER 1280
#define FL_IN_WATER_CROUCHED 1286
#define FL_IN_AIR_MOVING_TO_CROUCH 260
#define FL_IN_AIR_STAND 256 //774
#define FL_IN_AIR_MOVING_TO_STAND 258 //768
#define FL_IN_AIR_CROUCHED 262 //774


enum LifeState {
	LIFE_ALIVE = 0,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY
};

enum GameState {
	SIGNONSTATE_NONE = 0,
	SIGNONSTATE_CHALLENGE,
	SIGNONSTATE_CONNECTED,
	SIGNONSTATE_NEW,
	SIGNONSTATE_PRESPAWN,
	SIGNONSTATE_SPAWN,
	SIGNONSTATE_FULL,
	SIGNONSTATE_CHANGELEVEL
};

enum CompClr {
	COLOR_GREY = -1,
	COLOR_YELLOW,
	COLOR_PURPLE,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_ORANGE
};

enum ItemID {
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,				//"Desert Eagle"
	WEAPON_ELITE,				//"Dual Berettas"
	WEAPON_FIVESEVEN,			//"Five-SeveN"
	WEAPON_GLOCK,				//"Glock-18"
	WEAPON_AK47 = 7,			//"AK-47"
	WEAPON_AUG,					//"AUG"
	WEAPON_AWP,					//"AWP"
	WEAPON_FAMAS,				//"FAMAS"
	WEAPON_G3SG1,				//"G3SG1"
	WEAPON_GALIL = 13,			//"Galil AR"
	WEAPON_M249,				//"M249"
	WEAPON_M4A4 = 16,			//"M4A4"
	WEAPON_MAC10,				//"MAC-10"
	WEAPON_P90 = 19,			//"P90"
	WEAPON_MP5SD = 23,			//"MP5-SD"
	WEAPON_UMP45,				//"UMP-45"
	WEAPON_XM1014,				//"XM1014"
	WEAPON_BIZON,				//"PP-Bizon"
	WEAPON_MAG7,				//"MAG-7"
	WEAPON_NEGEV,				//"Negev"
	WEAPON_SAWEDOFF,			//"Sawed-Off"
	WEAPON_TEC9,				//"Tec-9"
	WEAPON_ZEUS,				//"Zeus x27"
	WEAPON_P2000,				//"P2000"
	WEAPON_MP7,					//"MP7"
	WEAPON_MP9,					//"MP9"
	WEAPON_NOVA,				//"Nova"
	WEAPON_P250,				//"P250"
	WEAPON_SHIELD,				//"Ballistic Shield"
	WEAPON_SCAR20,				//"SCAR-20"
	WEAPON_SG553,				//"SG 553"
	WEAPON_SSG08,				//"SSG 08"
	WEAPON_KNIFEGG,				//"Knife"
	WEAPON_KNIFE,				//"Knife"
	WEAPON_FLASHBANG,			//"Flashbang"
	WEAPON_HEGRENADE,			//"High Explosive Grenade"
	WEAPON_SMOKEGRENADE,		//"Smoke Grenade"
	WEAPON_MOLOTOV,				//"Molotov"
	WEAPON_DECOY,				//"Decoy Grenade"
	WEAPON_INC,					//"Incendiary Grenade"
	WEAPON_C4,					//"C4 Explosive"
	WEAPON_HEALTHSHOT = 57,		//"Medi-Shot"
	WEAPON_KNIFE_T = 59,		//"Knife"
	WEAPON_M4A1S,				//"M4A1-S"
	WEAPON_USPS,				//"USP-S"
	WEAPON_CZ75 = 63,			//"CZ75-Auto"
	WEAPON_REVOLVER,			//"R8 Revolver"
	WEAPON_TAGRENADE = 68,		//"Tactical Awareness Grenade"
	WEAPON_FISTS,				//"Bare Hands"
	WEAPON_BREACHCHARGE,		//"Breach Charge"
	WEAPON_TABLET = 72,			//"Tablet"
	WEAPON_MELEE = 74,			//"Knife"
	WEAPON_AXE,					//"Axe"
	WEAPON_HAMMER,				//"Hammer"
	WEAPON_SPANNER = 78,		//"Wrench"
	WEAPON_KNIFE_GHOST = 80,	//"Spectral Shiv"
	WEAPON_FIREBOMB,			//"Fire Bomb"
	WEAPON_DIVERSION,			//"Diversion Device"
	WEAPON_FRAG_GRENADE,		//"Frag Grenade"
	WEAPON_SNOWBALL,			//"Snowball"
	WEAPON_BUMPMINE,			//"Bump Mine"
	WEAPON_KNIFE_BAYONET = 500,			//"Bayonet"
	WEAPON_KNIFE_CLASSIC = 503,			//"Classic Knife"
	WEAPON_KNIFE_FLIP = 505,			//"Flip Knife"
	WEAPON_KNIFE_GUT,					//"Gut Knife"
	WEAPON_KNIFE_KARAMBIT,				//"Karambit"
	WEAPON_KNIFE_M9_BAYONET,			//"M9 Bayonet"
	WEAPON_KNIFE_TACTICAL,				//"Huntsman Knife"
	WEAPON_KNIFE_FALCHION = 512,		//"Falchion Knife"
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,	//"Bowie Knife"
	WEAPON_KNIFE_BUTTERFLY,				//"Butterfly Knife"
	WEAPON_KNIFE_PUSH,					//"Shadow Daggers"
	WEAPON_KNIFE_URSUS = 519,			//"Ursus Knife"
	WEAPON_KNIFE_GYPSY_JACKKNIFE,		//"Navaja Knife"
	WEAPON_KNIFE_STILETTO = 522,		//"Stiletto Knife"
	WEAPON_KNIFE_WIDOWMAKER,			//"Talon Knife"
	GLOVE_STUDDED_BLOODHOUND = 5027,	//"Bloodhound Gloves"
	GLOVE_T_SIDE,						//"Default T Gloves"
	GLOVE_CT_SIDE,						//"Default CT Gloves"
	GLOVE_SPORTY,						//"Sport Gloves"
	GLOVE_SLICK,						//"Driver Gloves"
	GLOVE_LEATHER_WRAP,					//"Hand Wraps"
	GLOVE_MOTORCYCLE,					//"Moto Gloves"
	GLOVE_SPECIALIST,					//"Specialist Gloves"
	GLOVE_HYDRA							//"Hydra Gloves"
};

enum ClassID {
	CAK47 = 1,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CBumpMine,
	CBumpMineProjectile,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerPing,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSnowball,
	CSnowballPile,
	CSnowballProjectile,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponShield,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail
};