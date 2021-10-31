#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"
#include"Class.h"

class Title
{
	bool stateEndFlag;
	bool pushStartFlag;
	int timer;
	int darkAlpha;
	thread* th;
	char command[256];
	bool inputFlag;
	bool endFlag;
private:
	void Console();
public:
	Title();
	~Title();
	void Update();
	void Draw()const;
	bool GetStateEndFlag()const { return stateEndFlag; }
};