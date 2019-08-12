#pragma once

#include "Assertions.h"
#include <string>
#include "glad/glad.h"

#define INFOLOG_SIZE 512

#ifdef RE_DEBUG

#ifdef __GNUC__
#define RE_NOINLINE  __atribute__((noinline))
#endif //__GNUC__

#ifdef _MSC_VER
#define RE_NOINLINE  __declspec(noinline)
#endif //_MSC_VER

#ifndef RE_NOINLINE
#error UNSUPPORTED COMPILER!
#endif //RE_NOINLINE

//Take care: Function is needed to be called only in case if there is 100% error
static std::string GetErrorString(int InErrorResult) {
	CHECK(InErrorResult != GL_NO_ERROR);
	std::string ErrorMessage;

	#define Case(Token) case Token : ErrorMessage = #Token; break;
	
	switch (InErrorResult)
	{
		Case(GL_INVALID_ENUM)
		Case(GL_INVALID_VALUE)
		Case(GL_INVALID_OPERATION)
		Case(GL_STACK_OVERFLOW)
		Case(GL_STACK_UNDERFLOW)
		Case(GL_OUT_OF_MEMORY)
		Case(GL_INVALID_FRAMEBUFFER_OPERATION)
	}

	#undef Case
	return ErrorMessage;
}

static void RE_NOINLINE CheckError(int ErrorResult)
{
	ErrorResult = glGetError(); 
	CHECKF(ErrorResult == GL_NO_ERROR, "ERROR: %s", GetErrorString(ErrorResult).c_str()); 
}

// TODO: Maybe it makes sence to inform user if there is some another error before
#define GLCall(GLFunction) { \
	int ErrorResult; \
	do \
	{ \
		ErrorResult = glGetError(); \
	} \
	while(ErrorResult != GL_NO_ERROR); \
	GLFunction; \
	CheckError(ErrorResult); \
	} 
#else 
#define GLCall(GLFunction) 
#define RE_NOINLINE 
#endif //RE_DEBUG
