#include "Aimbot.h"

CAimbot Aimbot;


void CAimbot::DropTarget() {
	Target = -1;
	iMax = 9999.f;
}




void CAimbot::Normal() {
	//DropTarget();
	if (Misc.WeaponValid(Misc.GetCurrentWeapon(Offsets.LocalBase))) {
		if (!Misc.IsReloading(Offsets.LocalBase)) {
			static int oldTarget = -1;
			Target = FindBestTarget();
			if (Target > 0) {
				Vector AimAngle;
				AimAngle = CalcAngle(MyEyePosition(), BonePos(EntBoneMatrix(EntBase(Target)), bone), Settings.Aimbot.RCS_Pitch, Settings.Aimbot.RCS_Yaw);
				AimAngle = SmoothAngle(MyViewAngle(), AimAngle, Settings.Aimbot.Aimbot_Smooth_Pitch, Settings.Aimbot.Aimbot_Smooth_Yaw);
				AimAngle = NormalizeAngle(AimAngle);
				AimAngle = ClampAngle(AimAngle);
				Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
				oldTarget = Target;
			}
			else {
				Target = -1;
			}
		}
	}
}

//float RandomFloat(float min, float max) {
//	std::uniform_real<float> ur(min, max);
//	std::random_device rd;
//	std::mt19937 mte(rd());
//	return ur(mte);
//}

//void CAimbot::AntiAim() {
//	for (int x = 1; x <= 8; x++) {
//		Vector antiaim;
//		if (x == 1) {
//			antiaim.y = 0;
//		}
//		if (x == 2) {
//			antiaim.y = 45;
//		}
//		if (x == 3) {
//			antiaim.y = 90;
//		}
//		if (x == 4) {
//			antiaim.y = 135;
//		}
//		if (x == 5) {
//			antiaim.y = 180;
//		}
//		if (x == 6) {
//			antiaim.y = 225;
//		}
//		if (x == 7) {
//			antiaim.y = 270;
//		}
//		if (x == 8) {
//			antiaim.y = 315;
//		}
//		Vector aimpunch;
//		aimpunch.x = 0;
//		aimpunch.y = 0;
//		aimpunch.z = 0;
//
//		//antiaim = NormalizeAngle(antiaim);
//		//antiaim = ClampAngle(antiaim);
//
//		Vector MyAngle = Aimbot.MyViewAngle();
//		Vector AimAngle;
//		AimAngle.y = MyAngle.y - 45;
//		AimAngle = NormalizeAngle(AimAngle);
//		AimAngle = ClampAngle(AimAngle);
//
//		Vector MyAngleDiff;
//		MyAngleDiff = MyAngle + antiaim;
//		MyAngleDiff = NormalizeAngle(MyAngleDiff);
//		MyAngleDiff = ClampAngle(MyAngleDiff);
//
//
//		for (int x = 1; x <= 256; x++) {
//			//Memory::Write<Vector>(Offsets.LocalBase + Offsets.m_aimPunchAngle, aimpunch);
//			Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
//			Memory::Write<Vector>(Offsets.LocalBase + Offsets.m_viewPunchAngle, MyAngleDiff);
//			if (x == 32) Sleep(1);
//			if (x == 64) Sleep(1);
//			if (x == 96) Sleep(1);
//			if (x == 128) Sleep(1);
//			if (x == 160) Sleep(1);
//			if (x == 192) Sleep(1);
//			if (x == 224) Sleep(1);
//		}
//		Sleep(1000);
//	}
//}


