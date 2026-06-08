#ifndef BENEFICIO_H
#define BENEFICIO_H

#include "Casilla.h"

class Beneficio : public Casilla {
public:
    Beneficio(int num, const sf::Texture& textura);
    void consecuencia(int numeroAleatorio) override;
};

#endif