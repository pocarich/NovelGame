#include"../header/BGMMgr.h"
#include"../header/Function.h"

MHandle BGMMgr::BGM[bgmNum];
bool BGMMgr::BGMStartFlag[bgmNum];
bool BGMMgr::BGMStopFlag[bgmNum];

void BGMMgr::Load()
{
	for (int i = 0; i < bgmNum; i++)
	{
		stringstream filePath;
		filePath << "data/bgm/bgm" << Function::NumToStringFillZero(i, 3) << ".mp3";

		BGM[i] = LoadSoundMem(filePath.str().c_str());

		assert(BGM[i] != 0 && "BGMMgr::Load()‚É‚ÄBGM‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
	}

	for (int i = 0; i < bgmNum; i++)
	{
		BGMStartFlag[i] = false;
		BGMStopFlag[i] = false;
	}
}

void BGMMgr::Play()
{
	for (int i = 0; i < bgmNum; i++)
	{
		if (BGMStartFlag[i])
		{
			BGMStartFlag[i] = false;
			if (CheckSoundMem(BGM[i]) == 0)
			{
				PlaySoundMem(BGM[i], DX_PLAYTYPE_LOOP);
			}
		}
		if (BGMStopFlag[i])
		{
			BGMStopFlag[i] = false;
			StopSoundMem(BGM[i]);
		}
	}
}

void BGMMgr::UpdateStartFlag(int num)
{
	BGMStartFlag[num] = true;
}

void BGMMgr::UpdateStopFlag(int num)
{
	BGMStopFlag[num] = true;
}

void BGMMgr::StopAllBGM()
{
	for (int i = 0; i < bgmNum; i++)
	{
		StopSoundMem(BGM[i]);
	}
}