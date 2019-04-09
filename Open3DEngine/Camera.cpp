#include "Camera.h"
#include <iostream>
namespace Engine
{	
	Camera::Camera()
	{
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		globalTransform = glm::mat4x4(1.0f);
		transormation = glm::vec3(0.0f, 0.0f, 0.0f);
		viewMatrix = glm::mat4x4(1.0f);
		rotateMatrix = glm::quat(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
	}

	void Camera::draw(Shader  &shader)
	{
		shader.SetUniformMat4f("view", viewMatrix);
	}

	void Camera::rotateCamera(const glm::quat & r)
	{
		rotateMatrix = r * rotateMatrix;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateMatrix);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}

	void Camera::translateCamera(const glm::vec3 & t)
	{
		transormation += t;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateMatrix);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}

	void Camera::scaleCamera(const float & s)
	{
		scale *= s;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateMatrix);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}
	void Camera::setGlobalTransform(const glm::mat4x4 & g)
	{
		globalTransform = g;
		viewMatrix = glm::mat4x4(1.0f);

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateMatrix);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}

	void Camera::rotateFromInput(float x0offset, float y0offset)
	{
		
		float diffx = x0offset, diffy = y0offset;
		float angle = glm::length(glm::vec2(diffx, diffy)) / 150.0f;

		std::cout << angle << std::endl;

		glm::vec3 axis = glm::vec3(diffy, diffx, 0.0f);
		std::cout << axis.x << ' ' << axis.y << std::endl;
		glm::quat r = glm::angleAxis(angle, axis);
		rotateMatrix = glm::normalize(r * rotateMatrix);

		viewMatrix = glm::mat4x4(1.0f);
		

		viewMatrix = glm::translate(viewMatrix, transormation);
		viewMatrix = viewMatrix * glm::mat4_cast(rotateMatrix);
		viewMatrix = glm::scale(viewMatrix, scale);
		viewMatrix = viewMatrix * (glm::inverse(globalTransform));
	}
}
