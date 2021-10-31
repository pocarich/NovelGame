#include"../header/GameMgr.h"
#include"../header/KeyBoard.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"

GameMgr::GameMgr()
{
	title = nullptr;
	game = nullptr;
	state = GameState::TITLE;
}

GameMgr::~GameMgr()
{
	if (title != nullptr)
		delete title;
	if (game != nullptr)
		delete game;
}

void GameMgr::Main()
{
	switch (state)
	{
	case GameState::TITLE:	TitleFunc();	break;
	case GameState::GAME:	GameFunc();		break;
	}
}

void GameMgr::TitleFunc()
{
	if (title == nullptr)
	{
		title = new Title();
	}

	title->Update();
	title->Draw();

	if (title->GetStateEndFlag())
	{
		delete title;
		title = nullptr;
		state = GameState::GAME;
	}
}

void GameMgr::GameFunc()
{
	if (game == nullptr)
	{
		game = new Game();
	}
	
	game->Update();
	game->Draw();
}