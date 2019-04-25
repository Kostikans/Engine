#pragma once
#include <GL/glew.h>
#include "src/render/Texture/Texture.h"

namespace Engine
{
	class DepthBuffer
	{
	private:
	
		GLuint depthMapFBOID;
		GLuint depthMapID;
	public:
		DepthBuffer();
		void Bind();
		void UnBind();
		GLuint GetMapID();
	};
}
