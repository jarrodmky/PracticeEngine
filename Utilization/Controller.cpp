//====================================================================================================
// Filename:	Controller.cpp
// Created by:	Jarrod MacKay
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"
#include "System.h"
#include "Controller.h"

using namespace Mathematics;
using namespace Utilization;

namespace
{
	const f32 moveScale = 3.0f;
	const f32 lookScale = 0.7f;
	const f32 deadDist = 60;
	const f32 buttonDelay = 0.1f;
	f32 buttonTimer = buttonDelay;
}

Controller::Controller(System& p_System)
: m_States(p_System)
, m_Frame(nullptr)
, m_ButtonMap()
, m_AxisMap()
{
}

Controller::~Controller()
{
}

void Controller::Calibrate(Mathematics::Frame* p_Frame)
{
	m_States.Initialize();
	m_Frame = p_Frame;
	m_ButtonMap.clear();
	m_AxisMap.clear();

	m_ButtonMap[Button::Action] = {false, false};
	m_ButtonMap[Button::Quit] = {false, false};
	m_ButtonMap[Button::Pause] = {false, false};
	m_ButtonMap[Button::FullScreen] = {false, false};
	m_ButtonMap[Button::DebugScreen] = {false, false};
	m_ButtonMap[Button::EdgeDetect] = {false, false};
	m_ButtonMap[Button::CelShade] = {false, false};
	m_ButtonMap[Button::PostProcessEffectUp] = {false, false};
	m_ButtonMap[Button::PostProcessEffectDown] = {false, false};

	m_AxisMap[Axis::PPEffectIntensity] = 0.0f;

	m_States.AddButton(KeyboardKey::ENTER);
	m_States.AddButton(KeyboardKey::ESCAPE);
	m_States.AddButton(KeyboardKey::SPACE);
	m_States.AddButton(KeyboardKey::F1);
	m_States.AddButton(KeyboardKey::F2);
	m_States.AddButton(KeyboardKey::F3);
	m_States.AddButton(KeyboardKey::F4);
	m_States.AddButton(KeyboardKey::UP);
	m_States.AddButton(KeyboardKey::DOWN);
	m_States.AddButton(KeyboardKey::RIGHT);
	m_States.AddButton(KeyboardKey::LEFT);
	m_States.AddButton(KeyboardKey::W);
	m_States.AddButton(KeyboardKey::A);
	m_States.AddButton(KeyboardKey::S);
	m_States.AddButton(KeyboardKey::D);
	m_States.AddButton(KeyboardKey::Q);
	m_States.AddButton(KeyboardKey::E);

	m_States.AddButton(MouseButton::LBUTTON);

	m_States.AddButton(GamepadButton::A);
	m_States.AddButton(GamepadButton::B);
	m_States.AddButton(GamepadButton::RMAIN);
}


