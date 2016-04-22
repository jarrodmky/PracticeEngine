#ifndef IncludedUtilInputStateH
#define IncludedUtilInputStateH

//====================================================================================================
// Filename:	InputState.h
// Created by:	Jarrod MacKay
// Description:	Abstracts keyboard, mouse and gamepad input so the game only deals with the state of key bindings.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <Mathematics.h>
#include "InputTypes.h"

namespace Utilization
{

	//====================================================================================================
	// Definitions
	//====================================================================================================
	class System;

	class InputStates
	{
		typedef std::pair<KeyboardKey, bool> KeyState;
		typedef std::pair<MouseButton, bool> MouseButtonState;
		typedef std::pair<GamepadButton, bool> GamepadButtonState;
		
		struct MouseBoardState
		{
			std::map<KeyboardKey, bool> Keys;
			std::map<MouseButton, bool> Buttons;
			Mathematics::Vector2 Position;
			Mathematics::Vector2 LastPosition;
			Mathematics::Vector2 Velocity;
			bool Connected;
		};

		struct GamepadState
		{
			std::map<GamepadButton, bool> Buttons;
			Mathematics::Vector2 LeftStick;
			Mathematics::Vector2 RightStick;
			f32 LeftTrigger;
			f32 RightTrigger;
			bool UpD;
			bool DownD;
			bool LeftD;
			bool RightD;
			bool Connected;
		};

		//Attributes
	private:

		MouseBoardState m_MouseBoard;
		GamepadState m_Gamepad;

		System& m_System;

		Mathematics::Vector2 m_LeftStickOrigin;
		Mathematics::Vector2 m_RightStickOrigin;
		
		//Operators
	public:

		InputStates(System& p_System);

		~InputStates();

		//Methods
	public:

		void Initialize();
		void Update(const f32 p_DeltaTime);

		const MouseBoardState& MouseAndKeyboard() const { return m_MouseBoard; }
		const GamepadState& Gamepad() const { return m_Gamepad; }

		void CalibrateMouse(const Mathematics::Vector2& p_ViewportCentre);
		void CalibrateGamepad();

		void AddButton(KeyboardKey p_Button) { m_MouseBoard.Keys.insert(KeyState(p_Button, false)); }
		void AddButton(MouseButton p_Button) { m_MouseBoard.Buttons.insert(MouseButtonState(p_Button, false)); }
		void AddButton(GamepadButton p_Button) { m_Gamepad.Buttons.insert(GamepadButtonState(p_Button, false)); }

	private:

		void UpdateButtons();
		void ResetButtons();
	};

}

#endif