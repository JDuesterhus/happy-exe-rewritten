#pragma once

#include "Misc.h"
#include "resource.h"
#include "Offsets.h"
#include "define.h"
#include "Settings.h"
#include "Aimbot.h"
//#include "vector.h"

#include <cstdlib>
#include <iomanip>
#include <sys/timeb.h>



class CVisuals
{
public:
	void Glow();
	void Chams();
	void Others();
	void BombTimer();
private:

	struct csGlowEnt {
		DWORD dwBase;						//4 bytes
		float r;							//4 bytes
		float g;							//4 bytes
		float b;							//4 bytes
		float m_flGlowAlpha;				//4 bytes
		char m_unk[4];						//4 bytes
		float m_flUnk;						//4 bytes
		float m_flBloomAmount;				//4 bytes
		float m_flUnk1;						//4 bytes
		bool m_bRenderWhenOccluded;			//1 byte
		bool m_bRenderWhenUnoccluded;		//1 byte
		bool m_bFullBloomRender;			//1 byte
		char m_unk1;						//1 byte
		int m_nFullBloomStencilTestValue;	//4 bytes
		int m_nGlowStyle;					//4 bytes
		int m_nSplitScreenSlot;				//4 bytes
		int m_nNextFreeSlot;				//4 bytes
	}; csGlowEnt sGlowEnt;					//sizeof(csGlowEnt) -> 56 bytes | 0x38

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

	int GetClassID(DWORD Entity);
	void GlowEntity(DWORD Entity, float r, float g, float b, float a, int style);
	void DyeEntity(DWORD Entity, BYTE r, BYTE g, BYTE b);
	bool EntityIsPistol(int id);
	bool EntityIsSMG(int id);
	bool EntityIsShotgun(int id);
	bool EntityIsRifle(int id);
	bool EntityIsSniper(int id);
	bool EntityIsGrenade(int id);
	bool EntityIsBomb(int id);
	bool EntityIsOther(int id);
	float GetFlashAlpha(DWORD base);
	//const char* GetMapName();
	//const char* GetMapDir();
	//static std::string GetGameDir();
};

extern CVisuals Visuals;