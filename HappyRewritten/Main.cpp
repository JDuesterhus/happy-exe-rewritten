#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <cstdlib>
#include <stdio.h> 
#include <stdlib.h>
#include <ctime>
#include <time.h>


#include "Offsets.h"
#include "define.h"
#include "Memory.h"
#include "Visuals.h"
#include "Trigger.h"
#include "Aimbot.h"
#include "Misc.h"
#include "Settings.h"
#include "vector.h"
#include "IniReader.h"
#include "XorStr.h"
#include "resource.h"

#pragma comment( lib, "winmm" )



using namespace std;

int isConnected;
//HWND WindowCSGO;
//HWND WindowCurrent;

void ActivationThread();
//void GameThread();
void GlowThread();
void ChamsThread();
void OthersThread();
void TriggerbotThread();
void BunnyHopThread();
void AutoStrafeThread();
void AutoPistolThread();
void FakelagThread();
void FakelagFixThread();
void SpammerThread();
void BombTimerThread();
void AimbotThread();
//void RCSThread();
void WeaponConfigThread();

Memory Mem;


void exiting() {
	float brightness = 0;
	DWORD thisPtr = (int)(Offsets.dwEngine + Offsets.model_ambient_min - 0x2c);
	DWORD xored = *(DWORD*)&brightness ^ thisPtr;
	Memory::Write<DWORD>(Offsets.dwEngine + Offsets.model_ambient_min, xored);
	Memory::Write<BYTE>(Offsets.dwClient + Offsets.force_update_spectator_glow, 0x74);
	Memory::Write<bool>(Offsets.dwEngine + Offsets.dwbSendPackets, true);
	Memory::Write<int>(Offsets.EngineBase + Offsets.clientstate_delta_ticks, -1);
}

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType) {
	if (dwCtrlType == CTRL_CLOSE_EVENT) {
		//exiting();
		exit(0);
		return TRUE;
	}
	return FALSE;
}

void PatternScan() {
	//if im done being lazy i'll add more important offset scans here
	Offsets.ClientCMDArray = Mem.FindPatternArr(Offsets.dwEngine, Offsets.dwEngineSize, XorStr("xxxx?????xx????xxx????x????xxxxxxxxx"), 36, 0x55, 0x8B, 0xEC, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x75, 0x0C, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x05, 0x8B, 0x01, 0xFF, 0x50, 0x34, 0x50, 0xA1);
	Offsets.ClientCMD = Offsets.ClientCMDArray - Offsets.dwEngine;

	//Offsets.PostProcessArray = Mem.FindPatternArr(Offsets.dwClient, Offsets.dwClientSize, "xx?????xxxxx????", 16, 0x80, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x56, 0x57, 0x0F, 0x85, 0x00, 0x00, 0x00, 0x00) + 2;
	//Offsets.PostProcess = Offsets.PostProcessArray - Offsets.dwClient;


	//Offsets.LvlBypassArray = Mem.FindPatternArr(Offsets.dwClient, Offsets.dwClientSize, "xxxxxxxxx", 36, 0x55, 0x8B, 0xEC, 0x8B, 0x55, 0x08, 0x8B, 0xCA, 0x53);
	//Offsets.LvlBypass = Offsets.LvlBypassArray - Offsets.dwClient;

	//Offsets.ForceAttack2Array = Mem.FindPatternArr(Offsets.dwClient, Offsets.dwClientSize, "xxxx????", 8, 0x70, 0xC7, 0x7D, 0x31, 0x00, 0x00, 0x00, 0x00);
	//Offsets.ForceAttack2 = Memory::Read<DWORD>(Offsets.ForceAttack2Array - Offsets.dwClient);


	//Offsets.LobbyInfoArray = Mem.FindPatternArr(Offsets.dwClient, Offsets.dwClientSize, "xx?????xx????xxxx", 17, 0xC6, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x85, 0xC9, 0x74, 0x22);
	//Offsets.LobbyInfo = Memory::Read<DWORD>(Offsets.LobbyInfoArray - Offsets.dwClient - 0x1000 + 0x50);


	//cout << "LvlBypassArray " << hex << Offsets.LvlBypassArray << endl;
	//cout << "LvlBypass " << hex << Offsets.LvlBypass << endl;
	//cout << dec;
}

