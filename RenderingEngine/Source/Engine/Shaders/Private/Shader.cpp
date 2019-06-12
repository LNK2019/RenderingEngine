#include "Shader.h"

Shader::Shader(EShaderType::Type ShaderType)
{
	ShaderID = glCreateShader(ShaderType);

}

Shader::Shader(EShaderType::Type ShaderType, const char * Source)
{
	ShaderID = glCreateShader(ShaderType);
	glShaderSource(ShaderID, 1, &Source, NULL);
}

