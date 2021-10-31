#include"../header/Mouse.h"

bool Mouse::click[3];
bool Mouse::clickOnce[3];
bool Mouse::clickPre[3];

void Mouse::Update()                                                //キー入力更新関連の関数の統括
{
	click[0] = GetMouseInput()&MOUSE_INPUT_LEFT;
	click[1] = GetMouseInput()&MOUSE_INPUT_MIDDLE;
	click[2] = GetMouseInput()&MOUSE_INPUT_RIGHT;

	for (int i = 0; i < 3; i++)
	{
		if (click[i] && !clickPre[i])
		{
			clickOnce[i] = true;
		}
		else
		{
			clickOnce[i] = false;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		clickPre[i] = click[i];
	}
}

bool Mouse::ClickOnce(int clickCode)								//スペースキーが押されているか
{
	static const unordered_map<int, int> toIndex=
	{
		{MOUSE_INPUT_LEFT,0},
		{MOUSE_INPUT_MIDDLE,1},
		{MOUSE_INPUT_RIGHT,2}
	};

	return clickOnce[toIndex.at(clickCode)];
}

bool Mouse::Click(int clickCode)
{
	static const unordered_map<int, int> toIndex =
	{
		{ MOUSE_INPUT_LEFT,0 },
		{ MOUSE_INPUT_MIDDLE,1 },
		{ MOUSE_INPUT_RIGHT,2 }
	};

	return click[toIndex.at(clickCode)];
}

Vector2<double> Mouse::GetMousePos()
{
	int x, y;
	GetMousePoint(&x, &y);
	return Vector2<double>((double)x, (double)y);
}