#include"../header/ChoiceButton.h"
#include"../header/Mouse.h"
#include"../header/Function.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"

array<GHandle,2> ChoiceButton::windowImg;

void ChoiceButton::Load()
{
	windowImg[0] = LoadGraph("data/graph/choice_button2.png");
	windowImg[1] = LoadGraph("data/graph/choice_button2_2.png");
}

ChoiceButton::ChoiceButton(Vector2<double> position, string choiceString) :position(position), choiceString(choiceString)
{
	onButton = false;
	isClicked = false;
}

ChoiceButton::~ChoiceButton()
{

}

void ChoiceButton::Update()
{
	if (Function::CheckRange(Mouse::GetMousePos(), position.x - 350, position.x + 350, position.y - 30, position.y + 30))
	{
		onButton = true;
	}
	else
	{
		onButton = false;
	}

	if (Mouse::ClickOnce(MOUSE_INPUT_LEFT))
	{
		if (onButton)
		{
			isClicked = true;
		}
	}
}

void ChoiceButton::Draw()const
{
	DrawRotaGraph(position.x, position.y, 0.5, 0.0, windowImg[onButton ? 1 : 0], TRUE);

	Function::Alpha(onButton ? 255 : 180);
	DrawFormatStringToHandle(position.x - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[24], choiceString.c_str()) / 2, position.y - 21, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[24], choiceString.c_str());
	Function::Alpha(255);
}