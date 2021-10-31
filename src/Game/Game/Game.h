#pragma once

#include"../header/Define.h"
#include"ChoiceButton.h"
#include"Character.h"

class Game
{
private:
	static vector<vector<pair<ScriptTag, vector<string>>>> scripts;

	static array<GHandle,1000> cgImage;
	static array<GHandle,1000> bgImage;
	static array<GHandle,1000> itemImage;
	static GHandle itemWindowImage;
	static GHandle messageWindowImage;
	static GHandle nameWindowImage;
	static const array<Color, 3> fadeColorList;
private:
	int transitionID;
	vector<ChoiceButton> choiceButtonList;
	array<Character,3> characterList;
	list<ScreenEffectPtr> screenEffectList;

	int sceneIndex;
	int scriptRowIndex;
	ScriptTag rowTag;
	bool rowEnded;

	bool readingScript;

	array<int, 3> timerList;
	bool clickRequestFlag;
	int messageCharIndex;
	string message;
	string name;
	int bgNum;
	int cgNum;
	int waitTime;
	bool showMessageWindow;
	string selectID;
	array<int, 3> fadeAlpha;
	int fadeType;
	int fadeTimer;
	int fadeTime;
	int itemIndex;

	thread* readScriptThread;
public:
	static void Load();
	static void Init();
private:
	void UpdateEvent();
	void ProceedEvent();
	void TransitScene(int n);
	void ObserveReadScript();
	void DeleteScreenEffect();

	void InitMessageClickWait(vector<string>& args);
	void InitMessageRenewPage(vector<string>& args);
	void InitMessageWindowSet(vector<string>& args);
	void InitMessageWindowDelete(vector<string>& args);
	void InitNameSet(vector<string>& args);
	void InitNameDelete(vector<string>& args);
	void InitBackGroundSet(vector<string>& args);
	void InitBackGroundDelete(vector<string>& args);
	void InitCGSet(vector<string>& args);
	void InitCGDelete(vector<string>& args);
	void InitScreenEffectSet(vector<string>& args);
	void InitScreenEffectDelete(vector<string>& args);
	void InitItemSet(vector<string>& args);
	void InitItemDelete(vector<string>& args);
	void InitCharaSet(vector<string>& args);
	void InitCharaDelete(vector<string>& args);
	void InitCharaAnimation(vector<string>& args);
	void InitSelect(vector<string>& args);
	void InitChoice(vector<string>& args);
	void InitIf(vector<string>& args);
	void InitElseIf(vector<string>& args);
	void InitElse(vector<string>& args);
	void InitEndIf(vector<string>& args);
	void InitJump(vector<string>& args);
	void InitJumpTag(vector<string>& args);
	void InitBGM(vector<string>& args);
	void InitBGMStop(vector<string>& args);
	void InitSE(vector<string>& args);
	void InitVoice(vector<string>& args);
	void InitStandFlag(vector<string>& args);
	void InitCancelFlag(vector<string>& args);
	void InitWaitTimer(vector<string>& args);
	void InitClick(vector<string>& args);
	void InitConsoleSet(vector<string>& args);
	void InitConsoleDelete(vector<string>& args);
	void InitPrintf(vector<string>& args);
	void InitFadeIn(vector<string>& args);
	void InitFadeOut(vector<string>& args);
	void InitTransitScene(vector<string>& args);

	void UpdateMessageClickWait();
	void UpdateMessageRenewPage();
	void UpdateMessageWindowSet();
	void UpdateMessageWindowDelete();
	void UpdateNameSet();
	void UpdateNameDelete();
	void UpdateBackGroundSet();
	void UpdateBackGroundDelete();
	void UpdateCGSet();
	void UpdateCGDelete();
	void UpdateScreenEffectSet();
	void UpdateScreenEffectDelete();
	void UpdateItemSet();
	void UpdateItemDelete();
	void UpdateCharaSet();
	void UpdateCharaDelete();
	void UpdateCharaAnimation();
	void UpdateSelect();
	void UpdateChoice();
	void UpdateIf();
	void UpdateElseIf();
	void UpdateElse();
	void UpdateEndIf();
	void UpdateJump();
	void UpdateJumpTag();
	void UpdateBGM();
	void UpdateBGMStop();
	void UpdateSE();
	void UpdateVoice();
	void UpdateStandFlag();
	void UpdateCancelFlag();
	void UpdateWaitTimer();
	void UpdateClick();
	void UpdateConsoleSet();
	void UpdateConsoleDelete();
	void UpdatePrintf();
	void UpdateFadeIn();
	void UpdateFadeOut();
	void UpdateTransitScene();
	
	void UpdateFade();

	void ProceedToEndIf(string tag);

	bool EvaluateExpression(string expression);
public:
	Game();
	~Game();
	void Update();
	void Draw()const;
	int GetTransitionID()const { return transitionID; }
};