#include"../header/Title.h"
#include"../header/KeyBoard.h"
#include"../header/BGMMgr.h"
#include"../header/SEMgr.h"
#include"../header/Function.h"
#include"../header/Environment.h"
#include"../header/Mouse.h"

Title::Title()
{
	stateEndFlag = false;
	pushStartFlag = false;
	timer = 0;
	darkAlpha = 0;
	endFlag = false;
	inputFlag = false;
}

Title::~Title()
{
	
}

void Title::Console()
{
	scanf("%s", command);
	inputFlag = true;
}

void Title::Update()
{
	if (!pushStartFlag)
	{
		if (Mouse::ClickOnce(MOUSE_INPUT_LEFT))
		{
			pushStartFlag = true;
		}
	}
	else
	{
		darkAlpha += 3;
		darkAlpha = min(255, darkAlpha);
		timer++;
		if (timer == 120)
		{
			stateEndFlag = true;
		}
	}
}

void Title::Draw()const
{
	if ((timer / 5) % 2 == 0)
	{
		DrawFormatStringToHandle(470, 470, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[4], "画面をクリックしてスタート！");
	}
	DrawFormatStringToHandle(570, 200, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[7], "皇専");

	Function::Alpha(darkAlpha);

	DrawFillBox(0, 0, Environment::GetWindowWidth(), Environment::GetWindowHeight(), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::BLACK]);

	Function::Alpha(255);
}
