
/*   アプリケーションのシステム管理   */

#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"
#include"FPSMgr.h"
#include"GameMgr.h"

class SystemMgr
{
	GameMgr* gameMgr;
	FPSMgr* fpsMgr;
private:
	void AddFont();
	void DeleteFont();
	bool Process();
public:
	SystemMgr();
	~SystemMgr();
	void Loop();
};