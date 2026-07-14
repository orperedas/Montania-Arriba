#include "headers/Casilla.h"
#include "headers/imagen.h"

Casilla::Casilla(int num)
    : numeroPosicion(num), 
      mensaje("Casilla " + std::to_string(num + 1)),
      texturaCasilla(Imagen::getImagen(IDImagen::CasillaNormal)),
      casillaVisual(texturaCasilla)
{
}

void Casilla::dibujar(sf::RenderTarget& target) const {
    target.draw(casillaVisual);
}

void Casilla::setPosicionVisual(sf::Vector2f posicion) {
    casillaVisual.setPosition(posicion);
}