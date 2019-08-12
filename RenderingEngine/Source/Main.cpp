#define SDL_MAIN_HANDLED

#include "Window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include <iostream>

int main(int argc, char** argv)
{
	Window MainWindow("TestWindow",800 ,600);
	MainWindow.ShowOpenGLVersion();	
	VertexArray VAO;
	VAO.Bind();
	VertexBuffer VBO;
	GLfloat Vertices[] =
	{
		-0.5f,  -0.5f,	0.f,
		0.f,	0.5f,	0.f,
		0.5f,	-0.5f,	0.f
	};
	VBO.BindBuffer();
	VBO.InitData(sizeof(Vertices), Vertices);
	VertexSpec VertexSpecification;
	VertexSpecification.PushAttribute<GLfloat>(3, false);
	VAO.AddAttributes(VBO, VertexSpecification);
	Shader VertexShader(EShaderType::VERTEX, "E:\\pet\\RenderingEngine\\RenderingEngine\\Source\\DummyVertexShader.vs");
	Shader PixelShader(EShaderType::FRAGMENT, "E:\\pet\\RenderingEngine\\RenderingEngine\\Source\\DummyPixelShader.ps");
	VertexShader.CompileShader();
	PixelShader.CompileShader();
	ShaderProgram MainShaderProgram;
	MainShaderProgram.AddProgram(&VertexShader);
	MainShaderProgram.AddProgram(&PixelShader);
	CHECK(MainShaderProgram.LinkProgram());
	MainShaderProgram.UseProgram();
	while (!MainWindow.WindowIsClosed())
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

		MainShaderProgram.UseProgram();
		VAO.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

		SDL_GL_SwapWindow(MainWindow.GetWindowHandler());
	}
	return 0;
}