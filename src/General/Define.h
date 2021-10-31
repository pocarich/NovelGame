#pragma once

#include<Dxlib.h>
#include<fstream>
#include<sstream>
#include<memory>
#include<string>
#include<array>
#include<vector>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<typeinfo>
#include<assert.h>
#include<algorithm>
#include<numeric>
#include<functional>
#include<assert.h>
#include<cstdio>
#include<iostream>
#include<Windows.h>
#include<queue>
#include<set>
#include<iomanip>
#include<random>
#include<future>

#define _USE_MATH_DEFINES
#include<math.h>

#define STR(var) #var

#include"Enum.h"

using namespace std;

class Define
{
public:
	static const int FPS = 60;
	static const int BASE_WINDOW_WIDTH =1278;
	static const int BASE_WINDOW_HEIGHT = 718;
	static const int MASU_SIZE = 32;

	static const int CHAR_PROCEED_INTERVAL = 2;
	static const int MESSAGE_COLUMN_LENGTH = 56;

	static const unordered_map<string, ScriptTag> tagToID;

private:
	Define() {};
	Define(const Define&) {};
	Define& operator =(const Define&) {};
};

typedef int GHandle;
typedef int MHandle;
typedef int FHandle;
typedef int Color;
typedef int Font;

class ScreenEffect;
typedef shared_ptr<ScreenEffect> ScreenEffectPtr;