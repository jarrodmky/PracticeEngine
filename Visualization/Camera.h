#ifndef IncludedVisuCameraH
#define IncludedVisuCameraH

//===========================================================================
// Filename:	Camera.h
// Author:		Jarrod MacKay
// Description:	Defines a camera that can be placed in the world
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Buffer.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class Camera
	{
		//Operators
	public:

		Camera();

	static const Meta::Class* StaticGetMetaClass();
	virtual const Meta::Class* GetMetaClass() const { return StaticGetMetaClass(); }

		//MetaClassDeclare

		//Methods
	public:

		void Calibrate(const Mathematics::Vector3& p_Position
					   , const Mathematics::Vector3& p_Interest
					   , const f32 p_FarZ
					   , const f32 p_FOV = 45.0f * Mathematics::RadsPerDeg
					   , bool p_ManuallySetNear = false
					   , const f32 p_NearZ = 0.0f);

		//manipulation
		void SetInterest(const Mathematics::Vector3& p_Interest);

		void SetFocus(const f32 p_FocalLength);

		//Transforms
		Mathematics::Matrix44 GetViewToWorldTransform() const;

		Mathematics::Matrix44 GetWorldToViewTransform() const;

		Mathematics::Matrix44 GetViewToPerspectiveTransform(const f32 p_AspectRatio) const;

		Mathematics::Matrix44 GetViewToOrthogonalTransform(const u32 p_ScreenWidth, const u32 p_ScreenHeight) const;

		Mathematics::Matrix44 GetWorldToPerspectiveTransform(const f32 p_AspectRatio) const;

		Mathematics::Matrix44 GetWorldToOrthogonalTransform(const u32 p_ScreenWidth, const u32 p_ScreenHeight) const;

		//camera
		inline Mathematics::scalar GetFocalLength() const;

		inline Mathematics::scalar GetAspectRatio() const;

		inline Mathematics::scalar GetHorizontalFOV() const;

		//ray cast
		inline Mathematics::Ray3 ScreenPointToRay(const Mathematics::IntVector2& p_ScreenCoords
												  , const Mathematics::UintVector2& p_ScreenLimits);

		//Attributes
	public:

		//extrinsic properties
		Mathematics::Frame Transform;

	private:

		//intrinsic properties
		f32 m_HorizontalFOV;

		f32 m_NearPlane;

		f32 m_FarPlane;
	};
}

#endif // #ifndef IncludedVisuCameraH