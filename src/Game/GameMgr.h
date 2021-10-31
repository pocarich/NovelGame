#pragma once

#include"Define.h"
#include"ColorMgr.h"
#include"FontMgr.h"
#include"Singleton.h"
#include"Title.h"
#include"Game.h"

enum struct GameState
{
	TITLE,
	GAME
};

class GameMgr
{
	GameState state;
	Title* title;
	Game* game;
private:
	void TitleFunc();
	void GameFunc();
public:
	GameMgr();
	~GameMgr();
	void Main();
};
