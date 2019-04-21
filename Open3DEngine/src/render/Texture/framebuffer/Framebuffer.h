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
		GLuint depthMapFBOID;
		GLuint depthMapID;
	public:
		FrameBuffer();
		void Bind();
		void UnBind();
		void Bindtex();
		void MultiSample();
	};
}