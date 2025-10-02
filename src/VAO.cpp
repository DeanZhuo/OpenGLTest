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

void VAO::LinkAttrib(VBO &VBO, GLuint index, GLuint size, GLenum type, GLsizeiptr stride, void *pointer)
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