enum ConsolColor {
	BLACK = 0,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE
};

void SetConsoleColor(int fg, int bg) {
	int color = fg + bg * 16;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void SetWindow() {
	//GETTING CONSOLE HANDLE
	HWND ConsoleWindow = GetConsoleWindow();
	//SET WINDOW TRANSPARENCY
	SetWindowLong(ConsoleWindow, GWL_EXSTYLE, GetWindowLong(ConsoleWindow, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(ConsoleWindow, 0, Settings.Misc.Window_Transparency, LWA_ALPHA);
	//RESIZE WINDOW
	RECT dimension;
	GetWindowRect(ConsoleWindow, &dimension); //stores the console's current dimensions
	MoveWindow(ConsoleWindow, dimension.left, dimension.top, 320, 440, TRUE);
	//REMOVE WINDOW SCROLLBARS
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(ConsoleHandle, &info);
	COORD new_size = {
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(ConsoleHandle, new_size);
}

struct new_bool :numpunct<char> {
	string_type do_truename() const {
		return XorStr("ON ");
	}
	string_type do_falsename() const {
		return XorStr("OFF");
	}
};

void menu() {
	system(XorStr("cls"));
	cout << XorStr("   ______________________________") << endl;
	cout << endl;
	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Glow ESP: ");
	cout << setw(5) << setfill(' ') << Settings.ESP.Glow;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Chams: ");
	cout << setw(5) << setfill(' ') << Settings.ESP.Chams;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Aimbot: ");
	cout << setw(5) << setfill(' ') << Settings.Aimbot.Aimbot;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Triggerbot: ");
	cout << setw(5) << setfill(' ') << Settings.Triggerbot.Triggerbot;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("AutoPistol: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Autopistol;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Radar: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Radar;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("BunnyHop: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Bunnyhop;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Autostrafe: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Autostrafe;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Spammer: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Spammer;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Remove Hands: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Remove_Hands;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Remove Ragdoll: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Remove_Ragdoll;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Remove Fog: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Remove_Fog;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Remove Smoke: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Remove_Smoke;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Reduce Flash: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Reduce_Flash;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Overwrite FOV: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Overwrite_FOV;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Nightmode: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Nightmode;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Fakelag: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Fakelag;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;

	cout << XorStr(" |");
	cout << right << setw(20) << setfill(' ') << XorStr("Bomb Timer: ");
	cout << setw(5) << setfill(' ') << Settings.Misc.Bomb_Timer;
	cout << setw(8) << setfill(' ') << XorStr("|") << endl;
	cout << XorStr("   ______________________________") << endl;
}

int main(int argc, char* argv[]) {
	//TITLE WITH BUILD DATE/TIME
	SetConsoleTitle(XorStr("Happy.exe | " __DATE__ " - " __TIME__ " BUILD"));
	//FINDING PROCESS AND MODULES
	cout << XorStr("------------------------------------") << endl;
	SetConsoleColor(LIGHT_AQUA, BLACK);
	//LOADING MAIN CONFIG
	Settings.LoadConfig(XorStr(".\\config\\default.ini"));
	//SetWindow();
	Sleep(500);
	cout << XorStr("WAITING FOR GAME");
	while (!Memory::hProc) {
		Memory::Process(XorStr("csgo.exe"));
		cout << ".";
		Sleep(500);
	}
	cout << endl << XorStr("WAITING FOR MODULES");
	while (!Offsets.dwEngineSize && !Offsets.dwClientSize) {
		cout << ".";
		Offsets.dwClient = Memory::Module(XorStr("client.dll"), Offsets.dwClientSize);
		Offsets.dwEngine = Memory::Module(XorStr("engine.dll"), Offsets.dwEngineSize);
		Sleep(500);
	}
	//cout << "client_panorama raw: " << Offsets.dwClient << endl;
	//cout << "engine raw: " << Offsets.dwEngine << endl;
	//cout << "client_panorama size: " << Offsets.dwClientSize << endl;
	//cout << "engine size: " << Offsets.dwEngineSize << endl;
	//Sleep(5000);
	//LOADING/DOWNLOADING OFFSETS/NETVARS
	cout << endl << XorStr("LOADING OFFSETS/NETVARS") << endl;
	Offsets.DownloadOffsets();
	Sleep(500);
	//SCAN OFFSETS/NETVARS
	cout << XorStr("SCANNING PATTERNS") << endl;
	PatternScan();
	Sleep(500);
	cout << XorStr("DONE") << endl;
	SetConsoleColor(WHITE, BLACK);
	cout << XorStr("------------------------------------") << endl;
	Sleep(500);
	Offsets.EngineBase = Memory::Read<DWORD>(Offsets.dwEngine + Offsets.dwClientState);
	//EXECUTE ON EXIT
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);
	set_terminate(exiting);
	atexit(exiting);
	//COOLER BOOLEAN NAMES
	cout << boolalpha;
	cout.imbue(locale(cout.getloc(), new new_bool));
	//PSEUDO RANDOM SEED
	srand((unsigned int)time(NULL) - (unsigned int)GetTickCount() + (unsigned int)GetCurrentProcessId());
	int startsound = (rand() % 18 + 1);
	//COOL START SOUND EFFECTS
	if (startsound == 1) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START1), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 2) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START2), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 3) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START3), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 4) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START4), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 5) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START5), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 6) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START6), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 7) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START7), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 8) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START8), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 9) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START9), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 10) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START10), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 11) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START11), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 12) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START12), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 13) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START13), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 14) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START14), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 15) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START15), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 16) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START16), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 17) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START17), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	if (startsound == 18) PlaySound(MAKEINTRESOURCE(IDR_SOUND_START18), GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);
	menu();
	//THREADS
	thread Activation_thread = thread(ActivationThread);
	//thread Game_thread = thread(GameThread);
	thread Glow_Thread = thread(GlowThread);
	thread Chams_Thread = thread(ChamsThread);
	thread Others_Thread = thread(OthersThread);
	thread Triggerbot_thread = thread(TriggerbotThread);
	thread BunnyHop_thread = thread(BunnyHopThread);
	thread AutoStrafe_Thread = thread(AutoStrafeThread);
	thread AutoPistol_thread = thread(AutoPistolThread);
	thread Fakelag_thread = thread(FakelagThread);
	thread FakelagFix_thread = thread(FakelagFixThread);
	thread Spammer_thread = thread(SpammerThread);
	thread BombTimer_thread = thread(BombTimerThread);
	thread Aimbot_thread = thread(AimbotThread);
	//thread RCS_thread = thread(RCSThread);
	thread WeaponConfig_thread = thread(WeaponConfigThread);

	Activation_thread.join();
	//Game_thread.join();
	Glow_Thread.join();
	Chams_Thread.join();
	Others_Thread.join();
	Triggerbot_thread.join();
	BunnyHop_thread.join();
	AutoStrafe_Thread.join();
	AutoPistol_thread.join();
	Fakelag_thread.join();
	FakelagFix_thread.join();
	Spammer_thread.join();
	BombTimer_thread.join();
	Aimbot_thread.join();
	//RCS_thread.join();
	WeaponConfig_thread.join();

	return(EXIT_SUCCESS);
}



