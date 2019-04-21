#pragma once

#include"src/render/Shader/Shader.h"
#include "src/render/Texture/Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"


namespace Engine
{
	class Transformation
	{
	public:
		virtual void draw(Shader &shader) = 0;
		virtual void rotate(const glm::quat &r) = 0;
		virtual void translate(const glm::vec3 &t) = 0;
		virtual void scaleObject(const glm::vec3 & s) = 0;
		virtual void setGlobalTransform(const glm::mat4x4 &g) = 0;
	};
}