#include "pch.h"
#include "InputHundler.h"


//�ǉ����ꂽ���̑S�Ă�ǐՂ��邱�Ƃ��ł���
Input::Hundler::Hundler()
{
	Input::GetInstance().AddHundler(this);
}

Input::Hundler::~Hundler()
{
	Input::GetInstance().DelateHundler(this);
}
