#pragma once
#include "Input.h"

//����I�ȃI�u�U�[�o�[
//�C���v�b�g�N���X�̒��ɂ���n���h���[�N���X��錾����Ƃ���������
//�C���i�[�N���X
class Input::Hundler 
{
public:
	Hundler();
	virtual ~Hundler();

	virtual void OnMouseMove(float x, float y) { x; y; }

};

