#ifndef CASTIGO_H
#define CASTIGO_H

#include "Casilla.h"

class Castigo : public Casilla {
public:
    Castigo(int num, const sf::Texture& textura);
    void consecuencia(int numeroAleatorio, Personaje& personaje) override;
};

#endif