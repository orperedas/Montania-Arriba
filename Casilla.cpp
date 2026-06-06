#include "headers/Casilla.h"

Casilla::Casilla() : numeroPosicion(0), mensaje("") {}

void Casilla::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(casillaVisual);
}

void Casilla::setPosicionVisual(sf::Vector2f posicion) {
    casillaVisual.setPosition(posicion);
}