void Controller::Update(const f32 p_DeltaTime, const Mathematics::Vector2 p_ScreenCentre)
{
	Time("ControllerUpdate");
	m_States.Update(p_DeltaTime);

	//button update
	const std::map<KeyboardKey, bool>& keys(m_States.MouseAndKeyboard().Keys);
	const std::map<MouseButton, bool>& mouse(m_States.MouseAndKeyboard().Buttons);
	const std::map<GamepadButton, bool>& pad(m_States.Gamepad().Buttons);

	if(buttonTimer < Zero)
	{
		buttonTimer = buttonDelay;

		//button down
		m_ButtonMap[Button::Action].first = keys.at(KeyboardKey::ENTER)
			|| mouse.at(MouseButton::LBUTTON)
			|| pad.at(GamepadButton::A);
		m_ButtonMap[Button::Quit].first = keys.at(KeyboardKey::ESCAPE)
			|| pad.at(GamepadButton::B);
		m_ButtonMap[Button::Pause].first = keys.at(KeyboardKey::SPACE)
			|| pad.at(GamepadButton::RMAIN);
		m_ButtonMap[Button::FullScreen].first = keys.at(KeyboardKey::F1);
		m_ButtonMap[Button::DebugScreen].first = keys.at(KeyboardKey::F2);
		m_ButtonMap[Button::EdgeDetect].first = keys.at(KeyboardKey::F3);
		m_ButtonMap[Button::CelShade].first = keys.at(KeyboardKey::F4);
		m_ButtonMap[Button::PostProcessEffectUp].first = keys.at(KeyboardKey::RIGHT);
		m_ButtonMap[Button::PostProcessEffectDown].first = keys.at(KeyboardKey::LEFT);
	}
	else
	{
		buttonTimer -= p_DeltaTime;

		//button down
		m_ButtonMap[Button::Action].first = false;
		m_ButtonMap[Button::Quit].first = false;
		m_ButtonMap[Button::Pause].first = false;
		m_ButtonMap[Button::FullScreen].first = false;
		m_ButtonMap[Button::DebugScreen].first = false;
		m_ButtonMap[Button::EdgeDetect].first = false;
		m_ButtonMap[Button::CelShade].first = false;
		m_ButtonMap[Button::PostProcessEffectUp].first = false;
		m_ButtonMap[Button::PostProcessEffectDown].first = false;
	}

	//button held
	m_ButtonMap[Button::Action].second &= m_ButtonMap[Button::Action].first;
	m_ButtonMap[Button::Quit].second &= m_ButtonMap[Button::Quit].first;
	m_ButtonMap[Button::Pause].second &= m_ButtonMap[Button::Pause].first;
	m_ButtonMap[Button::FullScreen].second &= m_ButtonMap[Button::FullScreen].first;
	m_ButtonMap[Button::DebugScreen].second &= m_ButtonMap[Button::DebugScreen].first;
	m_ButtonMap[Button::EdgeDetect].second &= m_ButtonMap[Button::EdgeDetect].first;
	m_ButtonMap[Button::CelShade].second &= m_ButtonMap[Button::CelShade].first;
	m_ButtonMap[Button::PostProcessEffectUp].second &= m_ButtonMap[Button::PostProcessEffectUp].first;
	m_ButtonMap[Button::PostProcessEffectDown].second &= m_ButtonMap[Button::PostProcessEffectDown].first;

	//axis update
	m_AxisMap[Axis::PPEffectIntensity] = MakeAxisFromKeys(KeyboardKey::DOWN, KeyboardKey::UP);

	//look update
	f32 lineDist = moveScale * p_DeltaTime;
	Vector2 move(MakeMoveDisc());
	m_Frame->MoveForward(lineDist * move(1));
	m_Frame->MoveLeft(-lineDist * move(0));
	m_Frame->MoveUp(lineDist * MakeAxisFromKeys(KeyboardKey::Q, KeyboardKey::E));

	//move update
	f32 angleDist = lookScale * p_DeltaTime;
	Vector2 look(MakeLookDisc(p_ScreenCentre));
	m_Frame->Pitch(-angleDist * look(1));
	m_Frame->Yaw(-angleDist * look(0));

	m_States.CalibrateMouse(p_ScreenCentre);
}

bool Controller::GetButton(Button p_Button) const
{
	return m_ButtonMap.at(p_Button).first && !m_ButtonMap.at(p_Button).second;
}

f32 Controller::MakeAxisFromKeys(KeyboardKey p_Negative, KeyboardKey p_Positive) const
{
	f32 ret = 0.0f;
	if(m_States.MouseAndKeyboard().Keys.at(p_Positive))
	{
		ret += 1.0f;
	}
	if(m_States.MouseAndKeyboard().Keys.at(p_Negative))
	{
		ret -= 1.0f;
	}
	return ret;
}

Vector2 Controller::MakeMoveDisc() const
{
	Vector2 ret = Zero2();
	ret(0) = MakeAxisFromKeys(KeyboardKey::A, KeyboardKey::D);
	ret(1) = MakeAxisFromKeys(KeyboardKey::S, KeyboardKey::W);
	ret += m_States.Gamepad().LeftStick;

	return ret.IsAtOrigin() ? Zero2() : ret.Direction();
}

Vector2 Controller::MakeLookDisc(const Mathematics::Vector2 p_ScreenCentre) const
{
	Vector2 ret = m_States.MouseAndKeyboard().Position - p_ScreenCentre;
	ret = (ret.LengthSquared() > deadDist * deadDist) ? ret : Zero2();
	//ret += m_States.Gamepad().RightStick;

	return ret.IsAtOrigin() ? Zero2() : ret.Direction();
}