#pragma once
#include <glad/glad.h>
#include "VertexAttribute.h"

class VertexArray
{
	GLuint ID;
public:
	VertexArray();

	GLuint GetID() const;

	bool IsCurrentlyBound();

	void Bind() const;
	
	void AddAttributes(VertexBuffer TargetBuffer, VertexSpec TargetVertexSpec);
	
	~VertexArray();
};

