#include"../header/Game.h"
#include"../header/Environment.h"
#include"../header/Mouse.h"
#include"../header/Function.h"
#include"../header/FontMgr.h"
#include"../header/ColorMgr.h"
#include"../header/PlayerData.h"
#include"../header/BGMMgr.h"
#include"../header/SEMgr.h"
#include"../header/VoiceMgr.h"
#include"../header/ScreenEffect.h"

vector<vector<pair<ScriptTag, vector<string>>>> Game::scripts;

array<GHandle, 1000> Game::cgImage;
array<GHandle, 1000> Game::bgImage;
array<GHandle, 1000> Game::itemImage;
GHandle Game::itemWindowImage;
GHandle Game::messageWindowImage;
GHandle Game::nameWindowImage;

const array<Color, 3> Game::fadeColorList = { (int)ColorMgr::BaseColor::BLACK,(int)ColorMgr::BaseColor::WHITE,(int)ColorMgr::BaseColor::RED };

void Game::Init()
{
	scripts.resize(1000);
}

void Game::Load()
{
	for (int i = 0; i != 75; i++)
	{
		//cgImage[i] = LoadGraph(("data/graph/cg/cg"+Function::NumToStringFillZero(i,3)+".jpg").c_str());
		bgImage[i] = LoadGraph(("data/graph/background/background" + Function::NumToStringFillZero(i, 3) + ".jpg").c_str());
		//itemImage[i] = LoadGraph(("data/graph/item/item" + Function::NumToStringFillZero(i, 3) + ".png").c_str());
	}
	itemWindowImage = LoadGraph("data/graph/item/item_window.png");
	messageWindowImage = LoadGraph("data/graph/message_window2.png");
	nameWindowImage = LoadGraph("data/graph/name_window2.png");
}

Game::Game()
{
	transitionID = -1;
	clickRequestFlag = false;
	messageCharIndex = 0;
	sceneIndex = 0;
	scriptRowIndex = 0;
	readingScript = false;
	rowEnded = true;
	rowTag = ScriptTag::SIZE;
	readScriptThread = nullptr;
	bgNum = -1;
	cgNum = -1;
	showMessageWindow = false;
	fadeType = -1;
	fadeTimer = 0;
	fadeTime = 1;
	itemIndex = -1;
	name = "";

	for (int i = 0; i != fadeAlpha.size(); i++)
	{
		fadeAlpha[i] = 0;
	}

	for (int i = 0; i != timerList.size(); i++)
	{
		timerList[i] = 0;
	}

	characterList[0] = Character(Formation::CENTER);
	characterList[1] = Character(Formation::LEFT);
	characterList[2] = Character(Formation::RIGHT);

	TransitScene(sceneIndex);
}

Game::~Game()
{
	BGMMgr::StopAllBGM();
	SEMgr::StopAllSE();
	VoiceMgr::StopAllVoice();
}

void Game::Update()
{
	if (readScriptThread == nullptr)
	{
		if (!rowEnded)
		{
			UpdateEvent();
			for (auto& obj : choiceButtonList)
			{
				obj.Update();
			}
		}
		if (rowEnded)
		{
			ProceedEvent();
		}
		for (auto& obj : characterList)
		{
			obj.Update();
		}
		for (auto& obj : screenEffectList)
		{
			obj->Update();
		}
		UpdateFade();
		DeleteScreenEffect();
	}
	else
	{
		ObserveReadScript();
	}
}

void Game::TransitScene(int n)
{
	transitionID = -1;
	clickRequestFlag = false;
	messageCharIndex = 0;
	readingScript = false;
	rowEnded = true;
	rowTag = ScriptTag::SIZE;
	readScriptThread = nullptr;
	bgNum = -1;
	cgNum = -1;
	showMessageWindow = false;
	fadeType = -1;
	fadeTimer = 0;
	fadeTime = 1;
	itemIndex = -1;
	name = "";

	for (int i = 0; i != timerList.size(); i++)
	{
		timerList[i] = 0;
	}

	characterList[0] = Character(Formation::CENTER);
	characterList[1] = Character(Formation::LEFT);
	characterList[2] = Character(Formation::RIGHT);

	sceneIndex = n;
	scriptRowIndex = 0;

	if (scripts[n].size() != 0)return;

	readingScript = true;
	readScriptThread=new thread([=]
	{
		scripts[n] = Function::ReadScript("data/script/script" + Function::NumToStringFillZero(n, 3) + ".csv");
		if (scripts[n].size() == 0)assert(0 && ("Game,script"+Function::NumToStringFillZero(n, 3) + ".csv‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½B").c_str());
		readingScript = false;
	});
}

