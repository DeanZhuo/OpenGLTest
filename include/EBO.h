#ifndef EBO_H
#define EBO_H

#include "VBO.h"

class EBO
{
public:
    unsigned int ID;
    EBO(unsigned int *indices, std::ptrdiff_t size);
    void Bind();
    void Unbind();
    void Delete();
};

#endif