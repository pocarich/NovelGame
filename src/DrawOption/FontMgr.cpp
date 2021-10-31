#include"../header/FontMgr.h"

vector<Font> FontMgr::fontList; 

void FontMgr::Load()
{
	fontList.push_back(CreateFontToHandle(NULL, 8, 1, DX_FONTTYPE_ANTIALIASING_EDGE));			//0
	fontList.push_back(CreateFontToHandle(NULL, 12, 2, DX_FONTTYPE_ANTIALIASING_EDGE));			//1
	fontList.push_back(CreateFontToHandle(NULL, 16, 2, DX_FONTTYPE_ANTIALIASING_EDGE));			//2
	fontList.push_back(CreateFontToHandle(NULL, 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE));			//3
	fontList.push_back(CreateFontToHandle(NULL, 24, 3, DX_FONTTYPE_ANTIALIASING_EDGE));			//4
	fontList.push_back(CreateFontToHandle(NULL, 32, 4, DX_FONTTYPE_ANTIALIASING_EDGE));			//5
	fontList.push_back(CreateFontToHandle(NULL, 48, 5, DX_FONTTYPE_ANTIALIASING_EDGE));			//6
	fontList.push_back(CreateFontToHandle(NULL, 64, 5, DX_FONTTYPE_ANTIALIASING_EDGE));			//7

	fontList.push_back(CreateFontToHandle("HG明朝B", 8, 1, DX_FONTTYPE_ANTIALIASING_EDGE));		//8
	fontList.push_back(CreateFontToHandle("HG明朝B", 12, 2, DX_FONTTYPE_ANTIALIASING_EDGE));	//9
	fontList.push_back(CreateFontToHandle("HG明朝B", 16, 2, DX_FONTTYPE_ANTIALIASING_EDGE));	//10
	fontList.push_back(CreateFontToHandle("HG明朝B", 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE));	//11
	fontList.push_back(CreateFontToHandle("HG明朝B", 24, 3, DX_FONTTYPE_ANTIALIASING_EDGE));	//12
	fontList.push_back(CreateFontToHandle("HG明朝B", 32, 4, DX_FONTTYPE_ANTIALIASING_EDGE));	//13
	fontList.push_back(CreateFontToHandle("HG明朝B", 48, 5, DX_FONTTYPE_ANTIALIASING_EDGE));	//14
	fontList.push_back(CreateFontToHandle("HG明朝B", 64, 5, DX_FONTTYPE_ANTIALIASING_EDGE));	//15

	fontList.push_back(CreateFontToHandle("03スマートフォントUI", 8, 1, DX_FONTTYPE_ANTIALIASING_EDGE));			//16
	fontList.push_back(CreateFontToHandle("03スマートフォントUI", 12, 2, DX_FONTTYPE_ANTIALIASING_EDGE));			//17
	fontList.push_back(CreateFontToHandle("03スマートフォントUI", 16, 2, DX_FONTTYPE_ANTIALIASING_EDGE));			//18
	fontList.push_back(CreateFontToHandle("03スマートフォントUI", 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE));			//19
	fontList.push_back(CreateFontToHandle("03スマートフォントUI", 24, 3, DX_FONTTYPE_ANTIALIASING_EDGE));			//20
	fontList.push_back(CreateFontToHandle("03スマートフォントUI", 32, 4, DX_FONTTYPE_ANTIALIASING_EDGE));			//21
	fontList.push_back(CreateFontToHandle("03スマートフォントUI", 48, 5, DX_FONTTYPE_ANTIALIASING_EDGE));			//22
	fontList.push_back(CreateFontToHandle("03スマートフォントUI", 64, 5, DX_FONTTYPE_ANTIALIASING_EDGE));			//23

	fontList.push_back(CreateFontToHandle("HG明朝B", 40, 5, DX_FONTTYPE_ANTIALIASING_EDGE));	//24
}