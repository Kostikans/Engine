#pragma once

#include "stbi_image.h"
#include <GL/glew.h>

namespace Engine {
	class Texture
	{
	private:
		GLuint textureID;
		
	public:
		Texture(const char *fileName);
		void Bind();
		void UnBind();
	};
}