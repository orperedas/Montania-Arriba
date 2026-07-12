#include "headers/Casilla.h"

Casilla::Casilla(int num, const sf::Texture& textura) 
    : numeroPosicion(num), 
      mensaje("Casilla " + std::to_string(num + 1)),
      texturaCasilla(textura),
      casillaVisual(textura)
{
}

void Casilla::dibujar(sf::RenderTarget& target) const {
    target.draw(casillaVisual);
}

void Casilla::setPosicionVisual(sf::Vector2f posicion) {
    casillaVisual.setPosition(posicion);
}