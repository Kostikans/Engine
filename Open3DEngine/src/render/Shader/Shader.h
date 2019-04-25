#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Engine
{
    class Shader
	{
	public:
		unsigned int ID;
		Shader();
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void use();
		void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const;
		void SetUniform1f(const std::string &name, float value) const;
		void SetUniform3f(const std::string &name, float v0, float v1, float v2) const;
		void SetUniform1i(const std::string &name, int value) const;
		void SetUniform3vec(const std::string &name, const glm::vec3 &value) const;
		void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) const;
		unsigned int  static loadCubemap(std::vector<std::string> faces);
		
	private:

	    void checkCompileErrors(unsigned int shader, std::string type);	
	};
}
