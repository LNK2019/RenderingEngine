#pragma once
#include "glad/glad.h"

class VertexBuffer
{
	GLuint VertexBufferID;
public:
	VertexBuffer(void * Data, GLsizeiptr Size);

	VertexBuffer();

	void InitData(GLsizeiptr Size, void * Data);

	void BindBuffer();
	
	static void UnbindCurrentVertexArray();
	static GLuint GetCurrentArrayBufferBinding();
	
	bool IsValid() const;

	bool IsCurrentlyBound() const;

	GLuint GetID() const;
	 
	~VertexBuffer();
};