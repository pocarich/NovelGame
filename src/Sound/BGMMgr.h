
/*   BGMä«óù   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"

class BGMMgr :public Singleton
{
private:
	static const int bgmNum = 10;
private:
	static MHandle BGM[bgmNum];
	static bool BGMStartFlag[bgmNum];
	static bool BGMStopFlag[bgmNum];
public:
	static void Load();
	static void Play();
	static void UpdateStartFlag(int);
	static void UpdateStopFlag(int);
	static void StopAllBGM();
};
