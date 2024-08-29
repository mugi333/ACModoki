#include "pch.h"
#include "InputHundler.h"


//’Ç‰Á‚³‚ê‚½‚à‚Ì‘S‚Ä‚ğ’ÇÕ‚·‚é‚±‚Æ‚ª‚Å‚«‚é
Input::Hundler::Hundler()
{
	Input::GetInstance().AddHundler(this);
}

Input::Hundler::~Hundler()
{
	Input::GetInstance().DelateHundler(this);
}
