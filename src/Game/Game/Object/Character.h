#pragma once

#include"Define.h"
#include"Class.h"

class Character
{
private:
	static vector<array<GHandle, 3>> charaImage;
private:
	bool isActive;
	Vector2<double> position;
	Vector2<double> animationOffsetPosition;
	Vector2<double> transitionOffsetPosition;
	Formation formation;
	int alpha;
	int ID;
	int nextID;
	int transitionTimer;
	int animationTimer;
	int appearType;
	int disappearType;
	int animationType;
	bool animationFlag;
	bool transitionFlag;
public:
	static void Load();
public:
	Character();
	Character(Formation formation);
	~Character();
	void Update();
	void Draw()const;
	void Transit(int nextID, int disappearType, int appearType);
	void Disappear(int disappearType);
	void StartAnimation(int animationType);
	bool DoTransition()const { return transitionFlag; }
	bool DoAnimation()const { return animationFlag; }
};