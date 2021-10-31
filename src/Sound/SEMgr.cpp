#include"../header/SEMgr.h"
#include"../header/Function.h"

MHandle SEMgr::SEList[seNum];
bool SEMgr::SEFlag[seNum];

void SEMgr::Load()
{
	for (int i = 0; i < seNum; i++)
	{
		stringstream filePath;
		filePath << "data/se/se" << Function::NumToStringFillZero(i, 3) << ".mp3";

		SEList[i] = LoadSoundMem(filePath.str().c_str());

		assert(SEList[i] != 0 && "SEMgr::Load()‚É‚ÄSE‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
	}

	for (int i = 0; i < seNum; i++)
	{
		SEFlag[i] = false;
	}
}

void SEMgr::Play()
{
	for (int i = 0; i < seNum; i++)
	{
		if (SEFlag[i])
		{
			PlaySoundMem(SEList[i], DX_PLAYTYPE_BACK);
			SEFlag[i] = false;
		}
	}
}

void SEMgr::UpdateFlag(int num)
{
	SEFlag[num] = true;
}

void SEMgr::StopAllSE()
{
	for (int i = 0; i < seNum; i++)
	{
		StopSoundMem(SEList[i]);
	}
}