#include "src/Transformation.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Engine
{
	class CameraWASD : public Transformation
	{
	private:

		glm::vec3 scale;
		glm::vec3 transormation;
		glm::mat4x4 viewMatrix;
		glm::mat4x4 globalTransform;
		glm::quat rotateQuat;
		float FOV;

	public:
		CameraWASD();
		void draw(Shader &shader);
		void rotate(const glm::quat &r);
		void translate(const glm::vec3 &t);
		void scaleObject(const glm::vec3 & s);
		void setGlobalTransform(const glm::mat4x4 &g);
		void rotateFromInput(float x0oofet, float y0offset);
		void zoom(double y0offset);
		glm::mat4x4& GetViewMatrix();
		glm::vec3 GetDirection();
		glm::vec3 GetUp();
		float getZoom();

	};
}