void Game::ObserveReadScript()
{
	if (!readingScript)
	{
		readScriptThread->join();
		delete readScriptThread;
		readScriptThread = nullptr;
	}
}

void Game::ProceedEvent()
{
	while (rowEnded&&scriptRowIndex < scripts[sceneIndex].size())
	{
		rowEnded = false;

		rowTag = scripts[sceneIndex][scriptRowIndex].first;
		vector<function<void(vector<string>&)>> initList = {
			[&](vector<string>& args) {InitMessageClickWait(args); },
			[&](vector<string>& args) {InitMessageRenewPage(args); },
			[&](vector<string>& args) {InitMessageWindowSet(args); },
			[&](vector<string>& args) {InitMessageWindowDelete(args); },
			[&](vector<string>& args) {InitNameSet(args); },
			[&](vector<string>& args) {InitNameDelete(args); },
			[&](vector<string>& args) {InitBackGroundSet(args); },
			[&](vector<string>& args) {InitBackGroundDelete(args); },
			[&](vector<string>& args) {InitCGSet(args); },
			[&](vector<string>& args) {InitCGDelete(args); },
			[&](vector<string>& args) {InitScreenEffectSet(args); },
			[&](vector<string>& args) {InitScreenEffectDelete(args); },
			[&](vector<string>& args) {InitItemSet(args); },
			[&](vector<string>& args) {InitItemDelete(args); },
			[&](vector<string>& args) {InitCharaSet(args); },
			[&](vector<string>& args) {InitCharaDelete(args); },
			[&](vector<string>& args) {InitCharaAnimation(args); },
			[&](vector<string>& args) {InitSelect(args); },
			[&](vector<string>& args) {InitChoice(args); },
			[&](vector<string>& args) {InitIf(args); },
			[&](vector<string>& args) {InitElseIf(args); },
			[&](vector<string>& args) {InitElse(args); },
			[&](vector<string>& args) {InitEndIf(args); },
			[&](vector<string>& args) {InitJump(args); },
			[&](vector<string>& args) {InitJumpTag(args); },
			[&](vector<string>& args) {InitBGM(args); },
			[&](vector<string>& args) {InitBGMStop(args); },
			[&](vector<string>& args) {InitSE(args); },
			[&](vector<string>& args) {InitVoice(args); },
			[&](vector<string>& args) {InitStandFlag(args); },
			[&](vector<string>& args) {InitCancelFlag(args); },
			[&](vector<string>& args) {InitWaitTimer(args); },
			[&](vector<string>& args) {InitClick(args); },
			[&](vector<string>& args) {InitConsoleSet(args); },
			[&](vector<string>& args) {InitConsoleDelete(args); },
			[&](vector<string>& args) {InitPrintf(args); },
			[&](vector<string>& args) {InitFadeIn(args); },
			[&](vector<string>& args) {InitFadeOut(args); },
			[&](vector<string>& args) {InitTransitScene(args); }
		};

		ScriptTag tempTag = rowTag;

		initList[(int)rowTag](scripts[sceneIndex][scriptRowIndex].second);

		if (tempTag != ScriptTag::TRANSIT_SCENE)
		{
			scriptRowIndex++;
		}
	}
}

