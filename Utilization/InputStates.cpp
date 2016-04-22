//====================================================================================================
// Filename:	InputState.cpp
// Created by:	Jarrod MacKay
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"
#include "System.h"
#include "InputStates.h"
#include "InputTypes.h"

using namespace Mathematics;
using namespace Utilization;

namespace
{
}

InputStates::InputStates(System& p_System)
	: m_MouseBoard()
	, m_Gamepad()
	, m_System(p_System)
	, m_LeftStickOrigin()
	, m_RightStickOrigin()
{}

InputStates::~InputStates()
{}

void InputStates::Initialize()
{
	m_System.Update();
	CalibrateGamepad();
	
	//init mouse and kb
	m_MouseBoard.Keys.clear();
	m_MouseBoard.Buttons.clear();
	m_MouseBoard.Position = Zero2();
	m_MouseBoard.LastPosition = Zero2();
	m_MouseBoard.Velocity = Zero2();
	m_MouseBoard.Connected = m_System.MouseIsConnected() && m_System.KeyboardIsConnected();

	//init gamepad
	m_Gamepad.Buttons.clear();
	m_Gamepad.LeftStick = Zero2();
	m_Gamepad.RightStick = Zero2();
	m_Gamepad.LeftTrigger = Zero;
	m_Gamepad.RightTrigger = Zero;
	m_Gamepad.UpD = false;
	m_Gamepad.DownD = false;
	m_Gamepad.LeftD = false;
	m_Gamepad.RightD = false;
	m_Gamepad.Connected = m_System.GamepadIsConnected();
}

void InputStates::Update(const f32 p_DeltaTime)
{
	//update buttons
	ResetButtons();
	m_System.Update();
	UpdateButtons();

	//update axes
	if (m_MouseBoard.Connected)
	{
		m_MouseBoard.LastPosition = m_MouseBoard.Position;
		m_MouseBoard.Position(0) = static_cast<f32>(m_System.GetMouseScreenX());
		m_MouseBoard.Position(1) = static_cast<f32>(m_System.GetMouseScreenY());
		m_MouseBoard.Velocity = Inverse(p_DeltaTime) * (m_MouseBoard.Position - m_MouseBoard.LastPosition);
	}
	if (m_Gamepad.Connected)
	{
		Vector2 leftRaw(MakeVector(m_System.GetLeftAnalogX(), m_System.GetLeftAnalogY()));
		Vector2 rightRaw(MakeVector(m_System.GetRightAnalogX(), m_System.GetRightAnalogY()));
		m_Gamepad.LeftStick = (leftRaw - m_LeftStickOrigin).Direction();
		m_Gamepad.RightStick = (rightRaw - m_RightStickOrigin).Direction();
		m_Gamepad.LeftTrigger = m_System.GetLeftTrigger();
		m_Gamepad.RightTrigger = m_System.GetRightTrigger();
		m_Gamepad.UpD = m_System.IsDPadUp();
		m_Gamepad.DownD = m_System.IsDPadDown();
		m_Gamepad.LeftD = m_System.IsDPadLeft();
		m_Gamepad.RightD = m_System.IsDPadRight();
	}
}

void InputStates::CalibrateMouse(const Vector2& p_ViewportCentre)
{
	if (m_MouseBoard.Connected)
	{
		m_MouseBoard.Position = p_ViewportCentre;
		m_MouseBoard.LastPosition = p_ViewportCentre;
		m_MouseBoard.Velocity = Zero2();
	}
}

void InputStates::CalibrateGamepad()
{
	if (!m_Gamepad.Connected)
	{
		m_LeftStickOrigin = MakeVector(m_System.GetLeftAnalogX(), m_System.GetLeftAnalogY());
		m_RightStickOrigin = MakeVector(m_System.GetRightAnalogX(), m_System.GetRightAnalogY());
	}
}

void InputStates::UpdateButtons()
{
	if (m_MouseBoard.Connected)
	{
		for (auto& k : m_MouseBoard.Keys)
		{
			k.second = m_System.IsKeyDown(static_cast<u32>(k.first));
		}
		for (auto& m : m_MouseBoard.Buttons)
		{
			m.second = m_System.IsMouseDown(static_cast<u32>(m.first));
		}
	}
	if (m_Gamepad.Connected)
	{
		for (auto& b : m_Gamepad.Buttons)
		{
			b.second = m_System.IsGamePadButtonDown(static_cast<u32>(b.first));
		}
	}
}

void InputStates::ResetButtons()
{
	if (m_MouseBoard.Connected)
	{
		for (auto& k : m_MouseBoard.Keys)
		{
			k.second = false;
		}
		for (auto& m : m_MouseBoard.Buttons)
		{
			m.second = false;
		}
	}
	if (m_Gamepad.Connected)
	{
		for (auto& b : m_Gamepad.Buttons)
		{
			b.second = false;
		}
	}
}