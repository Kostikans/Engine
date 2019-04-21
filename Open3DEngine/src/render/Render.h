#pragma once
#include "src/item/SimpleObject.h"
#include "src/render/Shader/Shader.h"
#include <vector>
#include "src/Window/Window.h"
namespace Engine
{
	class Render
	{
	private:
		std::vector<SimpleObject> objects;

	public:
		void draw(Shader &shader);
	};
}