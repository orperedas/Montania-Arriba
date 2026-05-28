#ifndef CASILLANORMAL_H
#define CASILLANORMAL_H

#include "Casilla.h"

class CasillaNormal : public Casilla {
public:
    CasillaNormal(int num);
    void consecuencia(int numeroAleatorio) override;
};

#endif