#pragma once

#include "Memory.h"
#include "Offsets.h"
#include "Misc.h"
#include "Settings.h"

class CTrigger
{
public:
	void Run();

private:
	void TriggerBullets();
	void TriggerShoot();
	float DashSpeed();

};

extern CTrigger Trigger;