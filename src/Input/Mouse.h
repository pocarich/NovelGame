#pragma once

#include"Define.h"
#include"Class.h"

class Mouse
{
	static bool click[3];							//キー入力状態の格納
	static bool clickPre[3];						//キー入力更新前の入力状態を保存
	static bool clickOnce[3];						//キー入力状態の格納(長押し判定なし)
private:
	Mouse() {};
	Mouse(const Mouse&) {};
	Mouse& operator =(const Mouse&) {};
public:
	static void Update();							//キー入力更新関連の関数の統括
	static bool ClickOnce(int);						//キー入力(非長押し)
	static bool Click(int);							//キー入力(長押し対応)
	static Vector2<double> GetMousePos();
};