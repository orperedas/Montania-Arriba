#ifndef CASILLA_H
#define CASILLA_H

#include <string>

#include <SFML/Graphics.hpp>

class Casilla {
protected:
    int numeroPosicion;
    std::string mensaje;
    sf::RectangleShape casillaVisual;

public:
    Casilla();
    Casilla(int num) : numeroPosicion(num) {}
    virtual void consecuencia(int numeroAleatorio) = 0;
    virtual void dibujar(sf::RenderWindow& ventana) = 0;
    
    int getNumeroPosicion() const { return numeroPosicion; }
};

#endif