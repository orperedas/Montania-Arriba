#ifndef CASILLANORMAL_H
#define CASILLANORMAL_H

#include "Casilla.h"

class CasillaNormal : public Casilla {
private:

public:
    CasillaNormal(int num);
    void consecuencia(int numeroAleatorio, Personaje& personaje) override;
};

#endif