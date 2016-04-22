///*	
//	tool_dbexporter.cpp :
//	2015/04/24
//	(C) 2015 Jarrod MacKay
//	Turns csv to JSOn, e.g. tool_dbexporter.exe -in:weapons.csv -out:weapons.json
//*/
#include "Precompiled.h"
//

char filler = '_';
////enumerates the accepted types of tokens
//enum TokenType
//{
//	eNULLTYPE = 0,
//	eSWITCH,
//	eINPUT,
//	eOUTPUT,
//	eCOMMAND
//};
//
////represents a token with a string and a type
//struct Token
//{
//	Token(std::string p_sIntitialString = "", enum TokenType p_eInitialType = eNULLTYPE)
//	{
//		m_sString = p_sIntitialString;
//		m_sType = p_eInitialType;
//	}
//
//	bool operator ==(const Token& p_rRHS) const
//	{
//		return (m_sString.compare(p_rRHS.m_sString) == 0 && m_sType == p_rRHS.m_sType);
//	}
//
//	std::string m_sString;
//	enum TokenType m_sType;
//};
//
////assigns the given token a type based on prefixed symbols
//void assignTokenType(Token& p_Token);
//
///*
//Program entry point.
//*/
//int _tmain(int argc, _TCHAR* argv[])
//{
//
//	dbPrintf("Hello, tool_dbexporter");
//
//	std::string inPath;
//	std::string outPath;
//
//	//convert tokens to C++ strings for convenience
//	Token* currentToken = nullptr;
//	Token* tokens = new Token[argc];
//	int i = 1; //skip the first command line argument (executable directory)
//
//	for (i = 1; i < argc; ++i)
//	{
//		tokens[i] = Token(argv[i]);
//		assignTokenType(tokens[i]);
//
//		//remove the prefix flags and set i/o
//		if (tokens[i].m_sType != eCOMMAND)
//		{
//			tokens[i].m_sString = tokens[i].m_sString.substr(3);
//			if (tokens[i].m_sType == eINPUT)
//			{
//				inPath = tokens[i].m_sString;
//			}
//			else if (tokens[i].m_sType == eOUTPUT)
//			{
//				outPath = tokens[i].m_sString;
//			}
//		}
//	}
//	i = 1;
//
//	//process
//	int numArguments = argc;
//	std::cout << std::endl;
//
//	std::replace(inPath.begin(), inPath.end(), '\\', '/');
//	std::replace(inPath.begin(), inPath.end(), '/', '\\');
//	std::replace(outPath.begin(), outPath.end(), '\\', '/');
//	std::replace(outPath.begin(), outPath.end(), '/', '\\');
//
//	AIDebugMessageV("in: %s out: %s", inPath.c_str(), outPath.c_str());
//		CSV::CsvFile inFile(inPath);
//		JSON::JsonFile outFile(outPath);
//
//		FileConverter converter;
//
//		if (inFile.readInText())
//		{
//			outFile = converter.convertToJson(inFile, outFile);
//			outFile.writeOutText();
//		}
//
//
//	return 0;
//}
//
//
//
////HELPER FUNCTION DEFINITIONS
//
//void assignTokenType(Token& p_Token)
//{
//	std::string tokenString = p_Token.m_sString;
//	if (tokenString[0] == '[' && tokenString[2] == ']')
//	{
//		if (tokenString[1] == 'S')
//		{
//			p_Token.m_sType = eSWITCH;
//		}
//		else if (tokenString[1] == 'I')
//		{
//			p_Token.m_sType = eINPUT;
//		}
//		else if (tokenString[1] == 'O')
//		{
//			p_Token.m_sType = eOUTPUT;
//		}
//	}
//	else
//	{
//		p_Token.m_sType = eCOMMAND;
//	}
//}