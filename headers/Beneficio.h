#ifndef BENEFICIO_H
#define BENEFICIO_H

#include "Casilla.h"

class Beneficio : public Casilla {
public:
    Beneficio(int num);
    void consecuencia(int numeroAleatorio) override;
};

#endif