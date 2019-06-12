#pragma once
#include <stdint.h>
#include "glad/glad.h"

namespace EShaderType
{
	enum Type : GLenum
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};
}

class Shader
{
	int32_t ShaderID;
public:
	Shader(EShaderType::Type ShaderType);
	Shader(EShaderType::Type ShaderType, const char * Source);
};