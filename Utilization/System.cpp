//====================================================================================================
// Filename:	System.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "System.h"

using namespace Input;

//====================================================================================================
// Callback Definitions
//====================================================================================================

BOOL CALLBACK Input::EnumGamePadCallback(const DIDEVICEINSTANCE* pDIDeviceInstance, VOID* pContext)
{
	// Obtain an interface to the enumerated joystick
	System* inputSystem = static_cast<System*>(pContext);
	IDirectInput8* pDI = inputSystem->mpDirectInput;
	IDirectInputDevice8** pGamePad = &(inputSystem->mpGamePadDevice);
	if (FAILED(pDI->CreateDevice(pDIDeviceInstance->guidInstance, pGamePad, nullptr))) 
	{
		Assert(false, "[System] Failed to create game pad device.");
	}

	return DIENUM_STOP;
}

//====================================================================================================
// Class Definitions
//====================================================================================================

System::System()
	: mpDirectInput(nullptr)
	, mpKeyboardDevice(nullptr)
	, mpMouseDevice(nullptr)
	, mpGamePadDevice(nullptr)
	, mMouseX(0)
	, mMouseY(0)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mInitialized(false)
{
	ZeroMemory(mCurrKeyBuffer, kKeyBufferSize);
	ZeroMemory(mPrevKeyBuffer, kKeyBufferSize);
	ZeroMemory(&mCurrMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&mPrevMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&mCurrGamePadState, sizeof(DIJOYSTATE));
	ZeroMemory(&mPrevGamePadState, sizeof(DIJOYSTATE));
}

//----------------------------------------------------------------------------------------------------

System::~System()
{
	Assert(!mInitialized, "[System] Terminate() must be called to clean up!");
}

//----------------------------------------------------------------------------------------------------

void System::Initialize(HWND window)
{
	// Check if we have already initialized the system
	if (mInitialized)
	{
		Assert(false, "[System] System already initialized.");
	}

	//LOG("[System] Initializing...");

	// Obtain an interface to DirectInput
	HRESULT hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mpDirectInput, nullptr);
	Assert(SUCCEEDED(hr), "[System] Failed to create DirectInput object.");

	//----------------------------------------------------------------------------------------------------
	// Create keyboard device
	hr = mpDirectInput->CreateDevice(GUID_SysKeyboard, &mpKeyboardDevice, nullptr);
	Assert(SUCCEEDED(hr), "[System] Failed to create keyboard device.");

	// Set the keyboard data format
	hr = mpKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	Assert(SUCCEEDED(hr), "[System] Failed to set keyboard data format.");

	// Set the keyboard cooperative level
	hr = mpKeyboardDevice->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	Assert(SUCCEEDED(hr), "[System] Failed to set keyboard cooperative level.");

	// Acquire the keyboard device
	hr = mpKeyboardDevice->Acquire();
	Assert(SUCCEEDED(hr), "[System] Failed to acquire keyboard device.");
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// Create mouse device
	hr = mpDirectInput->CreateDevice(GUID_SysMouse, &mpMouseDevice, nullptr);
	Assert(SUCCEEDED(hr), "[System] Failed to create mouse device.");

	// Set the mouse data format
	hr = mpMouseDevice->SetDataFormat(&c_dfDIMouse);
	Assert(SUCCEEDED(hr), "[System] Failed to set mouse data format.");

	// Set the mouse cooperative level
	hr = mpMouseDevice->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	Assert(SUCCEEDED(hr), "[System] Failed to set mouse cooperative level.");

	// Acquire the mouse device
	hr = mpMouseDevice->Acquire();
	Assert(SUCCEEDED(hr), "[System] Failed to acquire mouse device.");

	// Calculate starting mouse position
	RECT clientRect;
	GetClientRect(window, &clientRect);
	GetWindowRect(window, &clientRect);
	mScreenWidth = clientRect.right - clientRect.left;
	mScreenHeight = clientRect.bottom - clientRect.top;
	mMouseX = mScreenWidth >> 1;
	mMouseY = mScreenHeight >> 1;
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// Enumerate for game pad device
	if (FAILED(mpDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGamePadCallback, this, DIEDFL_ATTACHEDONLY)))
	{
		Assert(false, "[System] Failed to enumerate for game pad devices.");
	}

	// Check if we have a game pad detected
	if (mpGamePadDevice != nullptr)
	{
		// Set the game pad data format
		hr = mpGamePadDevice->SetDataFormat(&c_dfDIJoystick);
		Assert(SUCCEEDED(hr), "[System] Failed to set game pad data format.");

		// Set the game pad cooperative level
		hr = mpGamePadDevice->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		Assert(SUCCEEDED(hr), "[System] Failed to set game pad cooperative level.");

		// Acquire the game pad device
		hr = mpGamePadDevice->Acquire();
		Assert(SUCCEEDED(hr), "[System] Failed to acquire game pad device.");
	}
	else
	{
		//LOG("[System] No game pad attached.");
	}

	// Set flag
	mInitialized = true;

	//LOG("[System] System initialized.");
}

