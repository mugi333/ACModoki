#include "pch.h"
#include "Input.h"
#include "InputHundler.h"
#include <Windows.h>
#include <Wingdi.h>
#include <iostream>


//�V���O���g��
Input& Input::GetInstance()
{
	static Input me;

	return me;
}

void Input::Updata()
{
	m_mouseTracker->Update(m_mouse->GetState());

}

void Input::SetWindow(HWND window)
{
	m_window = window;

	// �}�E�X���g�p�ł����Ԃɂ���
	/*m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();*/

	// �L�[�{�[�h���g�p�ł����Ԃɂ���
	/*m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();*/



}

void Input::MouseMove(LPARAM lparam)
{

	WINDOWINFO windowInfo;

	POINT POINT;
	GetCursorPos(&POINT);

	

	//�E�B���h�E�̍\���̂̃T�C�Y��������
	windowInfo.cbSize = sizeof(WINDOWINFO);

	//�E�B���h�E�̏����擾
	GetWindowInfo(m_window, &windowInfo);

	//�E�B���h�E��̍��W�ɕϊ�����
	ScreenToClient(m_window, &POINT);

	CollHundlerFanction(&Hundler::OnMouseMove, static_cast<float>(POINT.x), static_cast<float>(POINT.y));



}

void Input::SetCursolPosition(float x, float y)
{
	//WINDOWINFO windowInfo;

	//�E�B���h�E�̍\���̂̃T�C�Y��������
	//windowInfo.cbSize = sizeof(WINDOWINFO);

	//�E�B���h�E�̃N���C�A���g�̈�̏����擾
	//RECT RECT;
	//GetWindowRect(m_window, &RECT);


	//�J�[�\���̍��W���Z�b�g���Ă���
	//SetCursorPos(RECT.left + (RECT.right * (1.0f + x) / 2.0f),
	//	RECT.top + (RECT.bottom * (1.0f + y) / 2.0f));
	
	WINDOWINFO windowInfo;
	//�E�B���h�E�̈ʒu���擾
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(m_window, &windowInfo);

	SetCursorPos(x + windowInfo.rcClient.left, y + windowInfo.rcClient.top);


}

Input::Input()
{
	AllocConsole();
	//    �W�����o�͂Ɋ��蓖�Ă�恙
	FILE* console = NULL;
	freopen_s(&console, "CONOUT$", "w+", stdout); 
	freopen_s(&console, "CONIN$", "r+", stdin);
}

Input::~Input()
{
}

void Input::AddHundler(Hundler* hundler)
{

	m_hundler.push_back(hundler);

}

void Input::DelateHundler(Hundler* hundler)
{

	m_hundler.erase(std::find(m_hundler.begin(), m_hundler.end(), hundler));



	
}
