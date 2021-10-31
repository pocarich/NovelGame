#pragma once

#include"Define.h"
#include"Singleton.h"

class Environment :public Singleton
{
private:
	static int windowWidth;
	static int windowHeight;
public:
	static void SetWindowSize(int w, int h) { windowWidth = w, windowHeight = h; }
	static int GetWindowWidth() { return windowWidth; }
	static int GetWindowHeight() { return  windowHeight; }
};