#include"../header/VoiceMgr.h"
#include"../header/Function.h"

MHandle VoiceMgr::VoiceList[voiceNum];
bool VoiceMgr::VoiceFlag[voiceNum];

void VoiceMgr::Load()
{
	for (int i = 0; i < voiceNum; i++)
	{
		stringstream filePath;
		filePath << "data/voice/voice" << Function::NumToStringFillZero(i, 4) << ".mp3";

		VoiceList[i] = LoadSoundMem(filePath.str().c_str());

		assert(VoiceList[i] != 0 && "VoiceMgr::Load()�ɂ�Voice�̓ǂݍ��݂Ɏ��s���܂����B");
	}

	for (int i = 0; i < voiceNum; i++)
	{
		VoiceFlag[i] = false;
	}
}

void VoiceMgr::Play()
{
	for (int i = 0; i < voiceNum; i++)
	{
		if (VoiceFlag[i])
		{
			PlaySoundMem(VoiceList[i], DX_PLAYTYPE_BACK);
			VoiceFlag[i] = false;
		}
	}
}

void VoiceMgr::UpdateFlag(int num)
{
	VoiceFlag[num] = true;
}

void VoiceMgr::StopAllVoice()
{
	for (int i = 0; i < voiceNum; i++)
	{
		StopSoundMem(VoiceList[i]);
	}
}