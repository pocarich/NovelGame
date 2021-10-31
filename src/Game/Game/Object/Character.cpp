#include"../header/Character.h"
#include"../header/Function.h"

vector<array<GHandle, 3>> Character::charaImage;

void Character::Load()
{
	for (int i = 0; i < 30; i++)
	{
		array<GHandle, 3> tempArray = { 0,0,0 };
		for (int j = 0; j < 3; j++)
		{
			string filePath = "data/graph/chara/chara" + to_string(i) + "_" + to_string(j) + ".png";
			tempArray[j] = LoadGraph(filePath.c_str());
		}
		charaImage.push_back(tempArray);
	}
}

Character::Character() :Character(Formation::CENTER)
{

}

Character::Character(Formation formation):formation(formation)
{
	isActive = false;
	transitionOffsetPosition = Vector2<double>(0.0, 0.0);
	animationOffsetPosition = Vector2<double>(0.0, 0.0);
	alpha = 0;
	ID = -1;
	nextID = -1;
	transitionTimer = 0;
	animationTimer = 0;
	appearType = -1;
	disappearType = -1;
	animationType = -1;
	animationFlag = false;
	transitionFlag = false;

	switch (formation)
	{
	case Formation::CENTER:
		position = Vector2<double>(Define::BASE_WINDOW_WIDTH / 2.0, Define::BASE_WINDOW_HEIGHT / 2.0 + 100);
		break;
	case Formation::LEFT:
		position = Vector2<double>(Define::BASE_WINDOW_WIDTH / 4.0, Define::BASE_WINDOW_HEIGHT / 2.0 + 100);
		break;
	case Formation::RIGHT:
		position = Vector2<double>(Define::BASE_WINDOW_WIDTH / 4.0*3.0, Define::BASE_WINDOW_HEIGHT / 2.0 + 100);
		break;
	}
}

Character::~Character()
{

}

void Character::Update()
{
	if (!isActive)return;

	if (transitionFlag)
	{
		if (disappearType != -1)
		{
			switch (disappearType)
			{
			case 0:
				transitionOffsetPosition = Vector2<double>(0.0, 0.0);
				alpha = 0;
				disappearType = -1;
				if (appearType == -1)
				{
					isActive = false;
					transitionFlag = false;
				}
				else
				{
					ID = nextID;
				}
				break;
			case 1:
				transitionTimer++;
				transitionOffsetPosition = Vector2<double>(0.0, 0.0);
				alpha = max(0, (int)(255.0*(1.0 - transitionTimer / 10.0)));
				if (transitionTimer == 10)
				{
					transitionTimer = 0;
					disappearType = -1;
					if (appearType == -1)
					{
						isActive = false;
						transitionFlag = false;
					}
					else
					{
						ID = nextID;
					}
				}
				break;
			case 2:
				transitionTimer++;
				switch (formation)
				{
				case Formation::LEFT:
					transitionOffsetPosition = Vector2<double>(-1000.0*transitionTimer / 20.0, 0.0);
					break;
				case Formation::RIGHT:
					transitionOffsetPosition = Vector2<double>(1000.0*transitionTimer / 20.0, 0.0);
					break;
				}
				if (transitionTimer == 20)
				{
					transitionTimer = 0;
					disappearType = -1;
					if (appearType == -1)
					{
						isActive = false;
						transitionFlag = false;
					}
					else
					{
						ID = nextID;
					}
				}
				break;
			}
		}
		else
		{
			if (appearType != -1)
			{
				switch (appearType)
				{
				case 0:
					transitionOffsetPosition = Vector2<double>(0.0, 0.0);
					alpha = 255;
					appearType = -1;
					break;
				case 1:
					transitionTimer++;
					transitionOffsetPosition = Vector2<double>(0.0, 0.0);
					alpha = min(255, (int)(255.0*transitionTimer / 10.0));
					if (transitionTimer == 10)
					{
						transitionTimer = 0;
						appearType = -1;
					}
					break;
				case 2:
					transitionTimer++;
					alpha = 255;
					switch (formation)
					{
					case Formation::LEFT:
						transitionOffsetPosition = Vector2<double>(-1000.0*(1.0-transitionTimer / 20.0), 0.0);
						break;
					case Formation::RIGHT:
						transitionOffsetPosition = Vector2<double>(1000.0*(1.0-transitionTimer / 20.0), 0.0);
						break;
					}
					if (transitionTimer == 20)
					{
						transitionTimer = 0;
						appearType = -1;
					}
					break;
				}
			}
			else
			{
				transitionFlag = false;
			}
		}
	}

	if (animationFlag)
	{
		if (animationType != -1)
		{
			switch (animationType)
			{
			case 0:
				animationTimer++;
				animationOffsetPosition = Vector2<double>(0.0, -abs(100.0*sin(2 * M_PI*1.0 / 40.0*animationTimer)));
				if (animationTimer == 40)
				{
					animationType = -1;
				}
				break;
			}
		}
		else
		{
			animationFlag = false;
		}
	}
}

void Character::Draw()const
{
	if (!isActive)return;
	Vector2<double> tempPos = position + transitionOffsetPosition + animationOffsetPosition;
	Function::Alpha(alpha);
	DrawRotaGraph(tempPos.x, tempPos.y, 1.0, 0.0, charaImage[ID][0], TRUE, formation == Formation::CENTER || formation == Formation::RIGHT ? TRUE : FALSE);
	Function::Alpha(255);
}

void Character::Transit(int nextID, int disappearType, int appearType)
{
	this->nextID = nextID;
	this->appearType = appearType;
	this->disappearType = disappearType;

	if (!isActive)
	{
		ID = nextID;
	}

	isActive = true;
	transitionTimer = 0;
	transitionFlag = true;
}

void Character::Disappear(int disappearType)
{
	if (!isActive)return;
	this->disappearType = disappearType;
	transitionTimer = 0;
	transitionFlag = true;
}

void Character::StartAnimation(int animationType)
{
	if (!isActive)return;
	this->animationType = animationType;
	animationTimer = 0;
	animationFlag = true;
}