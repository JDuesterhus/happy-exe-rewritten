#pragma once

#include "Memory.h"
#include "Offsets.h"
#include "define.h"
#include "vector.h"
#include "Settings.h"
#include "XorStr.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

class CMisc
{
public:
	void Autopistol();
	void BunnyHop();
	void AutoStrafe();
	void Fakelag();
	void FakelagFix();
	void ChatSpam();
	void WeaponConfig();
	bool CanJump(int flag, bool crouch);
	int GetFlags(DWORD base);
	bool IsZooming(DWORD base);
	bool IsAttacking();
	bool IsAttacking2();
	DWORD GetWeaponEntity(DWORD base);
	int GetCurrentWeapon(DWORD base);
	bool IsReloading(DWORD base);
	float GetWeaponAccuracy(DWORD base);
	int GetShotsFired(DWORD base);
	//int GetShotsFiredPistol();
	bool WeaponValid(int id);
	bool WeaponIsAutomatic(int id);
	bool WeaponIsPistol(int id);
	bool WeaponIsSniper(int id);
	bool WeaponIsKnife(int id);
	float GetSpeed1D();
	float GetSpeed2D();
	float GetSpeed3D(); 
	void Console(const char* command);
private:
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
	#pragma pack(push,1)
	struct ClientCmd_Unrestricted_t {
		char command[200];
		bool delay;
	};
	#pragma pack(pop)



	bool IsJumping();
};

extern CMisc Misc;