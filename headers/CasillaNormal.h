#ifndef CASILLANORMAL_H
#define CASILLANORMAL_H

#include "Casilla.h"

class CasillaNormal : public Casilla {
private:
    sf::RectangleShape casillaNormal;

public:
    CasillaNormal(int num);
    void consecuencia(int numeroAleatorio) override;
    void dibujar(sf::RenderWindow& ventana) {};
};

#endif