//void CAimbot::RCS() {
//	static Vector PrevAimPunch;
//	static Vector AimPunch1;
//	static Vector AimPunch;
//	static Vector AimAngle;
//	AimPunch = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_aimPunchAngle);
//
//	Vector SmoothPunch;
//	SmoothPunch.x = SmoothPunch.x * 0.2 + AimPunch.x * (1 - 0.2);
//	SmoothPunch.y = SmoothPunch.y * 0.2 + AimPunch.y * (1 - 0.2);
//	AimAngle = Memory::Read<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles);
//	if (Misc.WeaponIsAutomatic(Misc.GetCurrentWeapon(Offsets.LocalBase)) && !Misc.IsReloading(Offsets.LocalBase)) {
//		DWORD WeaponEntity = Misc.GetWeaponEntity(Offsets.LocalBase);
//		int WeaponClip = Memory::Read<int>(WeaponEntity + Offsets.m_iClip1);
//		if (WeaponClip > 0) {
//			if (Misc.IsAttacking() || Misc.GetShotsFired(Offsets.LocalBase) > 1) {
//				//Vector PretictedAngle;
//				static int PrevShots = 0;
//				//std::cout << "AimPunchx: " << AimPunch.x << std::endl;
//				//std::cout << "AimPunchy: " << AimPunch.y << std::endl;
//				//Vector src = AimAngle;
//				//RandomFloat(1, 2)
//				AimAngle.x -= (AimPunch.x - PrevAimPunch.x) * 1;
//				AimAngle.y -= (AimPunch.y - PrevAimPunch.y) * 1;
//				Vector src;
//				src = Memory::Read<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles);
//				//AimAngle = SmoothAngle(src, AimAngle, 0.11, 0.24);
//				//AimAngle = NormalizeAngle(AimAngle);
//				//AimAngle = ClampAngle(AimAngle);
//
//				//Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
//
//				AimAngle = SmoothAngle(MyViewAngle(), AimAngle, 10, 10);
//				AimAngle = NormalizeAngle(AimAngle);
//				AimAngle = ClampAngle(AimAngle);
//				Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
//
//
//
//				Sleep(1);
//				//AimAngle = SmoothAngle(src, AimAngle, 4, 4);
//				//AimAngle = NormalizeAngle(AimAngle);
//				//AimAngle = ClampAngle(AimAngle);
//				//while (AimPunch.x < (PrevAimPunch.x + 1) || AimPunch.y < (PrevAimPunch.y + 1) || AimPunch.x > (PrevAimPunch.x - 1) || AimPunch.y > (PrevAimPunch.y - 1)) {
//				//
//				//	std::cout << "changing angles" << std::endl;
//				//	Sleep(1);
//				//
//				//
//				//}
//				//if (AimPunch.x > (PrevAimPunch.x + 1) || AimPunch.y > (PrevAimPunch.y + 1) || AimPunch.x <(PrevAimPunch.x - 1) || AimPunch.y < (PrevAimPunch.y - 1)) {
//				//	src = Memory::Read<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles);
//				//	AimPunch = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_aimPunchAngle);
//				//	AimAngle = SmoothAngle(src, AimAngle, 0, 0);
//				//	AimAngle = NormalizeAngle(AimAngle);
//				//	AimAngle = ClampAngle(AimAngle);
//				//	Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
//				//
//				//}
//				PrevAimPunch.x = SmoothPunch.x;
//				PrevAimPunch.y = SmoothPunch.y;
//				//else {
//				//
//				//
//				//	std::cout << "NOT changing angles" << std::endl;
//				//}
//
//			}
//			if (!Misc.IsAttacking() && Misc.GetShotsFired(Offsets.LocalBase) == 0) {
//				PrevAimPunch.x = SmoothPunch.x;
//				PrevAimPunch.y = SmoothPunch.y;
//			}
//		}
//	}
//}



