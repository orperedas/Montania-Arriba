#ifndef CASILLA_H
#define CASILLA_H

#include <string>

class Casilla {
protected:
    int numeroPosicion;
    std::string mensaje;

public:
    Casilla(int num) : numeroPosicion(num) {}
    virtual ~Casilla() = default; 
    virtual void consecuencia(int numeroAleatorio) = 0; 
};

#endif