#pragma once
#include <GL/glew.h>
#include <iostream>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#define ASSERT(x) if ((!x))__debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(glLogCall(#x,__FILE__,__LINE__))


void GLClearError();
bool  glLogCall(const char* function, const char* file, int line);
class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader) const;

};