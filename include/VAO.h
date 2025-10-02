#ifndef VAO_H
#define VAO_H

#include "VBO.h"

class VAO
{
public:
    unsigned int ID;
    VAO();
    void Bind();
    void Unbind();
    void Delete();
    void LinkAttrib(VBO &VBO, GLuint index, GLuint size, GLenum type, GLsizeiptr stride, void *pointer);
};

#endif