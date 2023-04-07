#pragma once

#include "Memory.h"
#include "Offsets.h"
#include "define.h"
#include "Misc.h"
#include "Settings.h"
#include "vector.h"
#include <algorithm>
#include <random>
#include <WinUser.h>

class CAimbot
{
public:
	void Normal();
	//void AntiAim();
	//void RCS();
	//void Silent();

	void TwoHP();
	void OneEighty();
	void ThreeSixty();

	float VecDist(Vector& fVec1, Vector& fVec2); //CHECK IF THIS IS USEFUL FOR RUNBOOST BOT LATER
	float VecDist2D(Vector& fVec1, Vector& fVec2);

	Vector CalcAngle(Vector src, Vector dst, float recoilx, float recoily);
	Vector ClampAngle(Vector angle);
	Vector NormalizeAngle(Vector angle);


	Vector MyViewAngle();
	Vector MyOrigin();
	Vector MyEyeAngle();
	Vector MyEyePosition();
	Vector MyAimPunch();

private:
	int bone;
	void DropTarget();
	int Target = -1;
	int TargetOld = -1;
	float iMax;

	Vector BonePos(DWORD boneBase, int boneID);

	int FindBestTarget();
	float AngleDiff(Vector angle, Vector src, Vector dst);

	float Dot(const Vector& v1, Vector& v2);
	float GetFov(Vector angle, Vector src, Vector dst);
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

	bool CanShoot();

	struct CGlobalVarsBase {
		float realtime;
		int framecount;
		float absolute_frametime;
		float absolute_framestarttimestddev;
		float curtime;
		float frameTime;
		int maxClients;
		int tickcount;
		float interval_per_tick;
		float interpolation_amount;
		int simThicksThisFrame;
		int network_protocol;
	}; CGlobalVarsBase globalVars;

};

extern CAimbot Aimbot;