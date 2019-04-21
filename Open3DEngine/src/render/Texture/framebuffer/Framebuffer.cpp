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
		glBindTexture(GL_TEXTURE_2D, screenTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1400, 700, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTextureID, 0);	

		//depth map
		glGenTextures(1, &depthMapID);
		glBindTexture(GL_TEXTURE_2D, depthMapID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//shadow map
		glGenFramebuffers(1, &depthMapFBOID);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBOID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapID, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void FrameBuffer::Bind()
	{
		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	}
	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
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
}