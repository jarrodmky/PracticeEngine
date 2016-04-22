#ifndef IncludedAbstObservableH
#define IncludedAbstObservableH

//===========================================================================
// Filename:	Observer.h
// Author:		Jarrod MacKay
// Description:	
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>

//===========================================================================
// Templates
//===========================================================================

namespace Abstracts
{
	class Observer
	{
		//Methods
	public:

		virtual ~Observer() {}

		virtual void Notify() = 0;
	};

	template<typename t_Observer>
	class Observable
	{
	//Methods
	public:

		virtual ~Observable() 
		{}

		virtual Observable()
			: m_Observers(nullptr)
		{}

		void ShowTo(t_Observer* p_Observer)
		{
			m_Observers.push_back(p_Observer);
		}

		void HideFrom(t_Observer* p_Observer)
		{
			auto I = std::find(m_Observers.begin(), m_Observers.end(), p_Observer);
			m_Observers.erase(I);
		}

		void NotifyObservers()
		{
			for (auto observer : m_Observers)
			{
				observer->Notify();
			}
		}

	//Attributes
	private:

		std::vector<t_Observer*> m_Observers;
	};

} // namespace Abstracts
#endif // #ifndef IncludedAbstObservableH