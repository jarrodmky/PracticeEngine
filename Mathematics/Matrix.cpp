#include "Precompiled.h"
#include "Matrix.h"
#include "Point.h"

using namespace Mathematics;

Matrix::Matrix(const Vector p_FirstAxis
						  , const Vector p_SecondAxis
						  , const Vector p_ThirdAxis
						  , const Point p_Origin)
: m_Array()
{
	//first column
	m_Array(0, 0) = p_FirstAxis.x;
	m_Array(1, 0) = p_FirstAxis.y;
	m_Array(2, 0) = p_FirstAxis.z;
	
	//second column
	m_Array(0, 1) = p_SecondAxis.x;
	m_Array(1, 1) = p_SecondAxis.y;
	m_Array(2, 1) = p_SecondAxis.z;

	//third column
	m_Array(0, 2) = p_ThirdAxis.x;
	m_Array(1, 2) = p_ThirdAxis.y;
	m_Array(2, 2) = p_ThirdAxis.z;

	//fourth column
	m_Array(0, 3) = p_Origin.x;
	m_Array(1, 3) = p_Origin.y;
	m_Array(2, 3) = p_Origin.z;
	m_Array(3, 3) = ConstantScalars::Unity;
}	

Matrix::Matrix(
		 const scalar p_r1c1, const scalar p_r1c2, const scalar p_r1c3, const scalar p_r1c4
	   , const scalar p_r2c1, const scalar p_r2c2, const scalar p_r2c3, const scalar p_r2c4
	   , const scalar p_r3c1, const scalar p_r3c2, const scalar p_r3c3, const scalar p_r3c4
	   , const scalar p_r4c1, const scalar p_r4c2, const scalar p_r4c3, const scalar p_r4c4)
: m_Array()
{
	//first column
	m_Array(0, 0) = p_r1c1;
	m_Array(1, 0) = p_r2c1;
	m_Array(2, 0) = p_r3c1;
	m_Array(3, 0) = p_r4c1;
	
	//second column
	m_Array(0, 1) = p_r1c2;
	m_Array(1, 1) = p_r2c2;
	m_Array(2, 1) = p_r3c2;
	m_Array(3, 1) = p_r4c2;

	//third column
	m_Array(0, 2) = p_r1c3;
	m_Array(1, 2) = p_r2c3;
	m_Array(2, 2) = p_r3c3;
	m_Array(3, 2) = p_r4c3;

	//fourth column
	m_Array(0, 3) = p_r1c4;
	m_Array(1, 3) = p_r2c4;
	m_Array(2, 3) = p_r3c4;
	m_Array(3, 3) = p_r4c4;
}