//static NTSTATUS(__stdcall* NtDelayExecution)(BOOL Alertable, PLARGE_INTEGER DelayInterval) = (NTSTATUS(__stdcall*)(BOOL, PLARGE_INTEGER)) GetProcAddress(GetModuleHandle("ntdll.dll"), "NtDelayExecution");
//static NTSTATUS(__stdcall* ZwSetTimerResolution)(IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution) = (NTSTATUS(__stdcall*)(ULONG, BOOLEAN, PULONG)) GetProcAddress(GetModuleHandle("ntdll.dll"), "ZwSetTimerResolution");
//
//static void SleepShort(float milliseconds) {
//	static bool once = true;
//	if (once) {
//		ULONG actualResolution;
//		ZwSetTimerResolution(1, true, &actualResolution); 
//		once = false;
//	}
//
//	LARGE_INTEGER interval;
//	interval.QuadPart = -1 * (int)(milliseconds * 10000.0f);
//	NtDelayExecution(false, &interval);
//}

//void CAimbot::Silent() {
//	Vector AimAngle; //move
//	if (Misc.WeaponValid(Misc.GetCurrentWeapon(Offsets.LocalBase))) {
//		if (!Misc.IsReloading(Offsets.LocalBase)) {
//			if (CanShoot()) {
//				Target = FindBestTarget();
//				if (Target > 0) {
//					AimAngle = CalcAngle(MyEyePosition(), BonePos(EntBoneMatrix(EntBase(Target)), bone), Settings.Aimbot.RCS_Pitch, Settings.Aimbot.RCS_Yaw);
//					AimAngle = NormalizeAngle(AimAngle);
//					AimAngle = ClampAngle(AimAngle);
//					Vector nullvector;
//					nullvector.x = 0;
//					nullvector.y = 0;
//					nullvector.z = 0;
//					Vector MyAngle = MyViewAngle();
//					Vector MyAngleDiff;
//					MyAngleDiff.y = MyAngle.y - AimAngle.y;
//					MyAngleDiff.x = MyAngle.x - AimAngle.x;
//					for (int x = 1; x <= 256; x++) {
//						Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, false);
//						Memory::Write<Vector>(Offsets.LocalBase + Offsets.m_viewPunchAngle, MyAngleDiff); //FAKE ANGLE
//						if (x >= 16 && x <= 64) Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle); //REAL ANGLE
//						if (x == 16) Sleep(1);
//						//if (x == 128) SleepShort(0.5);
//					}
//					SleepShort((Settings.Aimbot.Aimbot_Silent_Strength + 25) / 100 * 2);
//					MyAngle = MyViewAngle();
//					MyAngle.y = MyAngle.y + MyAngleDiff.y;
//					MyAngle.x = MyAngle.x + MyAngleDiff.x;
//					for (int x = 1; x <= 256; x++) {
//						Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, true);
//						Memory::Write<Vector>(Offsets.LocalBase + Offsets.m_viewPunchAngle, nullvector); //FAKE ANGLE
//						Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, MyAngle); //REAL ANGLE
//						//if (x == 32) Sleep(1);
//						//if (x == 128) SleepShort(0.5);
//					}
//					//Sleep((-Settings.Aimbot.Aimbot_Silent_Strength + 105) * 4);
//				}
//				else {
//					Target = -1;
//				}
//			}
//		}
//	}
//}






void CAimbot::TwoHP() {
	if (Misc.GetCurrentWeapon(Offsets.LocalBase) == WEAPON_HEGRENADE) {
		Vector AimAngle;
		Vector Angle;
		Vector AngleOld = MyViewAngle();
		//look up
		do {
			Angle = MyViewAngle();
			Vector AngleUP;
			AngleUP.x = -89;
			AngleUP.y = Angle.y;
			AimAngle = SmoothAngle(Angle, AngleUP, 5, 5);
			AimAngle = NormalizeAngle(AimAngle);
			AimAngle = ClampAngle(AimAngle);
			Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
			Sleep(1);
		} while (Angle.x > -88.9);
		//throw nade
		Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack2 + -120, 5);
		Sleep(200);
		Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack, 5);
		Sleep(80); //78-82 
		Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack2 + -120, 4);
		Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack, 4);
		Sleep(220);
		//knife
		Misc.Console("slot3");
		//look down
		do {
			Angle = MyViewAngle();
			Vector AngleDOWN;
			AngleDOWN.x = AngleOld.x;
			AngleDOWN.y = Angle.y;
			AimAngle = SmoothAngle(Angle, AngleDOWN, 10, 10);
			AimAngle = NormalizeAngle(AimAngle);
			AimAngle = ClampAngle(AimAngle);
			Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
			Sleep(1);
		} while (Angle.x < AngleOld.x - 0.01);
	}
}

