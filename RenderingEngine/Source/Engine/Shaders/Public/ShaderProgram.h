#pragma once
#include <stdint.h>
#include <vector>
#include "Shader.h"
#include "CoreMinimal.h"

class ShaderProgram
{
	int32_t ShaderProgramID;
	std::vector<Shader *> Shaders;
public:
	ShaderProgram();
	//returns false if there is already existing shader 
	bool AddProgram(Shader * ShaderToAdd);
	bool LinkProgram();
	bool SetBool(const char * VarName, bool NewValue);
	bool SetInt(const char * VarName, bool NewValue);
	bool SetUint(const char * VarName, bool NewValue);
	bool SetFloat(const char * VarName, bool NewValue);
	bool SetDouble(const char * VarName, bool NewValue);
	//TODO: Also i need to add another setters for uniform variables(or use another approach to set them) that are not already here but it's enough for now
private:
	bool AreShadersCompiled() const;
};