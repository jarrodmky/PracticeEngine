//===========================================================================
// Filename:	Camera.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Camera.h"

using namespace Mathematics;
using namespace Visualization;

//===========================================================================
// Meta
//===========================================================================

MetaClassBegin(Camera)
MetaFieldBegin
MetaField(Transform, "Transform"),
MetaField(m_HorizontalFOV, "FOV"),
MetaField(m_NearPlane, "NearPlane"),
MetaField(m_FarPlane, "FarPlane")
MetaFieldEnd
MetaClassEnd

//===========================================================================
// Definitions
//===========================================================================

Camera::Camera()
	: Transform()
	, m_HorizontalFOV()
	, m_NearPlane()
	, m_FarPlane()
{}

//---------------------------------------------------------------------------

void Camera::Calibrate(const Vector3& p_Position
	, const Vector3& p_Interest
	, const f32 p_FarZ
	, const f32 p_FOV
	, bool p_ManuallySetNear
	, const f32 p_NearZ)
{
	Assert(Zero < p_FOV && p_FOV < Pi, "FOV not in (0, Pi), focal length is infinite. ");
	Transform.SetOrientation((p_Interest - p_Position).Direction());
	Transform.SetPosition(p_Position);
	m_HorizontalFOV = p_FOV;
	m_FarPlane = p_FarZ;

	m_NearPlane = (!p_ManuallySetNear) ? (GetFocalLength()) : (p_NearZ);
}

//---------------------------------------------------------------------------

void Camera::SetInterest(const Vector3& p_Interest)
{
	Transform.SetOrientation(p_Interest - Transform.GetForward(), Transform.GetUp());
}

//---------------------------------------------------------------------------

void Camera::SetFocus(const f32 p_FocalLength)
{
	m_HorizontalFOV = 2.0f * std::atan(Inverse(p_FocalLength));
}

//---------------------------------------------------------------------------

Matrix44 Camera::GetViewToWorldTransform() const
{
	return Transform.GetLocalToWorld();
}

//---------------------------------------------------------------------------

Matrix44 Camera::GetWorldToViewTransform() const
{
	return Transform.GetWorldToLocal();
}

//---------------------------------------------------------------------------

Matrix44 Camera::GetWorldToPerspectiveTransform(const f32 p_AspectRatio) const
{
	return GetViewToPerspectiveTransform(p_AspectRatio) * GetWorldToViewTransform();
}

//---------------------------------------------------------------------------

Matrix44 Camera::GetWorldToOrthogonalTransform(const u32 p_ScreenWidth, const u32 p_ScreenHeight) const
{
	return GetViewToOrthogonalTransform(p_ScreenWidth, p_ScreenHeight) * GetWorldToViewTransform();
}

//---------------------------------------------------------------------------

Matrix44 Camera::GetViewToPerspectiveTransform(const f32 p_AspectRatio) const
{
	return MakePerspectiveView(GetHorizontalFOV(), p_AspectRatio, m_FarPlane, m_NearPlane) * MakeReflectionAboutXY();
}

//---------------------------------------------------------------------------

Matrix44 Camera::GetViewToOrthogonalTransform(const u32 p_ScreenWidth, const u32 p_ScreenHeight) const
{
	return MakeOrthographicView(p_ScreenWidth, p_ScreenHeight, m_FarPlane, m_NearPlane) * MakeReflectionAboutXY();
}

//---------------------------------------------------------------------------

scalar Camera::GetFocalLength() const
{
	return Inverse(std::tan(m_HorizontalFOV * 0.5f));
}

//---------------------------------------------------------------------------

scalar Camera::GetHorizontalFOV() const
{
	return m_HorizontalFOV;
}

//---------------------------------------------------------------------------

Ray3 Camera::ScreenPointToRay(const Mathematics::IntVector2& p_ScreenCoords
										  , const Mathematics::UintVector2& p_ScreenLimits)
{
	const f32 aspect = (f32)p_ScreenLimits(0) / (f32)p_ScreenLimits(1);
	const Vector2 halfLimits = MakeVector((f32)p_ScreenLimits(0), (f32)p_ScreenLimits(1));
	const f32 tanFOV = std::tan(m_HorizontalFOV * 0.5f);
	const Vector2 delta = tanFOV * MakeVector(((f32)p_ScreenCoords(0) / halfLimits(0) - 1.0f) * aspect
											  , (1.0f - (f32)p_ScreenCoords(1) / halfLimits(1)));
	
	Matrix44 invViewMatrix(GetViewToWorldTransform());

	Ray3 ray(MakeProjectedPoint(invViewMatrix * Zero4())
			 , MakeProjectedVector(invViewMatrix * MakeVector(delta(0), delta(1), Unity, Zero).Direction()));
	
	return ray;
}