#pragma once

#include "Memory.h"
#include "Offsets.h"
#include "define.h"
#include "Misc.h"
#include "Settings.h"
#include "vector.h"
#include <algorithm>

class CAimbot
{
public:
	void Run();
	void TwoHP();
	void OneEighty();
	void ThreeSixty();
private:
	int bone;
	void DropTarget();
	int Target = -1;
	int TargetOld = -1;
	float iMax;

	Vector BonePos(DWORD boneBase, int boneID);

	int FindBestTarget();
	float AngleDiff(Vector angle, Vector src, Vector dst);
	float VecDist(Vector& fVec1, Vector& fVec2);

	float Dot(const Vector &v1, Vector &v2);
	float GetFov(Vector angle, Vector src, Vector dst);
	Vector CalcAngle(Vector src, Vector dst, float recoilx, float recoily);
	Vector ClampAngle(Vector angle);
	Vector NormalizeAngle(Vector angle);
	Vector SmoothAngle(Vector src, Vector dst, float smoothx, float smoothy);
	void MakeVector(Vector angle, Vector& vector);

	DWORD EntBase(int i);
	DWORD EntBoneMatrix(DWORD base);
	bool EntDormant(DWORD base);
	int EntHealth(DWORD base);
	bool EntSpotted(DWORD base);
	float EntGodTime(DWORD base);
	int EntTeam(DWORD base);
	int EntFlags(DWORD base);
	Vector EntOriginPos(DWORD base);
	Vector EntEyePos(DWORD base);

	Vector MyViewAngle();
	Vector MyOrigin();
	Vector MyEyeAngle();
	Vector MyEyePosition();
	Vector MyAimPunch();
};

extern CAimbot Aimbot;