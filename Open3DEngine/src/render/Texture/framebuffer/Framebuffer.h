#pragma once
#include <GL/glew.h>
#include "src/render/Texture/Texture.h"

namespace Engine
{
	class FrameBuffer 
	{
	private:
		GLuint rboID;
		GLuint textureColorBufferMultiSampledID;
		GLuint framebufferID;
		GLuint intermediateFBOID;
		GLuint screenTextureID;

	public:
		FrameBuffer();
		void Bind();
		void UnBind();
		void Bindtex();
		void MultiSample();
		GLuint GetTexture();
	};
}