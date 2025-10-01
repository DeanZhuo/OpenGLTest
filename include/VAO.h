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
    void LinkAttrib(VBO &VBO, unsigned int index, unsigned int size, unsigned int type, std::ptrdiff_t stride, void *pointer);
};

#endif