void Game::UpdateEvent()
{
	vector<function<void()>> updateList = {
		[&]() {UpdateMessageClickWait(); },
		[&]() {UpdateMessageRenewPage(); },
		[&]() {UpdateMessageWindowSet(); },
		[&]() {UpdateMessageWindowDelete(); },
		[&]() {UpdateNameSet(); },
		[&]() {UpdateNameDelete(); },
		[&]() {UpdateBackGroundSet(); },
		[&]() {UpdateBackGroundDelete(); },
		[&]() {UpdateCGSet(); },
		[&]() {UpdateCGDelete(); },
		[&]() {UpdateScreenEffectSet(); },
		[&]() {UpdateScreenEffectDelete(); },
		[&]() {UpdateItemSet(); },
		[&]() {UpdateItemDelete(); },
		[&]() {UpdateCharaSet(); },
		[&]() {UpdateCharaDelete(); },
		[&]() {UpdateCharaAnimation(); },
		[&]() {UpdateSelect(); },
		[&]() {UpdateChoice(); },
		[&]() {UpdateIf(); },
		[&]() {UpdateElseIf(); },
		[&]() {UpdateElse(); },
		[&]() {UpdateEndIf(); },
		[&]() {UpdateJump(); },
		[&]() {UpdateJumpTag(); },
		[&]() {UpdateBGM(); },
		[&]() {UpdateBGMStop(); },
		[&]() {UpdateSE(); },
		[&]() {UpdateVoice(); },
		[&]() {UpdateStandFlag(); },
		[&]() {UpdateCancelFlag(); },
		[&]() {UpdateWaitTimer(); },
		[&]() {UpdateClick(); },
		[&]() {UpdateConsoleSet(); },
		[&]() {UpdateConsoleDelete(); },
		[&]() {UpdatePrintf(); },
		[&]() {UpdateFadeIn(); },
		[&]() {UpdateFadeOut(); },
		[&]() {UpdateTransitScene(); }
	};

	updateList[(int)rowTag]();
}

void Game::DeleteScreenEffect()
{
	screenEffectList.erase(remove_if(screenEffectList.begin(), screenEffectList.end(), [&](ScreenEffectPtr& obj) {return obj->GetEndFlag(); }), screenEffectList.end());
}

void Game::UpdateFade()
{
	switch (fadeType)
	{
	case 0:
		fadeAlpha[0] = (int)(255.0 / fadeTime*fadeTimer);
		if (fadeTimer == fadeTime)
		{
			fadeAlpha[0] = 255;
			fadeType = -1;
		}
		break;
	case 1:
		fadeAlpha[1] = (int)(255.0 / fadeTime*fadeTimer);
		if (fadeTimer == fadeTime)
		{
			fadeAlpha[1] = 255;
			fadeType = -1;
		}
		break;
	case 2:
		fadeAlpha[2] = (int)(255.0 / fadeTime*fadeTimer);
		if (fadeTimer == fadeTime)
		{
			fadeAlpha[2] = 255;
			fadeType = -1;
		}
		break;
	case 3:
		fadeAlpha[0] = (int)(255.0*(1.0 - (double)fadeTimer / fadeTime));
		if (fadeTimer == fadeTime)
		{
			fadeAlpha[0] = 0;
			fadeType = -1;
		}
		break;
	case 4:
		fadeAlpha[1] = (int)(255.0*(1.0 - (double)fadeTimer / fadeTime));
		if (fadeTimer == fadeTime)
		{
			fadeAlpha[1] = 0;
			fadeType = -1;
		}
		break;
	case 5:
		fadeAlpha[2] = (int)(255.0*(1.0 - (double)fadeTimer / fadeTime));
		if (fadeTimer == fadeTime)
		{
			fadeAlpha[2] = 0;
			fadeType = -1;
		}
		break;
	}

	fadeTimer++;
}

