#ifndef CASTIGO_H
#define CASTIGO_H

#include "Casilla.h"

class Castigo : public Casilla {
public:
    Castigo(int num);
    void consecuencia(int numeroAleatorio) override;
};

#endif