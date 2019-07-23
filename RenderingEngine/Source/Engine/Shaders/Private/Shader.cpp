#include "Shader.h"
#include "CoreMinimal.h"
#include <fstream>
#include <iostream>
#include <sstream>


bool Shader::IsShaderCompilerSupported()
{
	GLboolean Result = GL_FALSE;
	GLCall(glGetBooleanv(GL_SHADER_COMPILER, &Result));
	return Result == GL_TRUE;
}

Shader::Shader(EShaderType::Type InShaderType) :
	bIsShaderCompiled(false)
{
	ShaderType = InShaderType;
	ShaderID = glCreateShader(ShaderType);
	CHECK(IsValid());
}

Shader::Shader(EShaderType::Type InShaderType, const char * ShaderSourcePath) :
	bIsShaderCompiled(false)
{
	ShaderType = InShaderType;
	ShaderID = glCreateShader(ShaderType);
	CHECK(IsValid());
	ReadShaderFromFile(ShaderSourcePath);
}

 bool Shader::IsShaderCodeExist() const
{
	return ShaderCode.empty();
}

 //TODO: I am not sure if we need check here, maybe it will be better to log warnings and return true 
 bool Shader::ReadShaderFromFile(const char * ShaderSourcePath)
 {
	 //create file steam 
	 std::ifstream Outfile;
	 //and open file
	 Outfile.open(ShaderSourcePath);
	 CHECK(Outfile.is_open());

	 //create string stream
	 std::stringstream ShaderSourceStream;
	 ShaderSourceStream << Outfile.rdbuf();
	 ShaderCode = ShaderSourceStream.str();
	 //close the stream
	 Outfile.close();
	 CHECK(IsShaderCodeExist());
	 return true;
 }

 //TODO: DON'T CRASH THE PROGRAM ON EVERY STEP! It's peace of shit to be honest.
 //I'm know that i need to handle somehow compilation error but i gonna crash the program for now
 void Shader::CompileShader()
 {
	CHECK(IsShaderCodeExist() && IsValid() && IsShaderCompilerSupported());
	const char * ShaderSourceRaw = ShaderCode.c_str();
	GLCall(glShaderSource(ShaderID, 1, &(ShaderSourceRaw), NULL));
	glCompileShader(ShaderID);

	int OpResult;
	char InfoLog[INFOLOG_SIZE];
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &OpResult);
	if (!OpResult)
	{
		glGetShaderInfoLog(ShaderID, INFOLOG_SIZE, NULL, InfoLog);
		LOG("ERROR::SHADER_COMPILING: %s", InfoLog);
		bIsShaderCompiled = true;
		CHECK(false);
	}
	else
	{
		bIsShaderCompiled = true;
	}
 }

 bool Shader::IsShaderReadyToAttach() const
 {
	 return IsValid() && IsShaderCodeExist();
 }

 bool Shader::IsShaderCompiled() const
 {
	 return bIsShaderCompiled;
 }

 GLint Shader::GetShaderID() const
 {
	 return ShaderID;
 }

 EShaderType::Type Shader::GetShaderType() const
 {
	 return ShaderType;
 }

 bool Shader::IsValid() const
 {
	 //glCreateShader returns 0 if smth go wrong
	 return ShaderID != 0;
 }
