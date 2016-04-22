#ifndef IncludedEncodingH
#define IncludedEncodingH

//====================================================================================================
// Filename:	Encoding.h
// Created by:	Jarrod MacKay
// Description:	Contains type conversion classes
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <Core.h>

class Base64Coder
{
public:

	Base64Coder()
	{
	}

	~Base64Coder()
	{
	}

	void Encode(const u8* p_Binary, const u32 p_InSize, std::string& p_Text)
	{
		u32 outSize = (4 * (p_InSize + 2)) / 3;
		p_Text.clear();
		u32 fourBytes = 0;

		//recursion
		if(p_InSize == 0)
		{
			return;
		}
		else if(p_InSize == 1)
		{
			//fill 3rd byte of u32 and pad output
			fourBytes |= (p_Binary[0] << 16);

			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 18) & 0x3F)));
			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 12) & 0x3F)));
			p_Text.push_back('=');
			p_Text.push_back('=');
			return;
		}
		else if(p_InSize == 2)
		{
			//fill 3rd and 2nd byte of u32 and pad output
			fourBytes |= (p_Binary[0] << 16);
			fourBytes |= (p_Binary[1] << 8);

			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 18) & 0x3F)));
			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 12) & 0x3F)));
			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 6) & 0x3F)));
			p_Text.push_back('=');
			return;
		}
		else
		{
			//fill first 3 bytes of u32
			fourBytes |= (p_Binary[0] << 16);
			fourBytes |= (p_Binary[1] << 8);
			fourBytes |= (p_Binary[2] << 0);

			//get subproblem solution
			std::string subString;
			u32 subStringLength = 0;
			Encode(&p_Binary[3], p_InSize - 3, subString);

			//combine
			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 18) & 0x3F)));
			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 12) & 0x3F)));
			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 6) & 0x3F)));
			p_Text.push_back(IndexToChar(static_cast<u8>((fourBytes >> 0) & 0x3F)));
			p_Text.append(subString);
		}
	}


	void Decode(const char* p_Text, const u32 p_InSize, std::vector<u8>& p_Binary)
	{
		//u32 outSize = (3 * (p_InSize + 3)) / 4;
		//p_Binary.clear();
		//u32 fourBytes = 0;
		//

		////recursion
		//if(p_InSize == 0)
		//{
		//	return;
		//}
		//else
		//{
		//	//fill 3 bytes of u32
		//	fourBytes |= (p_Text[0] << 18);
		//	fourBytes |= (p_Text[1] << 12);
		//	fourBytes |= (p_Text[2] << 6);
		//	fourBytes |= (p_Text[3] << 0);

		//	//get subproblem solution
		//	std::vector<u8> subVector;
		//	u32 subStringLength = 0;
		//	Decode(&p_Text[4], p_InSize - 4, subVector);

		//	//combine
		//	p_Binary.push_back(CharToIndex(static_cast<char>((fourBytes >> 16) & 0xFF)));
		//	p_Binary.push_back(CharToIndex(static_cast<char>((fourBytes >> 8) & 0xFF)));
		//	p_Binary.push_back(CharToIndex(static_cast<char>((fourBytes >> 0) & 0xFF)));
		//	p_Binary.insert(p_Binary.end(), subVector.begin(), subVector.end());
		//}
	}

private:

	const char IndexToChar(const u8 p_Index)
	{
		//0-25 <=> A-Z
		//26-51 <=> a-z
		//52-62 <=> 0-9
		//62 <=> +
		//63 <=> /
		if(0 <= p_Index && p_Index <= 25)
		{
			return static_cast<char>('A' + p_Index);
		}
		if(26 <= p_Index && p_Index <= 51)
		{
			return static_cast<char>('a' + (p_Index - 26));
		}
		if(52 <= p_Index && p_Index <= 62)
		{
			return static_cast<char>('0' + (p_Index - 52));
		}
		if(62 == p_Index)
		{
			return '+';
		}
		if(63 == p_Index)
		{
			return '/';
		}
		return 0;
	}

	const u8 CharToIndex(const char p_Char)
	{
		//0-25 <=> A-Z
		//26-51 <=> a-z
		//52-62 <=> 0-9
		//62 <=> +
		//63 <=> /
		if('A' <= p_Char && p_Char <= 'Z')
		{
			return static_cast<u8>(p_Char - 'A');
		}
		if('a' <= p_Char && p_Char <= 'z')
		{
			return static_cast<u8>((p_Char - 'a') + 26);
		}
		if('0' <= p_Char && p_Char <= '9')
		{
			return static_cast<u8>((p_Char - '0') + 52);
		}
		if('+' == p_Char)
		{
			return 62;
		}
		if('/' == p_Char)
		{
			return 63;
		}
		return 0;
	}
};

#endif // #ifndef IncludedEncodingH