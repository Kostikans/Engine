#include "src/render/Texture/framebuffer/Framebuffer.h"
#include <iostream>
namespace Engine {
	FrameBuffer::FrameBuffer()
	{
		//FrameBuffer
		glGenFramebuffers(1, &framebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
		
	    //textColorBuffer
		glGenTextures(1, &textureColorBufferMultiSampledID);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampledID);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_RGB, 1400, 700, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampledID, 0);

		//rbo
		glGenRenderbuffers(1, &rboID);
		glBindRenderbuffer(GL_RENDERBUFFER, rboID);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 16, GL_DEPTH24_STENCIL8, 1400, 700);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboID);
	
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//intermediate
		glGenFramebuffers(1, &intermediateFBOID);
		glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBOID);

		//screenTexture
		glGenTextures(1, &screenTextureID);
		glBindTexture(GL_TEXTURE_2D, screenTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1400, 700, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTextureID, 0);	

	
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void FrameBuffer::Bind()
	{
		
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	}
	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
	}
	void FrameBuffer::Bindtex()
	{
		glBindTexture(GL_TEXTURE_2D, screenTextureID);
	}
	void FrameBuffer::MultiSample()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebufferID);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBOID);
		glBlitFramebuffer(0, 0, 1400, 700, 0, 0, 1400, 700, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}
	GLuint FrameBuffer::GetTexture()
	{
		return screenTextureID;
	}
}