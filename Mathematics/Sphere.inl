//===========================================================================
// Filename:	Sphere.inl
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Class Definitions
//===========================================================================

namespace Mathematics
{
	Sphere::Sphere(const scalar& p_X
		 , const scalar& p_Y
		 , const scalar& p_Z
		 , const scalar& p_Radius)
	: Centre(Point(p_X, p_Y, p_Z))
	, Radius(p_Radius)
	{}

	//---------------------------------------------------------------------------

	Sphere::Sphere(const Point& p_Centre, const scalar& p_Radius)
	: Centre(p_Centre)
	, Radius(p_Radius)
	{}
}