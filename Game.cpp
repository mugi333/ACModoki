//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Game/Screen.h"
#include "Game/Scene/SceneManager.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
    :
    m_deviceResources{},
    m_timer{},
    m_commonStates{},
    m_commonResources{},
    m_debugString{},
    m_inputManager{},
    m_sceneManager{}
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    // �f�o�C�X���\�[�X�֘A��ݒ肷��
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */


    // ���ǋL�R�R���火������

    // �f�o�C�X�ƃR���e�L�X�g���擾����
    auto device  = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // ���̓}�l�[�W�����쐬����
    m_inputManager = std::make_unique<mylib::InputManager>(window);

    // �R�����X�e�[�g���쐬����
    m_commonStates = std::make_unique<CommonStates>(device);

    // �f�o�b�O��������쐬����
    m_debugString = std::make_unique<mylib::DebugString>(
        device,
        context,
        L"Resources/Fonts/SegoeUI_18.spritefont"
    );

    // ���ʃ��\�[�X���쐬����
    m_commonResources = std::make_unique<CommonResources>();

    // �V�[���֓n�����ʃ��\�[�X��ݒ肷��
    m_commonResources->Initialize(
        &m_timer,
        m_deviceResources.get(),
        m_commonStates.get(),
        m_debugString.get(),
        m_inputManager.get()
    );

    // �V�[���}�l�[�W��������������
    m_sceneManager = std::make_unique<SceneManager>();
    m_sceneManager->Initialize(m_commonResources.get());

    // ���ǋL�R�R�܂Ł�������
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.


    // ���ǋL�R�R���火������

    // ���̓}�l�[�W�����X�V����
    m_inputManager->Update();

    // �L�[�{�[�h�X�e�[�g���擾����
    const auto& keyboardState = m_inputManager->GetKeyboardState();

    // �uECS�v�L�[�ŏI������
    if (keyboardState.Escape)
    {
        ExitGame();
    }

    // �V�[���}�l�[�W�����X�V����
    m_sceneManager->Update(elapsedTime);

    // ���ǋL�R�R�܂Ł�������
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.


    // ���ǋL�R�R���火������

    UNREFERENCED_PARAMETER(context);

    // �f�o�b�O��������쐬����FFPS
    m_debugString->AddString("fps : %d", m_timer.GetFramesPerSecond());

    // �V�[���}�l�[�W����`�悷��
    m_sceneManager->Render();

    // �f�o�b�O�������`�悷��
    m_debugString->Render(m_commonStates.get());

    // ���ǋL�R�R�܂Ł�������


    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width   = Screen::WIDTH;    // ���ύX::800->Screen::WIDTH
    height  = Screen::HEIGHT;   // ���ύX::600->Screen::HEIGHT
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

    // ���ǋL��
    UNREFERENCED_PARAMETER(device);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