void CAimbot::ThreeSixty() {
	Vector AimAngle;
	Vector Angle;
	Vector AngleStart = MyViewAngle();
	Vector AngleOld = MyViewAngle();
	for (int i = 1; i <= 140; i++) {
		Angle = MyViewAngle();
		Vector AngleLEFT;
		AngleLEFT.x = Angle.x;
		AngleLEFT.y = AngleOld.y + 5 * i;
		if (i > 80) AngleLEFT.y = AngleOld.y + 0.75;
		AimAngle = SmoothAngle(Angle, AngleLEFT, 12, 12);
		AimAngle = NormalizeAngle(AimAngle);
		AimAngle = ClampAngle(AimAngle);
		Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
		Sleep(1);
	}
	Sleep(50);
}



void CAimbot::OneEighty() {
	Vector AimAngle;
	Vector Angle;
	Vector AngleStart = MyViewAngle();
	Vector AngleOld = MyViewAngle();
	for (int i = 1; i <= 70; i++) {
		Angle = MyViewAngle();
		Vector AngleLEFT;
		AngleLEFT.x = Angle.x;
		AngleLEFT.y = AngleOld.y + 5 * i;
		if (i > 40) AngleLEFT.y = AngleOld.y - 176;
		AimAngle = SmoothAngle(Angle, AngleLEFT, 12, 12);
		AimAngle = NormalizeAngle(AimAngle);
		AimAngle = ClampAngle(AimAngle);
		Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
		Sleep(1);
	}
	Sleep(50);
}


int CAimbot::FindBestTarget() {
	DropTarget();
	bone = Settings.Aimbot.Aimbot_Bone;

	struct EntityInfo {
		DWORD Base[65];
		bool Dormant[65];
		int Health[65];
		bool Spotted[65];
		float GodTime[65];
		int Team[65];
		int Flags[65];
		//Vector OriginPos[65];
		DWORD BoneMatrix[65];
		Vector EyePos[65];

	}; EntityInfo Ent;


	for (int i = 1; i <= 64; i++) {
		if (Settings.Aimbot.Aimbot_Check_Flash) {
			float LocalFlashAlpha = Memory::Read<float>(Offsets.LocalBase + Offsets.m_flFlashMaxAlpha - 0x8);
			if (Settings.Misc.Reduce_Flash && LocalFlashAlpha >= Settings.Misc.Reduce_Flash_Alpha * 0.8 || !Settings.Misc.Reduce_Flash && LocalFlashAlpha >= 255 * 0.8) // '* 0.8' for 20% visibility
				continue;
		}

		Ent.Base[i] = EntBase(i);
		if (Ent.Base[i] == 0)
			continue;

		Ent.Dormant[i] = EntDormant(Ent.Base[i]);
		if (Ent.Dormant[i])
			continue;

		Ent.Health[i] = EntHealth(Ent.Base[i]);
		if (Ent.Health[i] < 1)
			continue;

		if (Settings.Aimbot.Aimbot_Check_Visible) {
			Ent.Spotted[i] = EntSpotted(Ent.Base[i]);
			if (!Ent.Spotted[i])
				continue;
		}

		if (Settings.Aimbot.Aimbot_Ignore_God) {
			Ent.GodTime[i] = EntGodTime(Ent.Base[i]);
			if (Ent.GodTime[i] > 0)
				continue;
		}

		if (Settings.Aimbot.Aimbot_Ignore_Ally) {
			Ent.Team[i] = EntTeam(Ent.Base[i]);
			int LocalTeam = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iTeamNum);
			if (Ent.Team[i] == LocalTeam)
				continue;
		}

		if (Settings.Aimbot.Aimbot_Ignore_Jump) {
			Ent.Flags[i] = EntFlags(Ent.Base[i]);
			if (Ent.Flags[i] == 774)
				continue;
		}

		if (Misc.GetShotsFired(Offsets.LocalBase) >= Settings.Aimbot.Aimbot_Bone2_AfterShots) {
			bone = Settings.Aimbot.Aimbot_Bone2;
		}

		if (Ent.Health[i] <= Settings.Aimbot.Aimbot_Bone2_OnHealth) {
			bone = Settings.Aimbot.Aimbot_Bone2;
		}

		Ent.BoneMatrix[i] = EntBoneMatrix(Ent.Base[i]);
		if (GetFov(MyViewAngle(), MyEyePosition(), BonePos(Ent.BoneMatrix[i], bone)) > Settings.Aimbot.Aimbot_FOV)
			continue;

		Ent.EyePos[i] = EntEyePos(Ent.Base[i]);
		float tmp = AngleDiff(MyViewAngle(), MyEyePosition(), Ent.EyePos[i]);


		if (tmp < iMax) {
			iMax = tmp;
			Target = i; 
		}
	}
	if (Target == -1) {
		Sleep(8);
	}
	//RETARGET DELAY
	if (Target != TargetOld) {
		Sleep(Settings.Aimbot.Aimbot_Delay);
		if (Ent.Health[TargetOld] < 1 && TargetOld != -1) {
			Sleep(Settings.Aimbot.Aimbot_Delay_Kill);
		}
	}
	TargetOld = Target;
	//std::cout << "target: " << Target << std::endl;
	return Target;
}



