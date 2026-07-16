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
    sf::Clock relojEfecto;
    bool efectoActivo;
public:
    Casilla(int num, const sf::Texture& textura); 
    
    virtual ~Casilla() = default; 

    virtual std::string consecuencia(int numeroAleatorio, Personaje& personaje) = 0;
    virtual void dibujar(sf::RenderTarget& target) const;
    
    void setPosicionVisual(sf::Vector2f posicion);
    sf::Vector2f getPosicionVisual() const { return casillaVisual.getPosition(); }
    int getNumeroPosicion() const { return numeroPosicion; }
    void cambiarTexturaTemporal(const sf::Texture& nuevaTextura);
    virtual void actualizar(); // <-- Revisa el tiempo constantemente
};

#endif