#ifndef IncludedVisuSceneH
#define IncludedVisuSceneH

#include <Mathematics.h>
#include "Material.h"

namespace Visualization
{

class Scene
{

	//Operations
	public:

		Scene();
		~Scene();
		

	//Methods
	public:

	//Attributes
	private:

		struct SceneObject
		{
			Mathematics::Frame& m_Frame;
			Material& m_Material;
		};
};

}

#endif // #ifndef IncludedVisuSceneH