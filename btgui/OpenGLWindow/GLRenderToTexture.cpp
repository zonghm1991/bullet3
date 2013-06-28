
///See http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/

#include "GLRenderToTexture.h"
#include "Bullet3Common/b3Scalar.h" // for b3Assert
GLRenderToTexture::GLRenderToTexture()
:m_framebufferName(0)
{
}
	
void GLRenderToTexture::init(int width, int height, GLuint textureId, int renderTextureType)
{
	m_renderTextureType = renderTextureType;

	glGenFramebuffers(1, &m_framebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferName);
	
	switch (m_renderTextureType)
	{
	case RENDERTEXTURE_COLOR:
		{
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);
			break;
		}
		case RENDERTEXTURE_DEPTH:
		{
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureId, 0);
			break;
		}
		default:
			{
			b3Assert(0);
			}
	};
	

	// The depth buffer
	glGenRenderbuffers(1, &m_depthrenderbuffer);
	
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthrenderbuffer);

	glBindFramebuffer( GL_FRAMEBUFFER, 0 );


}

bool GLRenderToTexture::enable()
{
	bool status = false;

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferName);

	
	switch (m_renderTextureType)
	{
	case RENDERTEXTURE_COLOR:
		{
			// Set the list of draw buffers.
			GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0,0};
			glDrawBuffers(1, drawBuffers);
			break;
		}
		case RENDERTEXTURE_DEPTH:
		{
			glDrawBuffer(GL_NONE);
			break;
		}
		default:
			{
			b3Assert(0);
			}
	};


	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		status = true;
	}


	return status;

}

void GLRenderToTexture::disable()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}
	
GLRenderToTexture::~GLRenderToTexture()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	if (m_depthrenderbuffer)
	{
		glDeleteRenderbuffers(1,&m_depthrenderbuffer);
	}


	if( m_framebufferName)
	{ 
		glDeleteFramebuffers(1, &m_framebufferName);
	}
}

