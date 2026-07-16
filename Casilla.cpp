#include "headers/Casilla.h"
#include "headers/imagen.h"

Casilla::Casilla(int num, const sf::Texture& textura)
    : numeroPosicion(num), 
      mensaje("Casilla " + std::to_string(num + 1)),
      texturaCasilla(textura),
      casillaVisual(texturaCasilla),
      efectoActivo(false)
{
}

void Casilla::dibujar(sf::RenderTarget& target) const {
    target.draw(casillaVisual);
}

void Casilla::setPosicionVisual(sf::Vector2f posicion) {
    casillaVisual.setPosition(posicion);
}
void Casilla::cambiarTexturaTemporal(const sf::Texture& nuevaTextura) {
    casillaVisual.setTexture(nuevaTextura);
    relojEfecto.restart();
    efectoActivo = true;
}

void Casilla::actualizar() {
    if (efectoActivo) {
        if (relojEfecto.getElapsedTime().asSeconds() >= 3.0f) {
            casillaVisual.setTexture(texturaCasilla);
            efectoActivo = false;
        }
    }
}