void Activation(bool boolean) {
	if (boolean) {
		PlaySound(MAKEINTRESOURCE(IDR_SOUND_ON), GetModuleHandle(NULL), SND_RESOURCE);
		Sleep(5);
	}
	else {
		PlaySound(MAKEINTRESOURCE(IDR_SOUND_OFF), GetModuleHandle(NULL), SND_RESOURCE);
	}
	menu();
}


void ActivationThread() {
	bool once = Settings.ESP.Glow;
	static int OldTeam = 0;
	while (true) {
		isConnected = Memory::Read<int>(Offsets.EngineBase + Offsets.dwClientState_State);
		Offsets.LocalBase = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwLocalPlayer);
		if (isConnected != 6) Offsets.LocalBase = 0; //temp crash fix


		//
		//if (MyOriginPos.y > -85 && MyOriginPos.y < 55) {
		//	if (MyOriginPos.x < -2355 && MyOriginPos.x > -2500) {
		//		if (MyOriginPos.z > 11710 && MyOriginPos.z < 11790) {
		//			cout << "trigger" << endl;
		//			Sleep(300);
		//			Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceForward, 4);
		//			Sleep(600);
		//			Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceLeft, 5);
		//			Sleep(300);
		//			Memory::Write<BYTE>(Offsets.dwClient + Offsets.dwForceJump, 5);
		//			Sleep(8000);
		//		}
		//	}
		//



		//UPDATE ON TEAMSWITCH
		int CurrentTeam = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iTeamNum);
		int CurrentHealth = Memory::Read<int>(Offsets.LocalBase + Offsets.m_iHealth);
		if (CurrentTeam != OldTeam) {
			Memory::Write<BYTE>(Offsets.dwClient + Offsets.force_update_spectator_glow, 0x74);
			Sleep(1000);
			Memory::Write<BYTE>(Offsets.dwClient + Offsets.force_update_spectator_glow, 0xEB);
		}
		OldTeam = CurrentTeam;

		if (GetAsyncKeyState(Settings.Hotkey.Reload_Config) & Pressed) {
			Settings.LoadConfig(XorStr(".\\config\\default.ini"));
			PlaySound(MAKEINTRESOURCE(IDR_SOUND_ON), GetModuleHandle(NULL), SND_RESOURCE);
			once = true;
			Memory::Write<int>(Offsets.EngineBase + Offsets.clientstate_delta_ticks, -1);
			SetWindow();
			menu();
			Sleep(200);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Glow) & Pressed) {
			Settings.ESP.Glow = !Settings.ESP.Glow;
			Activation(Settings.ESP.Glow);
			once = true;
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Chams) & Pressed) {
			float brightness = 0;
			DWORD thisPtr = (int)(Offsets.dwEngine + Offsets.model_ambient_min - 0x2c);
			DWORD xored = *(DWORD*)&brightness ^ thisPtr;
			Memory::Write<DWORD>(Offsets.dwEngine + Offsets.model_ambient_min, xored);
			Memory::Write<int>(Offsets.EngineBase + Offsets.clientstate_delta_ticks, -1);
			Settings.ESP.Chams = !Settings.ESP.Chams;
			Activation(Settings.ESP.Chams);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Triggerbot) & Pressed) {
			Settings.Triggerbot.Triggerbot = !Settings.Triggerbot.Triggerbot;
			Activation(Settings.Triggerbot.Triggerbot);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Autopistol) & Pressed) {
			Settings.Misc.Autopistol = !Settings.Misc.Autopistol;
			Activation(Settings.Misc.Autopistol);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Radar) & Pressed) {
			Settings.Misc.Radar = !Settings.Misc.Radar;
			Activation(Settings.Misc.Radar);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Bunnyhop) & Pressed) {
			Settings.Misc.Bunnyhop = !Settings.Misc.Bunnyhop;
			Activation(Settings.Misc.Bunnyhop);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Autostrafe) & Pressed) {
			Settings.Misc.Autostrafe = !Settings.Misc.Autostrafe;
			Activation(Settings.Misc.Autostrafe);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Spammer) & Pressed) {
			Settings.Misc.Spammer = !Settings.Misc.Spammer;
			Activation(Settings.Misc.Spammer);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Remove_Hands) & Pressed) {
			Memory::Write<int>(Offsets.EngineBase + Offsets.clientstate_delta_ticks, -1);
			Settings.Misc.Remove_Hands = !Settings.Misc.Remove_Hands;
			Activation(Settings.Misc.Remove_Hands);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Remove_Ragdoll) & Pressed) {
			Memory::Write<int>(Offsets.EngineBase + Offsets.clientstate_delta_ticks, -1);
			Settings.Misc.Remove_Ragdoll = !Settings.Misc.Remove_Ragdoll;
			Activation(Settings.Misc.Remove_Ragdoll);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Remove_Fog) & Pressed) {
			Memory::Write<int>(Offsets.EngineBase + Offsets.clientstate_delta_ticks, -1);
			Settings.Misc.Remove_Fog = !Settings.Misc.Remove_Fog;
			Activation(Settings.Misc.Remove_Fog);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Remove_Smoke) & Pressed) {
			Memory::Write<int>(Offsets.EngineBase + Offsets.clientstate_delta_ticks, -1);
			Settings.Misc.Remove_Smoke = !Settings.Misc.Remove_Smoke;
			Activation(Settings.Misc.Remove_Smoke);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Reduce_Flash) & Pressed) {
			Settings.Misc.Reduce_Flash = !Settings.Misc.Reduce_Flash;
			if (!Settings.Misc.Reduce_Flash)
				Memory::Write<float>(Offsets.LocalBase + Offsets.m_flFlashMaxAlpha, 255);
			Activation(Settings.Misc.Reduce_Flash);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Overwrite_FOV) & Pressed) {
			Settings.Misc.Overwrite_FOV = !Settings.Misc.Overwrite_FOV;
			if (!Settings.Misc.Overwrite_FOV)
				Memory::Write<int>(Offsets.LocalBase + 0x332C, 90);
			Activation(Settings.Misc.Overwrite_FOV);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Nightmode) & Pressed) {
			Memory::Write<int>(Offsets.EngineBase + Offsets.clientstate_delta_ticks, -1);
			Settings.Misc.Fakelag = !Settings.Misc.Fakelag;
			Activation(Settings.Misc.Fakelag);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Toggle_Fakelag) & Pressed) {
			Settings.Misc.Fakelag = !Settings.Misc.Fakelag;
			Activation(Settings.Misc.Fakelag);
		}
		if (GetAsyncKeyState(Settings.Hotkey.Bind_2HP) & Pressed) {
			Aimbot.TwoHP();
		}
		if (GetAsyncKeyState(Settings.Hotkey.Bind_180) & Pressed) {
			Aimbot.OneEighty();
		}
		if (GetAsyncKeyState(Settings.Hotkey.Bind_360) & Pressed) {
			Aimbot.ThreeSixty();
		}
		if (GetAsyncKeyState(Settings.Hotkey.Panic_Exit) & Pressed) {
			exit(0);
		}
		// PATCHING GLOW FIX
		if (Settings.ESP.Glow && once) {
			Memory::Write<BYTE>(Offsets.dwClient + Offsets.force_update_spectator_glow, 0xEB);
			once = false;
		}
		// UNPATCHING GLOW FIX
		if (!Settings.ESP.Glow && once) {
			Memory::Write<BYTE>(Offsets.dwClient + Offsets.force_update_spectator_glow, 0x74);
			once = false;
		}
		Sleep(50);
	}
}

