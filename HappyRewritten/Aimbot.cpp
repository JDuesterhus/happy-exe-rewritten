#include "Aimbot.h"

CAimbot Aimbot;


void CAimbot::DropTarget() {
	Target = -1;
	iMax = 9999.f;
}




void CAimbot::Run() {
	Vector AimAngle; //move
	//DropTarget();
	if (Misc.WeaponCanShoot(Misc.GetCurrentWeapon(Offsets.LocalBase)) && !Misc.IsReloading(Offsets.LocalBase)) {
		Target = FindBestTarget();
		if (Target > 0) {
			AimAngle = CalcAngle(MyEyePosition(), BonePos(EntBoneMatrix(EntBase(Target)), bone), Settings.Aimbot.RCS_Pitch, Settings.Aimbot.RCS_Yaw);
			//NormalizeAngle(AimAngle);
			AimAngle = SmoothAngle(MyViewAngle(), AimAngle, Settings.Aimbot.Aimbot_Smooth_Pitch, Settings.Aimbot.Aimbot_Smooth_Yaw);
			AimAngle = NormalizeAngle(AimAngle);
			AimAngle = ClampAngle(AimAngle);
			Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
		}
		else {
			Target = -1;
		}
	}
}

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
			AimAngle = SmoothAngle(Angle, AngleUP, 10, 10);
			AimAngle = NormalizeAngle(AimAngle);
			AimAngle = ClampAngle(AimAngle);
			Memory::Write<Vector>(Offsets.EngineBase + Offsets.dwClientState_ViewAngles, AimAngle);
			Sleep(1);
		} while (Angle.x > -88.99);
		//throw nade
		Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack2, 5);
		Sleep(200);
		Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack, 5);
		Sleep(80); //78-82
		Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceAttack2, 4);
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
	if (Target != TargetOld && TargetOld != -1) {
		if (Ent.Health[TargetOld] < 1) {
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