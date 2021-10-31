#pragma once

#include"Define.h"

class PlayerData
{
private:
	static array<bool, 1000> flagList;
public:
	static void Init();
	static void StandFlag(int i) { flagList[i] = true; }
	static void CancelFlag(int i) { flagList[i] = false; }
	static bool GetFlag(int i) { return flagList[i]; }
};