void Game::Draw()const
{
	if (readScriptThread == nullptr)
	{
		if (bgNum != -1)
		{
			DrawExtendGraph(0, 0, Environment::GetWindowWidth(), Environment::GetWindowHeight(), bgImage[bgNum], TRUE);
		}

		for (auto& obj : characterList)
		{
			obj.Draw();
		}

		for (auto& obj : screenEffectList)
		{
			obj->Draw();
		}

		if (cgNum != -1)
		{
			DrawExtendGraph(0, 0, Environment::GetWindowWidth(), Environment::GetWindowHeight(), bgImage[cgNum], TRUE);
		}

		if (itemIndex != -1)
		{
			DrawRotaGraph(Environment::GetWindowWidth() / 2, 250, 0.5, 0.0, itemWindowImage, TRUE);
			DrawRotaGraph(Environment::GetWindowWidth() / 2, 250, 0.5, 0.0, itemImage[itemIndex], TRUE);
		}

		if (name.size() != 0)
		{
			DrawRotaGraph(200, 475, 0.5, 0.0, nameWindowImage, TRUE, TRUE);
			DrawFormatStringToHandle(200 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[24], name.c_str())/2, 454, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[24], name.c_str());
		}

		if (showMessageWindow)
		{
			DrawRotaGraph(Define::BASE_WINDOW_WIDTH / 2, 600, 1.2, 0.0, messageWindowImage, TRUE);
		}

		if (message.size() != 0)
		{
			int rowNum = (messageCharIndex - 1) / Define::MESSAGE_COLUMN_LENGTH;
			int rowOffset = max(0, rowNum - 2);
			int rowIndex = rowOffset;
			while (Define::MESSAGE_COLUMN_LENGTH*rowIndex < messageCharIndex)
			{
				DrawFormatStringToHandle(44, 530 + 44 * (rowIndex - rowOffset), ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[24], message.substr(Define::MESSAGE_COLUMN_LENGTH*rowIndex, min(Define::MESSAGE_COLUMN_LENGTH, messageCharIndex - Define::MESSAGE_COLUMN_LENGTH*rowIndex)).c_str());
				rowIndex++;
			}
		}

		for (auto& obj : choiceButtonList)
		{
			obj.Draw();
		}

		for (int i = 0; i != fadeAlpha.size(); i++)
		{
			Function::Alpha(fadeAlpha[i]);
			DrawFillBox(0, 0, Environment::GetWindowWidth(), Environment::GetWindowHeight(), ColorMgr::GetColorCode()[fadeColorList[i]]);
			Function::Alpha(255);
		}
	}
	else
	{
		DrawFormatStringToHandle(Environment::GetWindowWidth() / 2 - GetDrawFormatStringWidthToHandle(FontMgr::GetFont()[24], "NOW LOADING...")/2, Environment::GetWindowHeight() / 2 - 25, ColorMgr::GetColorCode()[(int)ColorMgr::BaseColor::WHITE], FontMgr::GetFont()[24], "NOW LOADING...");
	}
}

void Game::InitMessageClickWait(vector<string>& args)
{
	message += args[0];
}

void Game::InitMessageRenewPage(vector<string>& args)
{

}

void Game::InitMessageWindowSet(vector<string>& args)
{
	showMessageWindow = true;
	rowEnded = true;
}

void Game::InitMessageWindowDelete(vector<string>& args)
{
	showMessageWindow = false;
	rowEnded = true;
}

void Game::InitNameSet(vector<string>& args)
{
	name = args[0];
	rowEnded = true;
}

void Game::InitNameDelete(vector<string>& args)
{
	name = "";
	rowEnded = true;
}

void Game::InitBackGroundSet(vector<string>& args)
{
	bgNum = atoi(args[0].c_str());
	rowEnded = true;
}

void Game::InitBackGroundDelete(vector<string>& args)
{
	bgNum = -1;
	rowEnded = true;
}

void Game::InitCGSet(vector<string>& args)
{
	cgNum = atoi(args[0].c_str());
	rowEnded = true;
}

void Game::InitCGDelete(vector<string>& args)
{
	cgNum = -1;
	rowEnded = true;
}

void Game::InitScreenEffectSet(vector<string>& args)
{
	screenEffectList.push_back(make_shared<ScreenEffect>(atoi(args[0].c_str()), atoi(args[1].c_str())));
	rowEnded = true;
}

void Game::InitScreenEffectDelete(vector<string>& args)
{
	screenEffectList.erase(remove_if(screenEffectList.begin(), screenEffectList.end(), [&](ScreenEffectPtr& obj) {return obj->GetID() == atoi(args[0].c_str()); }), screenEffectList.end());

	rowEnded = true;
}

void Game::InitItemSet(vector<string>& args)
{
	itemIndex= atoi(args[0].c_str());
	rowEnded = true;
}

void Game::InitItemDelete(vector<string>& args)
{
	itemIndex = -1;
	rowEnded = true;
}

