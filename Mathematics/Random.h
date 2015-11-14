#ifndef IncludedMathRandomH
#define IncludedMathMatrixH

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

		static u32 m_Step;
		
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

			//burn in and seed 1024bit generator
			u64 generated = 0;
			for (u32 i = 0; i < 160; ++i)
			{
				 generated = Unsigned64_64();
				 if (i % 10 == 0)
				 {
					 m_Seed1024[i / 10] = generated;
				 }
			}

			m_Step = static_cast<u32>(Unsigned64_64() & 15);

			for (u32 i = 0; i < 100; ++i)
			{
				Unsigned64_1024();
			}
		}

		static u32 GetInteger(const u32 p_Minimum, const u32 p_Maximum)
		{
			Assert(p_Minimum < p_Maximum, "Invalid range!");
			u32 range = (p_Maximum - p_Minimum);
			return (static_cast<u32>(Unsigned64_1024()) % range) + p_Minimum; 
		}

	private:

		NonInstantiable(Random);

		static u64 Unsigned64_64()
		{
			m_Seed64 ^= m_Seed64 >> 12;
			m_Seed64 ^= m_Seed64 << 25;
			m_Seed64 ^= m_Seed64 >> 27;
			return m_Seed64 * u64(2685821657736338717);
		}

		static u64 Unsigned64_1024()
		{
			u64 s0 = m_Seed1024[m_Step];
			m_Step = (m_Step + 1) & 15;
			u64 s1 = m_Seed1024[m_Step];
			s1 ^= s1 << 31;
			s1 ^= s1 >> 11;
			s0 ^= s0 >> 30;
			return (m_Seed1024[m_Step] = s0 ^ s1) * u64(1181783497276652981);
		}
	};
} // namespace Mathematics

#endif //#ifndef IncludedMathMatrixH