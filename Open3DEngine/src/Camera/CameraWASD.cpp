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
		FOV = 45.0f;
	}

	void CameraWASD::draw(Shader  &shader)
	{
		shader.SetUniformMat4f("view", viewMatrix);
	}

	void CameraWASD::rotate(const glm::quat & r)
	{
		rotateQuat = r * rotateQuat;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = glm::mat4_cast(rotateQuat) * viewMatrix;
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}

	void CameraWASD::translate(const glm::vec3 & t)
	{
		transormation += t;
		viewMatrix = glm::mat4x4(1.0f);
		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = glm::mat4_cast(rotateQuat) * viewMatrix;
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}

	void CameraWASD::scaleObject(const glm::vec3 & s)
	{
		scale *= s;
		viewMatrix = glm::mat4x4(1.0f);
		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = glm::mat4_cast(rotateQuat) * viewMatrix;
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}
	void CameraWASD::setGlobalTransform(const glm::mat4x4 & g)
	{
		globalTransform = g;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = glm::mat4_cast(rotateQuat) * viewMatrix;
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
		rotateQuat = r2 * rotateQuat * r1;
		viewMatrix = glm::mat4x4(1.0f);
		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = glm::mat4_cast(rotateQuat) * viewMatrix;
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));

	}
	void CameraWASD::zoom(double y0offset)
	{
		if (FOV >= 1.0f && FOV <= 45.0f)
			FOV -= y0offset;
		if (FOV <= 1.0f)
			FOV = 1.0f;
		if (FOV >= 45.0f)
			FOV = 45.0f;
	}
	glm::mat4x4& CameraWASD::GetViewMatrix()
	{
		return viewMatrix;
	}
	glm::vec3 CameraWASD::GetDirection()
	{	     
		return glm::inverse(glm::mat4_cast(rotateQuat))[2];
	}
	glm::vec3 CameraWASD::GetUp()
	{
		return glm::inverse(glm::mat4_cast(rotateQuat))[1];
	}
	float CameraWASD::getZoom()
	{
		return FOV;
	}
}
