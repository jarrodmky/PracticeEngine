//====================================================================================================
// Filename:	InputState.cpp
// Created by:	Jarrod MacKay
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"
#include "InputState.h"
#include "InputTypes.h"

using namespace Mathematics;
using namespace Utilization;

InputState::InputState(System& p_System)
: m_System(&p_System)
, m_LeftDisc()
, m_RightDisc()
, m_ActionPressed(false)
, m_ConfirmPressed(false)
, m_DenyPressed(false)
{}

InputState::~InputState() 
{}

void InputState::Calibrate()
{
	m_System->Update();
	m_LeftDiscCentre(1) = m_System->GetLeftAnalogX();
	m_RightDiscCentre(1) = m_System->GetRightAnalogX();
	m_LeftDiscCentre(2) = m_System->GetLeftAnalogY();
	m_RightDiscCentre(2) = m_System->GetRightAnalogY();
}

void InputState::Update()
{
	Reset();
	m_System->Update();

	//buttons

	if (m_System->IsKeyDown(Keys::SPACE) || m_System->IsGamePadButtonDown(Xbox::A))
	{
		m_ActionPressed = true;
	}

	if (m_System->IsKeyDown(Keys::ENTER) || m_System->IsGamePadButtonDown(Xbox::X))
	{
		m_ConfirmPressed = true;
	}

	if (m_System->IsKeyDown(Keys::ESCAPE) || m_System->IsGamePadButtonDown(Xbox::Y))
	{
		m_DenyPressed = true;
	}

	if(m_System->IsKeyDown(Keys::F1))
	{
		m_FullscreenPressed = true;
	}
	
	//axes or discs

	Vector2 leftRaw;
	Vector2 rightRaw;

	if (m_System->GamepadIsConnected())
	{
		leftRaw(1) = -m_System->GetLeftAnalogX();
		leftRaw(2) = m_System->GetLeftAnalogY();
		rightRaw(1) = m_System->GetRightAnalogX();
		rightRaw(2) = m_System->GetRightAnalogY();

		m_LeftDisc = leftRaw - m_LeftDiscCentre;
		m_RightDisc = rightRaw - m_LeftDiscCentre;
	}
	else
	{
		if (m_System->IsKeyDown(Keys::A))
		{
			leftRaw += U();
		}

		if (m_System->IsKeyDown(Keys::D))
		{
			leftRaw += -U();
		}

		if (m_System->IsKeyDown(Keys::W))
		{
			leftRaw += V();
		}

		if (m_System->IsKeyDown(Keys::S))
		{
			leftRaw += -V();
		}

		if (m_System->IsKeyDown(Keys::LEFT))
		{
			rightRaw += -U();
		}

		if (m_System->IsKeyDown(Keys::RIGHT))
		{
			rightRaw += U();
		}

		if (m_System->IsKeyDown(Keys::UP))
		{
			rightRaw += V();
		}

		if (m_System->IsKeyDown(Keys::DOWN))
		{
			rightRaw += -V();
		}

		if (!EquivalentToZero(leftRaw.LengthSquared()))
		{
			m_LeftDisc = leftRaw.Direction();
		}

		if (!EquivalentToZero(rightRaw.LengthSquared()))
		{
			m_RightDisc = rightRaw.Direction();
		}
	}
}

void InputState::Reset()
{
	m_ActionPressed = false;
	m_ConfirmPressed = false;
	m_DenyPressed = false;
	m_FullscreenPressed = false;

	m_LeftDisc = Zero2();
	m_RightDisc = Zero2();
}

bool InputState::Actioned() const
{
	return m_ActionPressed;
}

bool InputState::Confirmed() const
{
	return m_ConfirmPressed;
}

bool InputState::Denied() const
{
	return m_DenyPressed;
}

bool InputState::Fullscreen() const
{
	return m_FullscreenPressed;
}

f32 InputState::GetLeftVerticalAxis() const
{
	return m_LeftDisc(2);
}

f32 InputState::GetRightVerticalAxis() const
{
	return m_RightDisc(2);
}

f32 InputState::GetLeftHorizontalAxis() const
{
	return m_LeftDisc(1);
}

f32 InputState::GetRightHorizontalAxis() const
{
	return m_RightDisc(1);
}