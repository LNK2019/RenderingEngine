#include "ShaderProgram.h"
#include "glad/glad.h"

ShaderProgram::ShaderProgram() 
{
	ShaderProgramID  = glCreateProgram();
}

bool ShaderProgram::AddProgram(Shader * ShaderToAdd)
{
	CHECK(ShaderToAdd != nullptr && ShaderToAdd->IsShaderReadyToAttach());
	for (auto ShaderPtr : Shaders)
	{
		if (ShaderPtr == ShaderToAdd)
		{
			LOG("WARNING: Such shader alredy exists in shader program! Shader ID: %i | ShaderProgram ID: %i", ShaderToAdd->GetShaderID(), ShaderProgramID);
			return false;
		}
	}
	GLCall(glAttachShader(ShaderProgramID, ShaderToAdd->GetShaderID()));
	Shaders.push_back(ShaderToAdd);
	return true;
}

bool ShaderProgram::LinkProgram()
{
	if (Shaders.empty() || !AreShadersCompiled() || !IsValid())
	{
		LOG("WARNING: ShaderProgram is not ready to link!");
		return false;
	}
	GLCall(glLinkProgram(ShaderProgramID));
	return true;
}

bool ShaderProgram::AreShadersCompiled() const
{
	for (Shader * ShaderPtr : Shaders)
	{
		if (!ShaderPtr->IsShaderCompiled())
		{
			return false;
		}
	}
	return true;
}

bool ShaderProgram::SetBool(const char * VarName, bool NewValue)
{
	return SetInt(VarName, NewValue); //There is not particular function for boolean uniform 
}

bool ShaderProgram::SetInt(const char * VarName, bool NewValue)
{
	GLint UniformLocation = glGetUniformLocation(ShaderProgramID, VarName);
	if (UniformLocation == -1)
	{
		LOG("WARNING: Shader program failed to find uniform variable %s. Please check if your variable name is appropriate!", VarName);
		return false;
	}
	GLCall(glUniform1i(UniformLocation, NewValue));
	return true;
}

bool ShaderProgram::SetUint(const char * VarName, bool NewValue)
{
	GLint UniformLocation = glGetUniformLocation(ShaderProgramID, VarName);
	if (UniformLocation == -1)
	{
		LOG("WARNING: Shader program failed to find uniform variable %s. Please check if your variable name is appropriate!", VarName);
		return false;
	}
	GLCall(glUniform1ui(glGetUniformLocation(ShaderProgramID, VarName), NewValue));
	return true;
}

bool ShaderProgram::SetFloat(const char * VarName, bool NewValue)
{
	GLint UniformLocation = glGetUniformLocation(ShaderProgramID, VarName);
	if (UniformLocation == -1)
	{
		LOG("WARNING: Shader program failed to find uniform variable %s. Please check if your variable name is appropriate!", VarName);
		return false;
	}
	GLCall(glUniform1ui(glGetUniformLocation(ShaderProgramID, VarName), NewValue));
	return true;
}

bool ShaderProgram::SetDouble(const char * VarName, bool NewValue)
{
	GLint UniformLocation = glGetUniformLocation(ShaderProgramID, VarName);
	if (UniformLocation == -1)
	{
		LOG("WARNING: Shader program failed to find uniform variable %s. Please check if your variable name is appropriate!", VarName);
		return false;
	}
	GLCall(glUniform1d(glGetUniformLocation(ShaderProgramID, VarName), NewValue));
	return true;
}

void ShaderProgram::UseProgram()
{
	GLCall(glUseProgram(ShaderProgramID));
	//glUseProgram(ShaderProgramID);
}

bool ShaderProgram::IsValid()
{
	return ShaderProgramID != 0;
}
