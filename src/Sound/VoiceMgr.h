#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"

class VoiceMgr :public Singleton
{
private:
	static const int voiceNum = 1;
private:
	static MHandle VoiceList[voiceNum];
	static bool VoiceFlag[voiceNum];
public:
	static void Load();
	static void Play();
	static void UpdateFlag(int);
	static void StopAllVoice();
};