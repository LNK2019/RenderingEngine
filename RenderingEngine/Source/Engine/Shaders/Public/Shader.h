#pragma once
#include "glad/glad.h"
#include <stdint.h>
#include <string>

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

	GLint ShaderID;
	std::string ShaderCode;
	EShaderType::Type ShaderType;
	bool bIsShaderCompiled;
public:
	Shader(EShaderType::Type ShaderType);
	//calls ReadShaderFromFile
 	Shader(EShaderType::Type ShaderType, const char * ShaderSourcePath);
	bool ReadShaderFromFile(const char * ShaderSourcePath);
	void CompileShader();
	bool IsShaderReadyToAttach() const;
	bool IsShaderCompiled() const;
	GLint GetShaderID() const;
	EShaderType::Type GetShaderType() const;
private:
	static bool IsShaderCompilerSupported();
	//return true if ShaderCode is not empty
	bool IsShaderCodeExist() const;
	//return true if ShaderID is valid
	bool IsValid() const;
};