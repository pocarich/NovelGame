#include"../header/PlayerData.h"

array<bool, 1000> PlayerData::flagList;

void PlayerData::Init()
{
	for (int i = 0; i != flagList.size(); i++)
	{
		flagList[i] = false;
	}
}