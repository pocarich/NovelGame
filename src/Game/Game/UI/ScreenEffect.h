#pragma once

#include"Define.h"

class ScreenEffect
{
private:
	static vector<GHandle> imageList;
private:
	int id;
	int timer;
	int alpha;
	int type;
	bool endFlag;
private:
public:
	static void Load();
public:
	ScreenEffect(int id,int type);
	~ScreenEffect();
	void Update();
	void Draw()const;
	bool GetEndFlag()const { return endFlag; }
	int GetID()const { return id; }
};