#ifndef IncludedSeriXmlFileH
#define IncludedSeriXmlFileH

//===========================================================================
// Filename:	XmlFile.h
// Author:		Jarrod MacKay
// Description:	Parses and stores a tree from an xml file
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

class TiXmlNode;
namespace Meta { class Class;}

//===========================================================================
// Definition
//===========================================================================

namespace Serialization
{
		class XmlFile
		{
		public:

			static bool Read(void* p_Instance, const Meta::Class* p_MetaClass, const TiXmlNode* p_Node);
		};


} // namespace Serialization

#endif // #ifndef IncludedSeriXmlFileH