void Game::InitCharaSet(vector<string>& args)
{
	while (scriptRowIndex != scripts[sceneIndex].size() && (scripts[sceneIndex][scriptRowIndex].first == ScriptTag::CHARA_SET || scripts[sceneIndex][scriptRowIndex].first == ScriptTag::CHARA_DELETE))
	{
		switch (scripts[sceneIndex][scriptRowIndex].first)
		{
		case ScriptTag::CHARA_SET:
			characterList[atoi(scripts[sceneIndex][scriptRowIndex].second[0].c_str())].Transit(atoi(scripts[sceneIndex][scriptRowIndex].second[1].c_str()), atoi(scripts[sceneIndex][scriptRowIndex].second[2].c_str()), atoi(scripts[sceneIndex][scriptRowIndex].second[3].c_str()));
			break;
		case ScriptTag::CHARA_DELETE:
			characterList[atoi(scripts[sceneIndex][scriptRowIndex].second[0].c_str())].Disappear(atoi(scripts[sceneIndex][scriptRowIndex].second[1].c_str()));
			break;
		}
		scriptRowIndex++;
	}
	scriptRowIndex--;
}

void Game::InitCharaDelete(vector<string>& args)
{
	while (scriptRowIndex != scripts[sceneIndex].size() && (scripts[sceneIndex][scriptRowIndex].first == ScriptTag::CHARA_SET || scripts[sceneIndex][scriptRowIndex].first == ScriptTag::CHARA_DELETE))
	{
		switch (scripts[sceneIndex][scriptRowIndex].first)
		{
		case ScriptTag::CHARA_SET:
			characterList[atoi(scripts[sceneIndex][scriptRowIndex].second[0].c_str())].Transit(atoi(scripts[sceneIndex][scriptRowIndex].second[1].c_str()), atoi(scripts[sceneIndex][scriptRowIndex].second[2].c_str()), atoi(scripts[sceneIndex][scriptRowIndex].second[3].c_str()));
			break;
		case ScriptTag::CHARA_DELETE:
			characterList[atoi(scripts[sceneIndex][scriptRowIndex].second[0].c_str())].Disappear(atoi(scripts[sceneIndex][scriptRowIndex].second[1].c_str()));
			break;
		}
		scriptRowIndex++;
	}
	scriptRowIndex--;
}

void Game::InitCharaAnimation(vector<string>& args)
{
	characterList[atoi(args[0].c_str())].StartAnimation(atoi(args[1].c_str()));
	rowEnded = true;
}

void Game::InitSelect(vector<string>& args)
{
	selectID = args[0];
	double interval = 400.0 / (args.size());
	for (int i = 1; i < args.size(); i++)
	{
		choiceButtonList.push_back(ChoiceButton(Vector2<double>(Environment::GetWindowWidth() / 2, 250 - 200.0 + interval*i), args[i]));
	}
}

void Game::InitChoice(vector<string>& args)
{

}

void Game::InitIf(vector<string>& args)
{
	string tag = args[0];
	if (EvaluateExpression(args[1]))
	{
		rowEnded = true;
		return;
	}

	while (true)
	{
		while (scriptRowIndex != scripts[sceneIndex].size() && (scripts[sceneIndex][scriptRowIndex].first != ScriptTag::ENDIF || scripts[sceneIndex][scriptRowIndex].second[0] != tag)&& (scripts[sceneIndex][scriptRowIndex].first != ScriptTag::ELSEIF || scripts[sceneIndex][scriptRowIndex].second[0] != tag)&& (scripts[sceneIndex][scriptRowIndex].first != ScriptTag::ELSE || scripts[sceneIndex][scriptRowIndex].second[0] != tag))
		{
			scriptRowIndex++;
		}

		if (scriptRowIndex == scripts[sceneIndex].size())return;

		bool broken = false;

		switch (scripts[sceneIndex][scriptRowIndex].first)
		{
		case ScriptTag::ELSEIF:
			if (EvaluateExpression(scripts[sceneIndex][scriptRowIndex].second[1]))
			{
				broken = true;
			}
			break;
		case ScriptTag::ELSE:
			broken = true;
			break;
		case ScriptTag::ENDIF:
			broken = true;
			break;
		}

		if (broken)
		{
			rowEnded = true;
			break;
		}
		else
		{
			scriptRowIndex++;
		}
	}
}

