#pragma once

#include"Define.h"
#include"Class.h"

class ChoiceButton
{
private:
	static array<GHandle,2> windowImg;
private:
	Vector2<double> position;
	string choiceString;
	bool onButton;
	bool isClicked;
public:
	static void Load();
public:
	ChoiceButton(Vector2<double> position, string choiceString);
	~ChoiceButton();
	void Update();
	void Draw()const;
	bool IsClicked()const { return isClicked; }
};