//----------------------------------------------------------------------------------------------------

void System::Terminate()
{
	// Check if we have already terminated the system
	if (!mInitialized)
	{
		Assert(false, "[System] System already terminated.");
	}

	//LOG("[System] Terminating...");

	// Release devices
	if (mpGamePadDevice != nullptr)
	{
		mpGamePadDevice->Unacquire();
		mpGamePadDevice->Release();
		mpGamePadDevice = nullptr;
	}
	if (mpMouseDevice != nullptr)
	{
		mpMouseDevice->Unacquire();
		mpMouseDevice->Release();
		mpMouseDevice = nullptr;
	}
	if (mpKeyboardDevice != nullptr)
	{
		mpKeyboardDevice->Unacquire();
		mpKeyboardDevice->Release();
		mpKeyboardDevice = nullptr;
	}

	ProperlyRelease(mpDirectInput);

	// Set flag
	mInitialized = false;

	//LOG("[System] System terminated.");
}

//----------------------------------------------------------------------------------------------------

void System::Update()
{
	Assert(mInitialized, "[System] System not initialized.");

	// Update keyboard
	if (mpKeyboardDevice != nullptr)
	{
		UpdateKeyboard();
	}

	// Update mouse
	if (mpMouseDevice != nullptr)
	{
		UpdateMouse();
	}

	// Update game pad
	if (mpGamePadDevice != nullptr)
	{
		UpdateGamePad();
	}
}

//----------------------------------------------------------------------------------------------------

bool System::IsKeyDown(u32 key) const
{
	return (mCurrKeyBuffer[key] & 0x80) != 0;
}

//----------------------------------------------------------------------------------------------------

bool System::IsKeyPressed(u32 key) const
{
	const bool currState = (mCurrKeyBuffer[key] & 0x80) != 0;
	const bool prevState = (mPrevKeyBuffer[key] & 0x80) != 0;
	return !prevState && currState;
}

//----------------------------------------------------------------------------------------------------

bool System::IsMouseDown(u32 button) const
{
	return (mCurrMouseState.rgbButtons[button] & 0x80) != 0;
}

//----------------------------------------------------------------------------------------------------

bool System::IsMousePressed(u32 button) const
{
	const bool currState = (mCurrMouseState.rgbButtons[button] & 0x80) != 0;
	const bool prevState = (mPrevMouseState.rgbButtons[button] & 0x80) != 0;
	return !prevState && currState;
}

//----------------------------------------------------------------------------------------------------

s32 System::GetMouseScreenX() const
{
	return mMouseX;
}

//----------------------------------------------------------------------------------------------------

s32 System::GetMouseScreenY() const
{
	return mMouseY;
}

//----------------------------------------------------------------------------------------------------

bool System::IsMouseLeftEdge() const
{
	return (mMouseX == 0);
}

//----------------------------------------------------------------------------------------------------

bool System::IsMouseRightEdge() const
{
	return (mMouseX == mScreenWidth - 1);
}

//----------------------------------------------------------------------------------------------------

bool System::IsMouseTopEdge() const
{
	return (mMouseY == 0);
}

//----------------------------------------------------------------------------------------------------

bool System::IsMouseBottomEdge() const
{
	return (mMouseY == mScreenHeight - 1);
}

//----------------------------------------------------------------------------------------------------

s32 System::GetMouseMoveX() const
{
	return mCurrMouseState.lX;
}

//----------------------------------------------------------------------------------------------------

s32 System::GetMouseMoveY() const
{
	return mCurrMouseState.lY;
}

//----------------------------------------------------------------------------------------------------

s32 System::GetMouseMoveZ() const
{
	return mCurrMouseState.lZ;
}

//----------------------------------------------------------------------------------------------------

bool System::IsGamePadButtonDown(u32 button) const
{
	return (mCurrGamePadState.rgbButtons[button] & 0x80) != 0;
}

//----------------------------------------------------------------------------------------------------

bool System::IsGamePadButtonPressed(u32 button) const
{
	const bool currState = (mCurrGamePadState.rgbButtons[button] & 0x80) != 0;
	const bool prevState = (mPrevGamePadState.rgbButtons[button] & 0x80) != 0;
	return !prevState && currState;
}
//----------------------------------------------------------------------------------------------------