void Game::ProceedToEndIf(string tag)
{

}

void Game::InitElseIf(vector<string>& args)
{
	string tag = args[0];
	while (scriptRowIndex != scripts[sceneIndex].size() && (scripts[sceneIndex][scriptRowIndex].first != ScriptTag::ENDIF || scripts[sceneIndex][scriptRowIndex].second[0] != tag))
	{
		scriptRowIndex++;
	}

	rowEnded = true;
}

void Game::InitElse(vector<string>& args)
{

	string tag = args[0];
	while (scriptRowIndex != scripts[sceneIndex].size() && (scripts[sceneIndex][scriptRowIndex].first != ScriptTag::ENDIF || scripts[sceneIndex][scriptRowIndex].second[0] != tag))
	{
		scriptRowIndex++;
	}

	rowEnded = true;
}

void Game::InitEndIf(vector<string>& args)
{
	rowEnded = true;
}

void Game::InitJump(vector<string>& args)
{
	string tag = args[0];
	while (scriptRowIndex != scripts[sceneIndex].size() && (scripts[sceneIndex][scriptRowIndex].first != ScriptTag::JUMP_TAG || scripts[sceneIndex][scriptRowIndex].second[0] != tag))
	{
		scriptRowIndex++;
	}

	if (scriptRowIndex == scripts[sceneIndex].size())return;

	scriptRowIndex++;
	rowEnded = true;
}

void Game::InitJumpTag(vector<string>& args)
{
	rowEnded = true;
}

void Game::InitBGM(vector<string>& args)
{
	BGMMgr::UpdateStartFlag(atoi(args[0].c_str()));
	rowEnded = true;
}

void Game::InitBGMStop(vector<string>& args)
{
	int i = atoi(args[0].c_str());
	if (i == -1)
	{
		BGMMgr::StopAllBGM();
	}
	else
	{
		BGMMgr::UpdateStopFlag(i);
	}
	rowEnded = true;
}

void Game::InitSE(vector<string>& args)
{
	SEMgr::UpdateFlag(atoi(args[0].c_str()));
	rowEnded = true;
}

void Game::InitVoice(vector<string>& args)
{
	VoiceMgr::UpdateFlag(atoi(args[0].c_str()));
	rowEnded = true;
}

void Game::InitStandFlag(vector<string>& args)
{
	PlayerData::StandFlag(atoi(args[0].c_str()));
	rowEnded = true;
}

void Game::InitCancelFlag(vector<string>& args)
{
	PlayerData::CancelFlag(atoi(args[0].c_str()));
	rowEnded = true;
}

void Game::InitWaitTimer(vector<string>& args)
{
	waitTime = atoi(args[0].c_str());
}

void Game::InitClick(vector<string>& args)
{
	
}

void Game::InitConsoleSet(vector<string>& args)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	rowEnded = true;
}

void Game::InitConsoleDelete(vector<string>& args)
{
	FreeConsole();
	rowEnded = true;
}

void Game::InitPrintf(vector<string>& args)
{
	MessageBox(NULL, TEXT(args[0].c_str()), TEXT(args[1].c_str()), MB_OK);
	rowEnded = true;
}

void Game::InitFadeIn(vector<string>& args)
{
	fadeType = atoi(args[0].c_str());
	fadeTimer = 0;
	fadeTime = atoi(args[1].c_str());
	rowEnded = true;
}

void Game::InitFadeOut(vector<string>& args)
{
	fadeType = 3 + atoi(args[0].c_str());
	fadeTimer = 0;
	fadeTime = atoi(args[1].c_str());
	rowEnded = true;
}

void Game::InitTransitScene(vector<string>& args)
{
	TransitScene(atoi(args[0].c_str()));
}

