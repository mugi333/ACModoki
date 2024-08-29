#include "pch.h"
#include "Input.h"
#include "InputHundler.h"
#include <Windows.h>
#include <Wingdi.h>
#include <iostream>


//シングルトン
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

	// マウスを使用できる状態にする
	/*m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();*/

	// キーボードを使用できる状態にする
	/*m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();*/



}

void Input::MouseMove(LPARAM lparam)
{

	WINDOWINFO windowInfo;

	POINT POINT;
	GetCursorPos(&POINT);

	

	//ウィンドウの構造体のサイズを代入する
	windowInfo.cbSize = sizeof(WINDOWINFO);

	//ウィンドウの情報を取得
	GetWindowInfo(m_window, &windowInfo);

	//ウィンドウ上の座標に変換する
	ScreenToClient(m_window, &POINT);

	CollHundlerFanction(&Hundler::OnMouseMove, static_cast<float>(POINT.x), static_cast<float>(POINT.y));



}

void Input::SetCursolPosition(float x, float y)
{
	//WINDOWINFO windowInfo;

	//ウィンドウの構造体のサイズを代入する
	//windowInfo.cbSize = sizeof(WINDOWINFO);

	//ウィンドウのクライアント領域の情報を取得
	//RECT RECT;
	//GetWindowRect(m_window, &RECT);


	//カーソルの座標をセットしている
	//SetCursorPos(RECT.left + (RECT.right * (1.0f + x) / 2.0f),
	//	RECT.top + (RECT.bottom * (1.0f + y) / 2.0f));
	
	WINDOWINFO windowInfo;
	//ウィンドウの位置を取得
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(m_window, &windowInfo);

	SetCursorPos(x + windowInfo.rcClient.left, y + windowInfo.rcClient.top);


}

Input::Input()
{
	AllocConsole();
	//    標準入出力に割り当てるよ☆
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
