#include"../header/SystemMgr.h"
#include"../header/KeyBoard.h"
#include"../header/Mouse.h"
#include"../header/ColorMgr.h"
#include"../header/FontMgr.h"
#include"../header/SEMgr.h"
#include"../header/BGMMgr.h"
#include"../header/VoiceMgr.h"
#include"../header/Game.h"
#include"../header/Environment.h"
#include"../header/Game.h"
#include"../header/PlayerData.h"
#include"../header/ChoiceButton.h"
#include"../header/Character.h"
#include"../header/ScreenEffect.h"

SystemMgr::SystemMgr()
{
	SetMainWindowText("Adventure");
	SetAlwaysRunFlag(true);
	ChangeWindowMode(TRUE);

	int w = 1366;
	int h = 768;
	const int marginVertical = 50;
	const int marginHorizontal = (int)(marginVertical*(double)w / h);
	Environment::SetWindowSize(w - marginHorizontal, h - marginVertical);

	SetGraphMode(w - marginHorizontal, h - marginVertical, 16);
	SetWindowPosition((marginHorizontal-20)/2, (marginVertical-30)/2);

	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	AddFont();

	ColorMgr::Load();
	FontMgr::Load();
	SEMgr::Load();
	BGMMgr::Load();
	VoiceMgr::Load();
	Game::Init();
	PlayerData::Init();
	Game::Load();
	Character::Load();
	KeyBoard::Init();
	ScreenEffect::Load();
	ChoiceButton::Load();

	gameMgr = new GameMgr();
	fpsMgr = new FPSMgr();
}

SystemMgr::~SystemMgr()
{
	DxLib_End();
	DeleteFont();

	delete gameMgr;
	delete fpsMgr;
}

void SystemMgr::AddFont()
{
	
}

void SystemMgr::DeleteFont()
{
	
}

void SystemMgr::Loop()
{
	while (Process())
	{
		KeyBoard::Update();								       //キーボード入力の更新
		Mouse::Update();
		BGMMgr::Play();
		SEMgr::Play();
		VoiceMgr::Play();
		gameMgr->Main();                                       //ゲームのメイン処理
		fpsMgr->Main();
	}
}

bool SystemMgr::Process()
{
	if (ScreenFlip())return false;								//裏画面を表画面にコピー
	if (ProcessMessage())return false;							//ウィンドウのメッセージ処理
	if (ClearDrawScreen())return false;							//裏画面のクリア
	if (KeyBoard::PushOnce(KEY_INPUT_ESCAPE))return false;
	return true;
}