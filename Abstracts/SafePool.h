#ifndef IncludedAbstSafePoolH
#define IncludedAbstSafePoolH

//===========================================================================
// Filename:	SafePool.h
// Author:		Jarrod MacKay
// Description:	Provides small block allocators for safe dynamic memory
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "DynamicArray.h"
#include "Pool.h"

//===========================================================================
// Classes
//===========================================================================

namespace Abstracts
{
	template <typename t_Type>
	class SafePool;

	//==========
	// Handle
	//==========

	template <typename t_Type>
	class Handle
	{
		friend SafePool<t_Type>;

		//Attributes
	private:

		SafePool<t_Type>* m_Pool;

		u32 m_Slot;

		u32 m_AllocationID;

		//Operators
	public:

		Handle()
			: m_Pool(nullptr)
			, m_Slot(-1)
			, m_AllocationID(-1)
		{}

		~Handle()
		{}

		//Functions
	public:

		t_Type* Get()
		{
			return m_Pool->Get(m_Slot, m_AllocationID);
		}

		const bool IsValid() const
		{
			return m_Pool->IsValid(m_Slot, m_AllocationID);
		}
	};

	//==========
	// SafePool
	//==========

	template<typename t_Type>
	class SafePool
	{
		typedef Handle<t_Type> PoolHandle;
		friend PoolHandle;

	//Attributes
	private:

		Pool<t_Type> m_Objects;
		DynamicArray<u32> m_AllocationID;

		//Operators
	public:

		inline explicit SafePool(const u32 p_Elements)
			: m_Objects(p_Elements)
			, m_AllocationID(0, p_Elements)
		{}

		inline virtual ~SafePool() {}

		NonCopyable(SafePool<t_Type>);

		//Methods
	public:

		template<typename... t_Args>
		PoolHandle Allocate(const t_Args&... p_Args)
		{
			u32 filledSlot = m_Objects.Fill(p_Args...);
			PoolHandle newHandle;
			newHandle.m_Pool = this;
			newHandle.m_Slot = filledSlot;
			newHandle.m_AllocationID = m_AllocationID[filledSlot];
			return newHandle;
		}

		void Free(const PoolHandle p_Handle)
		{
			Assert(p_Handle.IsValid(), "Invalid handle!");
			u32 freedSlot = p_Handle.m_Slot;
			++(m_AllocationID[freedSlot]);
			m_Objects.Free(freedSlot);
		}

	private:

		inline t_Type* Get(const u32 p_Slot, const u32 p_AllocationID)
		{
			Assert(IsValid(p_Slot, p_AllocationID), "Invalid identifiers!");
			return m_Objects.Get(p_Slot);
		}
		inline const bool IsValid(const u32 p_Slot, const u32 p_AllocationID) const
		{
			return m_AllocationID[p_Slot] == p_AllocationID;
		}
	};

} // namespace Abstracts

#endif //#ifndef IncludedAbstSafePoolH