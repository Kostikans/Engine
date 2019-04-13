#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "src/render/Shader/Shader.h"


namespace Engine
{
	class Camera
	{
	private: 

		glm::vec3  scale;
		glm::vec3 transormation;
		glm::mat4x4 viewMatrix;
		glm::mat4x4 globalTransform;
		glm::quat rotateMatrix;
		
		
	public:

		Camera();
		void draw(Shader &shader);
		void rotateCamera(const glm::quat &r);
		void translateCamera(const glm::vec3 &t);
		void scaleCamera(const float &s);
		void setGlobalTransform(const glm::mat4x4 &g);
		void rotateFromInput(float x0oofet,float y0offset);
		glm::mat4x4& GetViewMatrix();
		
	};
}