float CAimbot::AngleDiff(Vector angle, Vector src, Vector dst) {
	Vector aim;
	float angDifference;

	Vector ang = CalcAngle(src, dst, Settings.Aimbot.RCS_Pitch, Settings.Aimbot.RCS_Yaw);

	MakeVector(angle, aim);
	MakeVector(ang, ang);

	float mag_s = FASTSQRT((aim.x * aim.x) + (aim.y * aim.y) + (aim.z * aim.z));
	float mag_d = FASTSQRT((aim.x * aim.x) + (aim.y * aim.y) + (aim.z * aim.z));

	float u_dot_v = aim.x * ang.x + aim.y * ang.y + aim.z * ang.z;

	angDifference = acosf(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI);

	return angDifference;
}



float CAimbot::VecDist(Vector& fVec1, Vector& fVec2) {
	return FASTSQRT(powf(fVec1.x - fVec2.x, 2) + powf(fVec1.y - fVec2.y, 2) + powf(fVec1.z - fVec2.z, 2));
}

float CAimbot::VecDist2D(Vector& fVec1, Vector& fVec2) {
	return FASTSQRT(powf(fVec1.x - fVec2.x, 2) + powf(fVec1.y - fVec2.y, 2));
}


DWORD CAimbot::EntBase(int i) {
	DWORD Entity = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwEntityList + (0x10 * i));
	return Entity;
}

DWORD CAimbot::EntBoneMatrix(DWORD base) {
	DWORD EntityBoneMatrix = Memory::Read<DWORD>(base + Offsets.m_dwBoneMatrix);
	return EntityBoneMatrix;
}

bool CAimbot::EntDormant(DWORD base) {
	bool EntityDormant = Memory::Read<bool>(base + Offsets.m_bDormant);
	return EntityDormant;
}

int CAimbot::EntHealth(DWORD base) {
	int EntityHealth = Memory::Read<int>(base + Offsets.m_iHealth);
	return EntityHealth;
}

bool CAimbot::EntSpotted(DWORD base) {
	bool EntitySpotted = Memory::Read<bool>(base + Offsets.m_bSpottedByMask);
	return EntitySpotted;
}

