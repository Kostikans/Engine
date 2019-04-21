#pragma once

#include <GL/glew.h>
#include "stbi_image.h"


namespace Engine {
	class Texturer
	{
	private:
		GLuint textureID;
	protected:
		int width, height;
	public:
		Texturer();
		Texturer(const char *fileName);
		void Bind();
		void UnBind();
	};
}