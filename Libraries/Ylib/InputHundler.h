#pragma once
#include "Input.h"

//限定的なオブザーバー
//インプットクラスの中にあるハンドラークラスを宣言するという書き方
//インナークラス
class Input::Hundler 
{
public:
	Hundler();
	virtual ~Hundler();

	virtual void OnMouseMove(float x, float y) { x; y; }

};

