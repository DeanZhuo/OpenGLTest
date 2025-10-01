#include "VAO.h"
#include <GL/glew.h>

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::LinkAttrib(VBO &VBO, unsigned int index, unsigned int size, unsigned int type, std::ptrdiff_t stride, void *pointer)
{
    VBO.Bind();
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
    VBO.Unbind();
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}