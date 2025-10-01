#ifndef VBO_H
#define VBO_H
#include <cstddef> // for std::ptrdiff_t

class VBO
{
public:
    unsigned int ID;
    VBO(float *vertices, std::ptrdiff_t size);
    void Bind();
    void Unbind();
    void Delete();
};

#endif