
/*   SEä«óù   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"

class SEMgr :public Singleton
{
private:
	static const int seNum = 10;
private:
	static MHandle SEList[seNum];
	static bool SEFlag[seNum];
public:
	static void Load();
	static void Play();
	static void UpdateFlag(int);
	static void StopAllSE();
};