#pragma once
#include "VertexBuffer.h"
#include "CoreMinimal.h"
#include <vector>

/*@TODO: manage attribs' storage more effective than std::vector*/

/*	Be careful: Order of pushing attribs to VertexSpec will be used as order of binding attributes in OpenGL state
	as a result we will not control location of every layout */
class VertexSpec
{
public:
	struct VertexAttrib
	{
		GLint NumberOfComponents;
		GLenum Type;
		bool IsNormalized;
		GLuint StartPos;
	};

private:
	GLuint VertexStride;
	std::vector<VertexAttrib> Attribs;
public:
	VertexSpec();

	static GLint GetMaxNumOfAttribs();

	bool IsLimitReached() const;

	unsigned int GetNumOfAttribs() const;

	VertexAttrib GetAttribute(unsigned int Index);

	GLuint GetGeneralSize();

	template<typename T>
	void PushAttribute(GLint NumOfComponents, bool bInNormalized)
	{
		static_assert(false);
	}
	template<>
	void PushAttribute<GLfloat>(GLint NumOfComponents, bool bIsNormalized)
	{
		CHECK(!IsLimitReached());
		Attribs.push_back({ NumOfComponents, GL_FLOAT, bIsNormalized, VertexStride });
		VertexStride += NumOfComponents * sizeof(GLfloat);
	}

	template<>
	void PushAttribute<GLuint>(GLint NumOfComponents, bool bIsNormalized)
	{
		CHECK(!IsLimitReached());
		Attribs.push_back({ NumOfComponents, GL_UNSIGNED_INT, bIsNormalized, VertexStride });
		VertexStride += NumOfComponents * sizeof(GLuint);
	}

	template<>
	void PushAttribute<GLint>(GLint NumOfComponents, bool bIsNormalized)
	{
		CHECK(!IsLimitReached());
		Attribs.push_back({ NumOfComponents, GL_INT, bIsNormalized, VertexStride });
		VertexStride += NumOfComponents * sizeof(GLint);
	}

	~VertexSpec();
};
