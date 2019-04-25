#include <src/render/Render.h>

namespace Engine {
	void Render::draw()
	{
		for (int i = 0; i < objects.size(); ++i)
		{
			
		}
	}
	void Render::add(SimpleObject &object)
	{
		objects.push_back(object);
	}
}