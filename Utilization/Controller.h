#ifndef IncludedUtilControllerH
#define IncludedUtilControllerH

//====================================================================================================
// Filename:	Controller.h
// Created by:	Jarrod MacKay
// Description:	Abstracts keyboard, mouse and gamepad input so the game only deals with the state of key bindings.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <Mathematics.h>
#include "InputTypes.h"
#include "InputStates.h"

namespace Utilization
{

	//====================================================================================================
	// Definitions
	//====================================================================================================
	class System;

	enum class Button : u32
	{
		Action,
		Quit,
		Pause,
		FullScreen,
		DebugScreen,
		EdgeDetect,
		CelShade,
		PostProcessEffectUp,
		PostProcessEffectDown
	};

	enum class Axis : u32
	{
		PPEffectIntensity = 0
	};

	class Controller
	{

		//Attributes
	private:

		InputStates m_States;
		Mathematics::Frame* m_Frame;
		std::map<Button, std::pair<bool, bool> > m_ButtonMap; //pressed / held
		std::map<Axis, f32> m_AxisMap;

		//Operators
	public:

		Controller(System& p_System);
		~Controller();

		//Methods
	public:

		void Calibrate(Mathematics::Frame* p_Frame);
		void Update(const f32 p_DeltaTime
					, const Mathematics::Vector2 p_ScreenCentre);

		bool GetButton(Button p_Button) const;
		f32 GetAxis(Axis p_Axis) const { return m_AxisMap.at(p_Axis); }

	private:

		f32 MakeAxisFromKeys(KeyboardKey p_A, KeyboardKey p_B) const;
		Mathematics::Vector2 MakeMoveDisc() const;
		Mathematics::Vector2 MakeLookDisc(const Mathematics::Vector2 p_ScreenCentre) const;
	};
}

#endif