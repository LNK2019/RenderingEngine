#pragma once 
#include "VertexAttribute.h"
#include "CoreMinimal.h"

GLint VertexSpec::GetMaxNumOfAttribs()
{
	static GLint MaxNumOfAttribs = 0;
	if (MaxNumOfAttribs == 0)
	{
		GLCall(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MaxNumOfAttribs));
	}
	return MaxNumOfAttribs;
}

VertexSpec::VertexSpec() :
	VertexStride(0)
{

}

unsigned int VertexSpec::GetNumOfAttribs() const
{
	return Attribs.size();
}

GLuint VertexSpec::GetGeneralSize()
{
	return VertexStride;
}

VertexSpec::VertexAttrib VertexSpec::GetAttribute(unsigned int Index)
{
	CHECK(Index < Attribs.size());
	return Attribs[Index];
}

bool VertexSpec::IsLimitReached() const
{
	return GetNumOfAttribs() >= (GLuint)GetMaxNumOfAttribs();
}

VertexSpec::~VertexSpec()
{

}
