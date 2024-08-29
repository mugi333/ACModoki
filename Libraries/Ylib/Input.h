#pragma once
#include <vector>

class Input
{
public:
	//インナークラス
	class Hundler;

	static Input& GetInstance();

	void Updata();

	void SetWindow( HWND window);

	void MouseMove(LPARAM lparam);

	void SetCursolPosition(float x, float y);

private:

	// マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;
	DirectX::Mouse::State m_mouseState;

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;

	//ウィンドウハンドル
	 HWND m_window;
	
	Input();
	~Input();
	
	void AddHundler(Hundler* hundler);
	void DelateHundler(Hundler* hundler);

	//関数ポインタ→関数を引数として持ってくる
	//関数だけを指定したいので指定した関数だけ持ってくる
	//void型の（Hunderクラスの関数ポインタ）（引数リスト）
	//void(Hundler::*Func)(Argument...)
	//Argument... は可変長引数
	//関数と引数がワカラナイので引数を指定するためのもの
	// 指定した関数だけ呼び出すもの
	//
	template<class ...Argument>

	void CollHundlerFanction(void(Hundler::*Func)(Argument...),Argument...argument)
	{
		for (Hundler* hunder: m_hundler)
		{
			(hunder->*Func)(argument...);
		}
	
	}

	std::vector<Hundler*> m_hundler;


};

