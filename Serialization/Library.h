#ifndef IncludedSeriLibraryH
#define IncludedSeriLibraryH

//====================================================================================================
// Filename:	Library.h
// Created by:	Jarrod MacKay
// Description:	Holds reference counting resources
//====================================================================================================

#include <Abstracts.h>
#include <Mathematics.h>

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace Serialization
{

template<typename t_ResourceType>
class Library
{
	//Definitions
	protected:

	typedef u64 ResourceKey;
	
	typedef std::map<ResourceKey, t_ResourceType*> Manifest;

	//Attributes
	protected:

		std::string m_Path;
		
		Manifest m_Manifest;

	//Operators
	public:

		Library(const char* p_DirectoryPath);

		~Library();

	//Functions
	public:

		t_ResourceType* Borrow(const char* p_Name);
		void Return(t_ResourceType* p_Handle);

	private:

		void Aquire(const char* p_Name);

		//if reference not in container load it ad add two references for myself and the other guy the n return pointer
		//else if in container ad a refereence for the other guy and return;
};

#include "Library.inl"

}

#endif // #ifndef IncludedSeriLibraryH