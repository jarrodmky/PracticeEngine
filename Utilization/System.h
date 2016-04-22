#ifndef INCLUDED_INPUT_SYSTEM_H
#define INCLUDED_INPUT_SYSTEM_H

//====================================================================================================
// Filename:	System.h
// Created by:	Peter Chan
// Modified by: Jarrod MacKay
// Description:	Class for the input system with support for keyboard, mouse, and gamepad devices.
//====================================================================================================

#include <Mathematics.h>

//====================================================================================================
// Namespace
//====================================================================================================

namespace Utilization
{

//====================================================================================================
// Class Declarations
//====================================================================================================

class System
{
public:
	System();
	~System();

	void Initialize(HWND window);
	void Terminate();

	void Update();

	bool KeyboardIsConnected() const { return mpKeyboardDevice != nullptr; }
	bool MouseIsConnected() const { return mpMouseDevice != nullptr; }
	bool GamepadIsConnected() const { return mpGamePadDevice != nullptr; }

	//keyboard

	bool IsKeyDown(u32 key) const;
	bool IsKeyPressed(u32 key) const;

	//mouse

	bool IsMouseDown(u32 button) const;
	bool IsMousePressed(u32 button) const;

	s32 GetMouseScreenX() const;
	s32 GetMouseScreenY() const;

	s32 GetMouseMoveX() const;
	s32 GetMouseMoveY() const;
	s32 GetMouseMoveZ() const;

	bool IsMouseLeftEdge() const;
	bool IsMouseRightEdge() const;
	bool IsMouseTopEdge() const;
	bool IsMouseBottomEdge() const;

	//gamepad

	bool IsGamePadButtonDown(u32 button) const;
	bool IsGamePadButtonPressed(u32 button) const;

	bool IsDPadUp() const;
	bool IsDPadDown() const;
	bool IsDPadLeft() const;
	bool IsDPadRight() const;

	f32 GetLeftAnalogX() const;
	f32 GetLeftAnalogY() const;
	f32 GetRightAnalogX() const;
	f32 GetRightAnalogY() const;

	f32 GetLeftTrigger() const;
	f32 GetRightTrigger() const;

private:
	NonCopyable(System);
	
	friend BOOL CALLBACK EnumGamePadCallback(const DIDEVICEINSTANCE* pDIDeviceInstance, VOID* pContext);

	void UpdateKeyboard();
	void UpdateMouse();
	void UpdateGamePad();

	IDirectInput8* mpDirectInput;
	IDirectInputDevice8* mpKeyboardDevice;
	IDirectInputDevice8* mpMouseDevice;
	IDirectInputDevice8* mpGamePadDevice;

	static const u32 kKeyBufferSize = 256;
	u8 mCurrKeyBuffer[kKeyBufferSize];
	u8 mPrevKeyBuffer[kKeyBufferSize];

	DIMOUSESTATE mCurrMouseState;
	DIMOUSESTATE mPrevMouseState;

	DIJOYSTATE mCurrGamePadState;
	DIJOYSTATE mPrevGamePadState;

	s32 mMouseX;
	s32 mMouseY;

	s32 mScreenWidth;
	s32 mScreenHeight;

	bool mInitialized;
};

} // namespace Input

#endif // #ifndef INCLUDED_INPUT_SYSTEM_H