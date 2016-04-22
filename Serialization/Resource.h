#ifndef IncludedSeriResourceH
#define IncludedSeriResourceH

//====================================================================================================
// Filename:	Resource.h
// Created by:	Jarrod MacKay
// Description:	Class for file resources
//====================================================================================================

#include <Core.h>

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace Serialization
{

template <typename t_Type>
class Library;

template <typename t_Type>
class Resource
{
	friend Library<t_Type>;

	//Attributes
	private:
		
		mutable u32 m_ReferenceCount;

	//Operators
	public:

		Resource()
			: m_ReferenceCount(0)
		{}

		virtual ~Resource()
		{
			Assert(m_ReferenceCount == 0, "Still using resource!!");
		}

	//Functions
	public:

		const u32 GetReferenceCount() const
		{
			return m_ReferenceCount;
		}

private:

		void AddReference() const
		{
			++m_ReferenceCount;
		}

		void RemoveReference() const
		{
			--m_ReferenceCount;
		}

		bool Aquire(const std::string& p_Name)
		{
			if(OnAquire(p_Name))
			{
				return true;
			}
			return false;
		}

		void Release()
		{
			Assert(m_ReferenceCount == 0, "No references to released object!");
			//if(m_ReferenceCount == 1)
			//	OnRelease();
		}

	protected:

		virtual bool OnAquire(const std::string& p_Name) = 0;
		virtual void OnRelease() = 0;
};

}

#endif // #ifndef IncludedSeriResourceH