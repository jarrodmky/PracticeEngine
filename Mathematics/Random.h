#ifndef IncludedMathRandomH
#define IncludedMathRandomH

//===========================================================================
// Filename:	Random.h
// Author:		Jarrod MacKay
// Description:	Singleton class; methods and private static data for
//				random number generation.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "MathBase.h"

#define Modulo16(x) static_cast<u8>((x) & 15)

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class Random
	{
	//Attributes
	private:

		static u64 m_Seed64;

		static u64 m_Seed1024[16];

		static u8 m_Step;

		static bool m_Initialized;

		static const u32 m_BurnsPerNumber = 30;//>= 16
		
	//Methods
	public:

		static void Initialize()
		{
			//Seed the 64bit generator
			SYSTEM_INFO sysInfoSeed;
			GetNativeSystemInfo(&sysInfoSeed);
			m_Seed64 = sysInfoSeed.dwOemId + u32(-4);
			m_Seed64 <<= 32;
			m_Seed64 |= (timeGetTime() + u32());

			//burn in
			for (u32 i = 0; i < m_BurnsPerNumber; ++i)
			{
				Unsigned64_64();
			} 

			//seed 1024bit generator
			const u64 burnsPer64Bit = m_BurnsPerNumber * m_BurnsPerNumber;
			for (u64 i = 0; i < burnsPer64Bit; ++i)
			{
				u64 gen = Unsigned64_64();
				Assert(Modulo16(gen) == (gen % 16), "PLEASE REMOVE ME!");
				m_Seed1024[Modulo16(gen)] = gen;
			}

			m_Step = Modulo16(Unsigned64_64());

			for (u32 i = 0; i < m_BurnsPerNumber; ++i)
			{
				Unsigned64_1024();
			}

			m_Initialized = true;
		}

		//random positive integer in [min, max]
		static u32 Integer(const u32 p_Minimum, const u32 p_Maximum)
		{
			Assert(m_Initialized, "Randomizer is not initialized!!");
			Assert(p_Minimum < p_Maximum, "Invalid range!");
			u32 range = (p_Maximum - p_Minimum);
			return (static_cast<u32>(Unsigned64_1024()) % (range + 1)) + p_Minimum; 
		}

		//random element of [0,1]
		static f32 Unit()
		{
			Assert(m_Initialized, "Randomizer is not initialized!!");
			f32 unit = AbsoluteValue(static_cast<f32>(Unsigned64_1024())) / static_cast<f32>(MaxU64);
			Assert(unit >= Zero && unit <= Unity, "Not on [0,1]");
			return unit;
		}

		//random floating point number in [min,max]
		static f32 Float(const f32 p_Minimum, const f32 p_Maximum)
		{
			Assert(p_Minimum <= p_Maximum, "Invalid range!");
			f32 range = (p_Maximum - p_Minimum);
			return (Unit() * range) + p_Minimum;
		}


	private:

		//xorshift 64 bit
		static u64 Unsigned64_64()
		{
			m_Seed64 ^= m_Seed64 >> 12;
			m_Seed64 ^= m_Seed64 << 25;
			m_Seed64 ^= m_Seed64 >> 27;
			return m_Seed64 * u64(2685821657736338717);
		}

		//xorshift 1024 bit
		static u64 Unsigned64_1024()
		{
			u64 s0 = m_Seed1024[m_Step];
			m_Step = Modulo16(m_Step + 1);
			u64 s1 = m_Seed1024[m_Step];
			s1 ^= s1 << 31;
			s1 ^= s1 >> 11;
			s0 ^= s0 >> 30;
			return (m_Seed1024[m_Step] = s0 ^ s1) * u64(1181783497276652981);
		}
	};	
	
	inline const u32 MakeRandomInteger(const u32 p_Min, const u32 p_Max)
	{
		return Random::Integer(p_Min, p_Max);
	}

	inline const scalar MakeRandomScalar(const scalar p_Min, const scalar p_Max)
	{
		return Random::Float(p_Min, p_Max);
	}

} // namespace Mathematics

#undef Divide1024By64
#undef Modulo16

#endif //#ifndef IncludedMathRandomH