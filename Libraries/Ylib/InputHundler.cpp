#include "pch.h"
#include "InputHundler.h"


//追加されたもの全てを追跡することができる
Input::Hundler::Hundler()
{
	Input::GetInstance().AddHundler(this);
}

Input::Hundler::~Hundler()
{
	Input::GetInstance().DelateHundler(this);
}
