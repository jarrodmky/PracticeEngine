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
using namespace ConstantVectors;

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


	//axes or discs

	Vector leftRaw;
	Vector rightRaw;

	if (m_System->GamepadIsConnected())
	{
		leftRaw.x = m_System->GetLeftAnalogX();
		leftRaw.y = m_System->GetLeftAnalogY();
		rightRaw.x = m_System->GetRightAnalogX();
		rightRaw.y = m_System->GetRightAnalogY();

		m_LeftDisc = coordinate(leftRaw.x, leftRaw.y);
		m_RightDisc = coordinate(rightRaw.x, rightRaw.y);
	}
	else
	{
		if (m_System->IsKeyDown(Keys::A))
		{
			leftRaw += -I;
		}

		if (m_System->IsKeyDown(Keys::D))
		{
			leftRaw += I;
		}

		if (m_System->IsKeyDown(Keys::W))
		{
			leftRaw += J;
		}

		if (m_System->IsKeyDown(Keys::S))
		{
			leftRaw += -J;
		}

		if (m_System->IsKeyDown(Keys::LEFT))
		{
			rightRaw += -I;
		}

		if (m_System->IsKeyDown(Keys::RIGHT))
		{
			rightRaw += I;
		}

		if (m_System->IsKeyDown(Keys::UP))
		{
			rightRaw += J;
		}

		if (m_System->IsKeyDown(Keys::DOWN))
		{
			rightRaw += -J;
		}

		if (!EquivalentToZero(leftRaw.LengthSquared()))
		{
			leftRaw.Normalize();
			m_LeftDisc = coordinate(leftRaw.x, leftRaw.y);
		}

		if (!EquivalentToZero(rightRaw.LengthSquared()))
		{
			rightRaw.Normalize();
			m_RightDisc = coordinate(rightRaw.x, rightRaw.y);
		}
	}
}

void InputState::Reset()
{
	m_ActionPressed = false;
	m_ConfirmPressed = false;
	m_DenyPressed = false;

	m_LeftDisc = coordinate();
	m_RightDisc = coordinate();
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

f32 InputState::GetLeftVerticalAxis() const
{
	return m_LeftDisc.v;
}

f32 InputState::GetRightVerticalAxis() const
{
	return m_RightDisc.v;
}

f32 InputState::GetLeftHorizontalAxis() const
{
	return m_LeftDisc.u;
}

f32 InputState::GetRightHorizontalAxis() const
{
	return m_RightDisc.u;
}