#pragma once

#include"Class.h"
#include"Define.h"

class Function
{
public:
	template<typename T> static bool CheckRange(Vector2<T>& v, T min_x, T max_x, T min_y, T max_y)
	{
		return min_x <= v.x&&v.x <= max_x&&min_y <= v.y&&v.y <= max_y;
	}

	static vector<string> split(const string &str, char delim) {
		istringstream iss(str); string tmp; vector<string> res;
		while (getline(iss, tmp, delim)) res.push_back(tmp);
		return res;
	}
	static string NumToStringFillZero(int num, int digits)
	{
		std::ostringstream sout;
		sout << std::setfill('0') << std::setw(digits) << num;
		return sout.str();
	}

	static void Alpha(int value)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, value);
	}

	static int CalcCenterOfString(const int x1, const int x2, const Font font, const char* str)
	{
		return (x1 + x2) / 2 - GetDrawFormatStringWidthToHandle(font, str) / 2;
	}

	static vector<pair<ScriptTag, vector<string>>> ReadScript(string path)
	{
		vector<pair<ScriptTag, vector<string>>> res;

		ifstream ifs(path);

		if (ifs.fail())return res;

		string rowStr;
		int line = 0;
		while (getline(ifs, rowStr))
		{
			if (rowStr == "")continue;
			auto elements = split(rowStr, ',');
			vector<string> argList;

			for (int i = 1; i < elements.size(); i++)
			{
				argList.push_back(elements[i]);
			}

			if (Define::tagToID.count(elements[0]) == 0)assert(0 && "ReadScript,–¢“o˜^‚Ìƒwƒbƒ_‚ªŒŸo‚³‚ê‚Ü‚µ‚½B");
			res.push_back(make_pair(Define::tagToID.at(elements[0]), argList));

			line++;
		}

		return res;
	}
};