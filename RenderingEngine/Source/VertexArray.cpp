#include "VertexArray.h"
#include "CoreMinimal.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &ID));
}

GLuint VertexArray::GetID() const
{
	return ID;
}

bool VertexArray::IsCurrentlyBound()
{
	GLuint BoundVAO;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&BoundVAO);
	return BoundVAO == ID;
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(ID));
}

void VertexArray::AddAttributes(VertexBuffer TargetBuffer, VertexSpec TargetVertexSpec)
{
	if (!TargetBuffer.IsCurrentlyBound())
		TargetBuffer.BindBuffer();

	if (!IsCurrentlyBound())
		Bind();

	GLuint VertexStride = TargetVertexSpec.GetGeneralSize();
	for (unsigned int i = 0; i < TargetVertexSpec.GetNumOfAttribs(); ++i)
	{
		VertexSpec::VertexAttrib CurrentAttrib = TargetVertexSpec.GetAttribute(i);
		GLCall(glVertexAttribPointer(i, CurrentAttrib.NumberOfComponents,
			CurrentAttrib.Type, CurrentAttrib.IsNormalized, VertexStride, (void*)CurrentAttrib.StartPos));

		GLCall(glEnableVertexAttribArray(i));
	}
}

VertexArray::~VertexArray()
{
}
