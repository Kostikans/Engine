#pragma once

#include "stbi_image.h"
#include <GL/glew.h>

namespace Engine {
	class Texturer
	{
	private:
		GLuint textureID;
		
	public:
		Texturer(const char *fileName);
		void Bind();
		void UnBind();
	};
}