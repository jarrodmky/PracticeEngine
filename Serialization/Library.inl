//====================================================================================================
// Filename:	Library.inl
// Created by:	Jarrod MacKay
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

//====================================================================================================
// Class Definitions
//====================================================================================================

template <typename t_ResourceType>
Library<t_ResourceType>::Library(const char* p_DirectoryPath)
: m_Path(p_DirectoryPath)
, m_Manifest()
{

}

//----------------------------------------------------------------------------------------------------

template <typename t_ResourceType>
Library<t_ResourceType>::~Library()
{
	//check for no ownership!
	Assert(m_Manifest.empty(), "Items still allocated!");
	m_Manifest.clear();
}

//----------------------------------------------------------------------------------------------------

template <typename t_ResourceType>
t_ResourceType* Library<t_ResourceType>::Borrow(const char* p_Name)
{
	ResourceKey key(HashStringTo64bitInteger(p_Name));
	t_ResourceType* handle(nullptr);

	if(m_Manifest.find(key) == m_Manifest.end())
	{
		//key not found
		handle = new t_ResourceType();
		handle->AddReference();
		handle->AddReference();
		m_Manifest[key] = handle;
	}
	else
	{
		//key found
		handle = m_Manifest[key];
		handle->AddReference();
	}

	Assert(handle, "Could not aquire resource!");

	return handle;
}

//----------------------------------------------------------------------------------------------------

template <typename t_ResourceType>
void Library<t_ResourceType>::Return(t_ResourceType* p_Handle)
{

}