#ifndef CASILLANORMAL_H
#define CASILLANORMAL_H

#include "Casilla.h"

class CasillaNormal : public Casilla {
private:

public:
    CasillaNormal(int num, const sf::Texture& textura);
    void consecuencia(int numeroAleatorio) override;
    // void dibujar(sf::RenderWindow& ventana) override;
};

#endif