//ignore
//this is for automatic reattaching if the game closes/crashes but i need to do some changes to the memory class before
//void GameThread() {
//	static bool GameFound = false;
//	static bool GameAttached = false;
//	while (true) {
//		WindowCurrent = GetForegroundWindow();
//		WindowCSGO = FindWindow(0, "Counter-Strike: Global Offensive");
//
//		if (WindowCSGO != NULL) {
//			GameFound = true;
//			//cout << "found game" << endl;
//		}
//		if (WindowCSGO == NULL) {
//			GameFound = false;
//			GameAttached = false;
//			//cout << "game not found" << endl << endl << endl << endl << endl;
//			Mem.hPID = 0;
//			isConnected = -1;
//			Offsets.dwClient = 0;
//			Offsets.dwClientSize = 0;
//			Offsets.dwEngine = 0;
//			Offsets.dwEngineSize = 0;
//		}
//		if (GameFound && !GameAttached){
//			GameAttached = true;
//			while (!Mem.Process("csgo.exe")) {
//				Sleep(100);
//			}
//			//cout << "found process" << endl;
//			while (!Offsets.dwClientSize) {
//				cout << "finding clientdll" << endl;
//				Offsets.dwClient = Mem.Module("client_panorama.dll", Offsets.dwClientSize);
//				Sleep(100);
//			}
//			while (!Offsets.dwEngineSize) {
//				cout << "finding enginedll" << endl;
//				Offsets.dwEngine = Mem.Module("engine.dll", Offsets.dwEngineSize);
//				Sleep(100);
//			}
//			cout << "found modules" << endl;
//			cout << "clientdll module" << Offsets.dwClient << endl;
//			cout << "enginedll module" << Offsets.dwEngine << endl;
//
//			Offsets.EngineBase = Memory::Read<DWORD>(Offsets.dwEngine + Offsets.dwClientState);
//			Offsets.LocalBase = Memory::Read<DWORD>(Offsets.dwClient + Offsets.dwLocalPlayer);
//			//cout << "scanned bases" << endl;
//			Offsets.DownloadOffsets();
//			//cout << "loaded offsets" << endl;
//			PatternScan();
//			//cout << "patterns scanned" << endl;
//		}
//		Sleep(100);
//	}
//}


