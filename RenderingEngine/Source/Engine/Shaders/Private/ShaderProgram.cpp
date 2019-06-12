#include "ShaderProgram.h"
#include "glad/glad.h"

ShaderProgram::ShaderProgram()
{
	ShaderProgramID  = glCreateProgram();
}

