#ifndef IncludedCoreTypesH
#define IncludedCoreTypesH

//===========================================================================
// Filename:	Types.h
// Author:		Jarrod MacKay
// Description:	Definitions for standard data types.
//===========================================================================

//===========================================================================
// Typedefs
//===========================================================================

//signed integral
typedef char				s8;
typedef short				s16;
typedef int					s32;
typedef __int64				s64;

//unsigned integral
typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned __int64	u64;

//floating point
typedef float				f32;
typedef double				f64;

//#include <dvec.h>
//
//typedef F32vec4             v4f32;
//typedef F64vec2				v2f64;





union FourBytes
{
	f32 F32;
	u32 U32;
	s32 S32;
	u16 U16[2];
	s16 S16[2];
	u8 U8[4];
	s8 S8[4];
};

inline bool BigEndian()
{
	FourBytes test;
	test.U32 = 1;
	return test.U8[3] == 1;
}

inline bool LittleEndian()
{
	FourBytes test;
	test.U32 = 1;
	return test.U8[0] == 1;
}



#endif //#ifndef IncludedCoreTypesH