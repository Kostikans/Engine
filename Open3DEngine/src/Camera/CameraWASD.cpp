#include "CameraWASD.h"
#include <iostream>

namespace Engine
{
	CameraWASD::CameraWASD()
	{
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		globalTransform = glm::mat4x4(1.0f);
		transormation = glm::vec3(0.0f, 0.0f, 0.0f);
		viewMatrix = glm::mat4x4(1.0f);
		rotateQuat = glm::quat(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
	}

	void CameraWASD::draw(Shader  &shader)
	{
		shader.SetUniformMat4f("view", viewMatrix);
	}

	void CameraWASD::rotateCamera(const glm::quat & r)
	{
		rotateQuat = r * rotateQuat;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateQuat);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}

	void CameraWASD::translateCamera(const glm::vec3 & t)
	{
		transormation += t;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix *  glm::mat4_cast(rotateQuat);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}

	void CameraWASD::scaleCamera(const float & s)
	{
		scale *= s;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateQuat);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}
	void CameraWASD::setGlobalTransform(const glm::mat4x4 & g)
	{
		globalTransform = g;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateQuat);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));

	}

	void CameraWASD::rotateFromInput(float x0offset, float y0offset)
	{


		float yaw = 0 , pitch = 0;
		yaw += x0offset/5.0f;
		pitch += y0offset/5.0f;	
		glm::quat r1 = glm::angleAxis(glm::radians(yaw), glm::vec3(0.0f,1.0f,0.0f));
		glm::quat r2 = glm::angleAxis(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
		rotateQuat = glm::normalize(r2 * rotateQuat * r1);
		glm::vec3 dir(0.0f, 0.0f, 0.0f);
		glm::vec3 up(0.0f, 0.0f, 0.0f);
		viewMatrix = glm::mat4x4(1.0f);
		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateQuat);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));

	}
	glm::mat4x4& CameraWASD::GetViewMatrix()
	{
		return viewMatrix;
	}
	glm::vec3 CameraWASD::GetDirection()
	{
		    float x = 2 * (rotateQuat.x*rotateQuat.z + rotateQuat.w * rotateQuat.y);
			float y = 2 * (rotateQuat.y*rotateQuat.z - rotateQuat.w * rotateQuat.x);
			float z = 1 - 2 * (rotateQuat.x*rotateQuat.x + rotateQuat.y * rotateQuat.y);
			return glm::vec3(x, y, z);
	}
}