void GlowThread() {
	while (true) {
		Sleep(64);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (!Settings.Misc.Radar && !Settings.ESP.Glow)
				continue;

			Visuals.Glow();
		}
		else {
			Sleep(5000);
		}
	}
}

void ChamsThread() {
	while (true) {
		Sleep(64);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (!Settings.ESP.Chams)
				continue;

			Visuals.Chams();
		}
		else {
			Sleep(5000);
		}
	}
}

void OthersThread() {
	while (true) {
		Sleep(64);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (!Settings.Misc.Remove_Hands && !Settings.Misc.Remove_Ragdoll && !Settings.Misc.Remove_Smoke && !Settings.Misc.Remove_Fog && !Settings.Misc.Nightmode && !Settings.Misc.Reduce_Flash && !Settings.Misc.Overwrite_FOV && !Settings.Misc.Swap_Knife_Hand)
				continue;

			Visuals.Others();
		}
		else {
			Sleep(5000);
		}
	}
}

void TriggerbotThread() {
	while (true) {
		Sleep(1);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (Settings.Triggerbot.Triggerbot_Hotkey && !GetAsyncKeyState(Settings.Hotkey.Hold_TriggerBot) || !Settings.Triggerbot.Triggerbot)
				continue;

			Trigger.Run();
		}
		else {
			Sleep(5000);
		}
	}
}

