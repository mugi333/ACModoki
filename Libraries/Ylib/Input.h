#pragma once
#include <vector>

class Input
{
public:
	//�C���i�[�N���X
	class Hundler;

	static Input& GetInstance();

	void Updata();

	void SetWindow( HWND window);

	void MouseMove(LPARAM lparam);

	void SetCursolPosition(float x, float y);

private:

	// �}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;
	DirectX::Mouse::State m_mouseState;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;

	//�E�B���h�E�n���h��
	 HWND m_window;
	
	Input();
	~Input();
	
	void AddHundler(Hundler* hundler);
	void DelateHundler(Hundler* hundler);

	//�֐��|�C���^���֐��������Ƃ��Ď����Ă���
	//�֐��������w�肵�����̂Ŏw�肵���֐����������Ă���
	//void�^�́iHunder�N���X�̊֐��|�C���^�j�i�������X�g�j
	//void(Hundler::*Func)(Argument...)
	//Argument... �͉ϒ�����
	//�֐��ƈ��������J���i�C�̂ň������w�肷�邽�߂̂���
	// �w�肵���֐������Ăяo������
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

