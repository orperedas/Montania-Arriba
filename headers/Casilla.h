#ifndef CASILLA_H
#define CASILLA_H

#include <string>
#include <SFML/Graphics.hpp>

#include "Personaje.h"
#include "Sonido.h"

class Casilla {
protected:
    int numeroPosicion;
    std::string mensaje;
    
    sf::Texture texturaCasilla;
    sf::Sprite casillaVisual;

public:
    Casilla(int num, const sf::Texture& textura); 
    
    virtual ~Casilla() = default; 

    virtual void consecuencia(int numeroAleatorio, Personaje& personaje) = 0;
    virtual void dibujar(sf::RenderWindow& ventana);
    
    void setPosicionVisual(sf::Vector2f posicion);
    sf::Vector2f getPosicionVisual() const { return casillaVisual.getPosition(); }
    int getNumeroPosicion() const { return numeroPosicion; }
};

#endif