void BunnyHopThread() {
	while (true) {
		Sleep(1);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (!Settings.Misc.Bunnyhop)
				continue;

			Misc.BunnyHop();
		}
		else {
			Sleep(5000);
		}
	}
}

void AutoStrafeThread() {
	while (true) {
		Sleep(15.625);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (!Settings.Misc.Autostrafe)
				continue;

			Misc.AutoStrafe();
		}
		else {
			Sleep(5000);
		}
	}
}

void AutoPistolThread() {
	while (true) {
		Sleep(15.625);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (!Settings.Misc.Autopistol)
				continue;

			Misc.Autopistol();
		}
		else {
			Sleep(5000);
		}
	}
}

void FakelagThread() {
	while (true) {
		Sleep(1);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (Settings.Misc.Fakelag_Hotkey && !GetAsyncKeyState(Settings.Hotkey.Hold_Fakelag) || !Settings.Misc.Fakelag)
				continue;

			Misc.Fakelag();
		}
		else {
			Sleep(5000);
		}
	}
}

void FakelagFixThread() {
	while (true) {
		Sleep(10);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (Settings.Misc.Fakelag_Hotkey && !GetAsyncKeyState(Settings.Hotkey.Hold_Fakelag) || !Settings.Misc.Fakelag)
				continue;

			Misc.FakelagFix();
		}
		else {
			Sleep(5000);
		}
	}
}

void SpammerThread() {
	while (true) {
		Sleep(10);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (!Settings.Misc.Spammer)
				continue;

			Misc.ChatSpam();
		}
		else {
			Sleep(5000);
		}
	}
}

void BombTimerThread() {
	while (true) {
		Sleep(10);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (!Settings.Misc.Bomb_Timer)
				continue;

			Visuals.BombTimer();
		}
		else {
			Sleep(5000);
		}
	}
}

void AimbotThread() {
	while (true) {
		Sleep(6.25);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (Settings.Aimbot.Aimbot_Hotkey && !GetAsyncKeyState(Settings.Hotkey.Hold_Aimbot) || !Settings.Aimbot.Aimbot)
				continue;
			//if (!Settings.Aimbot.Aimbot_Silent)
			Aimbot.Normal();
			//if (Settings.Aimbot.Aimbot_Silent)
			//	Aimbot.Silent();
		}
		else {
			Sleep(5000);
		}
	}
}

void WeaponConfigThread() {
	while (true) {
		Sleep(64);
		if (isConnected == SIGNONSTATE_FULL && Offsets.LocalBase != 0) {
			if (Settings.Misc.Weapon_Config == 0)
				continue;

			Misc.WeaponConfig();
		}
		else {
			Sleep(5000);
		}
	}
}