void Game::UpdateMessageClickWait()
{
	timerList[0]++;
	if (timerList[0] % Define::CHAR_PROCEED_INTERVAL == 0)
	{
		messageCharIndex += 2;
		messageCharIndex = min(messageCharIndex, message.size());
	}
	if (messageCharIndex == message.size())
	{
		clickRequestFlag = true;
	}
	if (Mouse::ClickOnce(MOUSE_INPUT_LEFT))
	{
		if (clickRequestFlag)
		{
			message = "";
			messageCharIndex = 0;
			clickRequestFlag = false;
			timerList[0] = 0;
			VoiceMgr::StopAllVoice();
			rowEnded = true;
		}
		else
		{
			messageCharIndex = message.size();
			clickRequestFlag = true;
		}
	}
}

void Game::UpdateMessageRenewPage()
{

}

void Game::UpdateMessageWindowSet()
{

}

void Game::UpdateMessageWindowDelete()
{

}

void Game::UpdateNameSet()
{

}

void Game::UpdateNameDelete()
{

}

void Game::UpdateBackGroundSet()
{

}

void Game::UpdateBackGroundDelete()
{

}

void Game::UpdateCGSet()
{

}

void Game::UpdateCGDelete()
{

}

void Game::UpdateScreenEffectSet()
{

}

void Game::UpdateScreenEffectDelete()
{

}

void Game::UpdateItemSet()
{

}

void Game::UpdateItemDelete()
{

}

void Game::UpdateCharaSet()
{
	for (auto& obj : characterList)
	{
		if (obj.DoTransition())
		{
			return;
		}
	}
	rowEnded = true;
}

void Game::UpdateCharaDelete()
{
	for (auto& obj : characterList)
	{
		if (obj.DoTransition())
		{
			return;
		}
	}
	rowEnded = true;
}

void Game::UpdateCharaAnimation()
{

}

void Game::UpdateSelect()
{
	int i;
	for (i = 0; i != choiceButtonList.size(); i++)
	{
		if (choiceButtonList[i].IsClicked())
		{
			break;
		}
	}

	if (i == choiceButtonList.size())return;

	while (scriptRowIndex!= scripts[sceneIndex].size()&&(scripts[sceneIndex][scriptRowIndex].first != ScriptTag::CHOISE || scripts[sceneIndex][scriptRowIndex].second[0] != selectID || scripts[sceneIndex][scriptRowIndex].second[1] != to_string(i)))
	{
		scriptRowIndex++;
	}

	if (scriptRowIndex == scripts[sceneIndex].size())return;

	choiceButtonList.clear();
	scriptRowIndex++;
	rowEnded = true;
}

void Game::UpdateChoice()
{

}

void Game::UpdateIf()
{

}

void Game::UpdateElseIf ()
{

}

void Game::UpdateElse()
{

}

void Game::UpdateEndIf()
{

}

void Game::UpdateJump()
{

}

void Game::UpdateJumpTag()
{

}

void Game::UpdateBGM()
{

}

void Game::UpdateBGMStop()
{

}

void Game::UpdateSE()
{

}

void Game::UpdateVoice()
{

}

void Game::UpdateStandFlag()
{

}

void Game::UpdateCancelFlag()
{

}

void Game::UpdateWaitTimer()
{
	timerList[0]++;
	if (timerList[0] == waitTime)
	{
		timerList[0] = 0;
		rowEnded = true;
	}
}

void Game::UpdateClick()
{
	if (Mouse::ClickOnce(MOUSE_INPUT_LEFT))
	{
		rowEnded = true;
	}
}


void Game::UpdateConsoleSet()
{

}


void Game::UpdateConsoleDelete()
{

}


void Game::UpdatePrintf()
{

}

void Game::UpdateFadeIn()
{

}

void Game::UpdateFadeOut()
{

}

void Game::UpdateTransitScene()
{

}

bool Game::EvaluateExpression(string expression)
{
	auto elements = Function::split(expression, '|');
	for (auto element : elements)
	{
		auto elements2 = Function::split(element, '&');

		bool tempRes2 = true;
		for (auto element2 : elements2)
		{
			bool reverse = element2.front() == '!';
			if (reverse)
			{
				element2 = element2.substr(1);
			}

			tempRes2 = PlayerData::GetFlag(atoi(element2.c_str()));

			if (reverse)
			{
				tempRes2 = !tempRes2;
			}

			if (!tempRes2)break;
		}
		if (tempRes2)
		{
			return true;
		}
	}
	return false;
}