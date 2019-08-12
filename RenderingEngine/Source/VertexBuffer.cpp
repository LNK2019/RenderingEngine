#include "VertexBuffer.h"
#include "CoreMinimal.h"

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &VertexBufferID));
}

 VertexBuffer::VertexBuffer(void * Data, GLsizeiptr Size)
{
	CHECK((Data != nullptr) && (Size > 0));

	GLCall(glGenBuffers(1, &VertexBufferID));
	BindBuffer();
	InitData(Size, Data);
}
  
 void VertexBuffer::UnbindCurrentVertexArray()
 {
	 GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
 }

 GLuint VertexBuffer::GetID() const
 {
	 return VertexBufferID;
 }

 bool VertexBuffer::IsValid() const
 {
	 return VertexBufferID != 0;
 }

 void VertexBuffer::BindBuffer()
 {
	 GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID));
 }

 void VertexBuffer::InitData(GLsizeiptr Size, void * Data)
 {
	 CHECK(IsCurrentlyBound());
	 GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW));
 }

 bool VertexBuffer::IsCurrentlyBound() const
 {
	 return (GetCurrentArrayBufferBinding() == VertexBufferID) && IsValid();
 }

 GLuint VertexBuffer::GetCurrentArrayBufferBinding()
 {
	 GLuint CurrentArrayBufferID = 0;
	 GLCall(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint*)(&CurrentArrayBufferID))); //GL_ARRAY_BUFFER_BINDING promise to return value > 0
	 return CurrentArrayBufferID;
 }

 VertexBuffer::~VertexBuffer()
 {
	 //glDeleteBuffers(1, &VertexBufferID);
 }
