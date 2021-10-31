#pragma once

#include"Define.h"
#include"Class.h"

class Mouse
{
	static bool click[3];							//�L�[���͏�Ԃ̊i�[
	static bool clickPre[3];						//�L�[���͍X�V�O�̓��͏�Ԃ�ۑ�
	static bool clickOnce[3];						//�L�[���͏�Ԃ̊i�[(����������Ȃ�)
private:
	Mouse() {};
	Mouse(const Mouse&) {};
	Mouse& operator =(const Mouse&) {};
public:
	static void Update();							//�L�[���͍X�V�֘A�̊֐��̓���
	static bool ClickOnce(int);						//�L�[����(�񒷉���)
	static bool Click(int);							//�L�[����(�������Ή�)
	static Vector2<double> GetMousePos();
};