float CAimbot::EntGodTime(DWORD base) {
	float EntityGodTime = Memory::Read<float>(base + Offsets.m_bGunGameImmunity - 0x8);
	return EntityGodTime;
}

int CAimbot::EntTeam(DWORD base) {
	int EntityTeam = Memory::Read<int>(base + Offsets.m_iTeamNum);
	return EntityTeam;
}

int CAimbot::EntFlags(DWORD base) {
	int EntityFlags = Memory::Read<int>(base + Offsets.m_fFlags);
	return EntityFlags;
}

Vector CAimbot::EntOriginPos(DWORD base) {
	Vector EntityOriginPos = Memory::Read<Vector>(base + Offsets.m_vecOrigin);
	return EntityOriginPos;
}

Vector CAimbot::EntEyePos(DWORD base) {
	Vector EntityOriginPos = Memory::Read<Vector>(base + Offsets.m_vecOrigin);
	Vector EntityEyePos = Memory::Read<Vector>(base + Offsets.m_vecViewOffset);
	EntityEyePos = EntityOriginPos + EntityEyePos;
	return EntityEyePos;
}

Vector CAimbot::MyViewAngle() {
	Vector ViewAngle = Memory::Read<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles);
	return ViewAngle;
}

//maybe remove and use EntOrigin instead
Vector CAimbot::MyOrigin() {
	Vector Origin = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_vecOrigin);
	return Origin;
}

Vector CAimbot::MyEyeAngle() {
	Vector EyeAngle = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_vecViewOffset);
	return EyeAngle;
}

//use this for EntEyePos aswell
Vector CAimbot::MyEyePosition() {
	Vector EyePosition = MyOrigin() + MyEyeAngle();
	return EyePosition;
}

Vector CAimbot::MyAimPunch() {
	Vector AimPunch = Memory::Read<Vector>(Offsets.LocalBase + Offsets.m_aimPunchAngle);
	return AimPunch;
}

Vector CAimbot::BonePos(DWORD boneBase, int boneID) {
	Vector bonePos;
	bonePos.x = Memory::Read<float>(boneBase + 0x30 * boneID + 0x0C);
	bonePos.y = Memory::Read<float>(boneBase + 0x30 * boneID + 0x1C);
	bonePos.z = Memory::Read<float>(boneBase + 0x30 * boneID + 0x2C);
	return bonePos;
}

