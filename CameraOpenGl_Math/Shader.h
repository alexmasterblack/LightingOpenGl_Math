#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "shaderLoader.h"
#include "Mat4.h"
#include "Vec3.h"

class Shader {
private:
	unsigned int shaderProgram;

	glm::mat4 TrueView(const Mat4& data);
public:
	Shader() = default;

	Shader(std::string vertexPath, std::string fragmentPath);

	void SetMat4(std::string id, const Mat4& data);

	void SetVec3(const std::string id, const Vec3& data);

	void SetInt(const std::string id, int data);

	void SetFloat(const std::string id, float data);

	void Use();
};

#endif