bool System::IsDPadUp() const
{
	const bool hasGamePad = (mpGamePadDevice != nullptr);
	return hasGamePad && (mCurrGamePadState.rgdwPOV[0] == 0);
}

//----------------------------------------------------------------------------------------------------

bool System::IsDPadDown() const
{
	return (mCurrGamePadState.rgdwPOV[0] == 18000);
}

//----------------------------------------------------------------------------------------------------

bool System::IsDPadLeft() const
{
	return (mCurrGamePadState.rgdwPOV[0] == 27000);
}

//----------------------------------------------------------------------------------------------------

bool System::IsDPadRight() const
{
	return (mCurrGamePadState.rgdwPOV[0] == 9000);
}

//----------------------------------------------------------------------------------------------------

float System::GetLeftAnalogX() const
{
	return (mCurrGamePadState.lX / 32767.5f) - 1.0f;
}

//----------------------------------------------------------------------------------------------------

float System::GetLeftAnalogY() const
{
	return -(mCurrGamePadState.lY / 32767.5f) + 1.0f;
}

//----------------------------------------------------------------------------------------------------

float System::GetRightAnalogX() const
{
	return (mCurrGamePadState.lZ / 32767.5f) - 1.0f;
}

//----------------------------------------------------------------------------------------------------

float System::GetRightAnalogY() const
{
	return -(mCurrGamePadState.lRz / 32767.5f) + 1.0f;
}

//----------------------------------------------------------------------------------------------------

void System::UpdateKeyboard()
{
	// Store the previous keyboard state
	memcpy(mPrevKeyBuffer, mCurrKeyBuffer, kKeyBufferSize);

	// Get keyboard state
	static bool sWriteToLog = true;
	HRESULT hr = mpKeyboardDevice->GetDeviceState(kKeyBufferSize, (void*)mCurrKeyBuffer);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			if (sWriteToLog)
			{
				//LOG("[System] Keyboard device is lost.");
				sWriteToLog = false;
			}

			// Try to acquire keyboard device again
			mpKeyboardDevice->Acquire();
		}
		else
		{
			Assert(false, "[System] Failed to get keyboard state.");
			return;
		}
	}
	else
	{
		// Reset flag
		sWriteToLog = true;
	}
}

//----------------------------------------------------------------------------------------------------

void System::UpdateMouse()
{
	// Store the previous mouse state
	memcpy(&mPrevMouseState, &mCurrMouseState, sizeof(DIMOUSESTATE));

	// Get mouse state
	static bool sWriteToLog = true;
	HRESULT hr = mpMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void*)&mCurrMouseState);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			if (sWriteToLog)
			{
				//LOG("[System] Mouse device is lost.");
				sWriteToLog = false;
			}

			// Try to acquire mouse device again
			mpMouseDevice->Acquire();
		}
		else
		{
			Assert(false, "[System] Failed to get mouse state.");
			return;
		}
	}
	else
	{
		// Reset flag
		sWriteToLog = true;

		// Update mouse position
		mMouseX += mCurrMouseState.lX;
		mMouseY += mCurrMouseState.lY;

		// Check bound
		if (mMouseX < 0)
			mMouseX = 0;
		if (mMouseX>= mScreenWidth)
			mMouseX = mScreenWidth - 1;
		if (mMouseY < 0)
			mMouseY = 0;
		if (mMouseY>= mScreenHeight)
			mMouseY = mScreenHeight - 1;
	}
}

//----------------------------------------------------------------------------------------------------

void System::UpdateGamePad()
{
	// Store the previous game pad state
	memcpy(&mPrevGamePadState, &mCurrGamePadState, sizeof(DIJOYSTATE));

	// Poll the game pad device
	static bool sWriteToLog = true;
	HRESULT hr = mpGamePadDevice->Poll();
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			if (sWriteToLog)
			{
				//LOG("[System] Game pad device is lost.");
				sWriteToLog = false;
			}

			// Try to acquire game pad device again
			mpGamePadDevice->Acquire();
		}
		else
		{
			//LOG("[System] Failed to get game pad state.");
			return;
		}
	}
	else
	{
		// Reset flag
		sWriteToLog = true;
	}

	// Get game pad state
	hr = mpGamePadDevice->GetDeviceState(sizeof(DIJOYSTATE), (void*)&mCurrGamePadState);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			if (sWriteToLog)
			{
				//LOG("[System] Game pad device is lost.");
				sWriteToLog = false;
			}

			// Try to acquire game pad device again
			mpGamePadDevice->Acquire();
		}
		else
		{
			//LOG("[System] Failed to get game pad state.");
			return;
		}
	}
	else
	{
		// Reset flag
		sWriteToLog = true;
	}
}