float CAimbot::Dot(const Vector &v1, Vector &v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float CAimbot::GetFov(Vector angle, Vector src, Vector dst) {
	Vector ang, aim;
	ang = CalcAngle(src, dst, Settings.Aimbot.RCS_Pitch, Settings.Aimbot.RCS_Yaw);
	MakeVector(angle, aim);
	MakeVector(ang, ang);
	float mag = FASTSQRT(powf(aim.x, 2) + powf(aim.y, 2) + powf(aim.z, 2));
	float u_dot_v = Dot(aim, ang);
	return RAD2DEG(acosf(u_dot_v / (powf(mag, 2))));
}

Vector CAimbot::CalcAngle(Vector src, Vector dst, float recoilx, float recoily) {
	Vector AimAngles;
	Vector delta = src - dst;
	float hyp = FASTSQRT((delta.x * delta.x) + (delta.y * delta.y));
	if (Misc.GetShotsFired(Offsets.LocalBase) < Settings.Aimbot.RCS_AfterShots || !Settings.Aimbot.Aimbot_RCS) {
		recoilx = 0;
		recoily = 0;
	}
	AimAngles.x = atanf(delta.z / hyp) * M_RADPI - MyAimPunch().x * (0.02f * recoilx);
	AimAngles.y = atanf(delta.y / delta.x) * M_RADPI - MyAimPunch().y * (0.02f * recoily);
	AimAngles.z = 0.0f;
	if (delta.x >= 0.0)
		AimAngles.y += 180.0f;

	return AimAngles;
}

Vector CAimbot::ClampAngle(Vector angle) {
	while (angle.y > 180) angle.y -= 360;
	while (angle.y < -180) angle.y += 360;
	if (angle.x > 89.0f) angle.x = 89.0f;
	if (angle.x < -89.0f) angle.x = -89.0f;
	angle.z = 0.f;

	return angle;
}

Vector CAimbot::NormalizeAngle(Vector angle) {
	while (angle.x < -180.0f) angle.x += 360.0f;
	while (angle.x > 180.0f) angle.x -= 360.0f;
	while (angle.y < -180.0f) angle.y += 360.0f;
	while (angle.y > 180.0f) angle.y -= 360.0f;
	while (angle.z < -180.0f) angle.z += 360.0f;
	while (angle.z > 180.0f) angle.z -= 360.0f;

	return angle;
}

bool CAimbot::CanShoot() {
	DWORD WeaponEntity = Misc.GetWeaponEntity(Offsets.LocalBase);
	int WeaponClip = Memory::Read<int>(WeaponEntity + Offsets.m_iClip1);
	if (WeaponClip > 0) {
		int tickbase = Memory::Read<int>(Offsets.LocalBase + Offsets.m_nTickBase);
		CGlobalVarsBase var = Memory::Read<CGlobalVarsBase>(Offsets.dwEngine + Offsets.dwGlobalVars);
		float servertime = tickbase * var.interval_per_tick;
		float nextattack = Memory::Read<float>(WeaponEntity + Offsets.m_flNextPrimaryAttack);
		if (nextattack < servertime) {
			return true;
		}
	}
	return false;
}


/*
void CAimbot::ClampAngle(Vector& angles) {
	if (angles.x != angles.x)
	{
		angles.x = 0;
	}
	if (angles.y != angles.y)
	{
		angles.y = 0;
	}
	if (angles.x < -89.0f)
		angles.x = 89.0f;
	if (angles.x >  89.0f)
		angles.x = 89.0f;
	if (angles.y < -180.0f)
		angles.y += 360.0f;
	if (angles.y >  180.0f)
		angles.y -= 360.0f;
	if (angles.z != 0.0f)
		angles.z = 0.0f;
}

void CAimbot::NormalizeAngle(Vector& angle) {
	if (angle.x != angle.x)
	{
		angle.x = 0;
	}
	if (angle.y != angle.y)
	{
		angle.y = 0;
	}
	while (angle.x > 180.0f)
		angle.x -= 360.0f;

	while (angle.x < -180.0f)
		angle.x += 360.0f;

	while (angle.y > 180.0f)
		angle.y -= 360.0f;

	while (angle.y < -180.0f)
		angle.y += 360.0f;

	while (angle.z > 180.0f)
		angle.z -= 360.0f;

	while (angle.z < -180.0f)
		angle.z += 360.0f;
	ClampAngle(angle);
}
*/

Vector CAimbot::SmoothAngle(Vector src, Vector dst, float smoothx, float smoothy) {
	smoothx += 1.f;	//if (smoothx < 1.f) smoothx = 1.f;
	smoothy += 1.f;	//if (smoothy < 1.f) smoothy = 1.f;
	Vector Angle;
	Angle = dst - src;
	Angle = ClampAngle(Angle);
	Angle.x = src.x + Angle.x / smoothx; //		|	Pitch	up/down		^/v
	Angle.y = src.y + Angle.y / smoothy; //		-	Yaw		right/left	>/<
	return Angle;
}

void CAimbot::MakeVector(Vector angle, Vector& vector) {
	float pitch = float(angle[0] * M_PI / 180);
	float yaw = float(angle[1] * M_PI / 180);
	float tmp = float(cos(pitch));
	vector[0] = float(-tmp * -cos(yaw));
	vector[1] = float(sin(yaw)*tmp);
	vector[2] = float(-sin(pitch));
}