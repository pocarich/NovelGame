#include"../header/ScreenEffect.h"
#include"../header/ColorMgr.h"
#include"../header/Environment.h"
#include"../header/Function.h"

vector<GHandle> ScreenEffect::imageList;

void ScreenEffect::Load()
{

}

ScreenEffect::ScreenEffect(int id,int type):id(id),type(type)
{
	timer = 0;
	alpha = 255;
	endFlag = false;
}

ScreenEffect::~ScreenEffect()
{

}

void ScreenEffect::Update()
{
	switch (type)
	{
	case 0:
		timer++;
		alpha = 100 + (int)(100.0*sin(2 * M_PI*1.0 / 60.0*timer));
		break;
	}
}

void ScreenEffect::Draw()const
{
	switch (type)
	{
	case 0:
		Function::Alpha(alpha);
		DrawFillBox(0, 0, Environment::GetWindowWidth(), Environment::GetWindowHeight(), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::RED]);
		Function::Alpha(255);
		break;
	}
}