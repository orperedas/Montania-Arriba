#include "Personaje.h"
#include <algorithm>

Personaje::Personaje(int vidasIniciales) : posicion(0), vidas(vidasIniciales), turnosPerdidos(0) {
    mShape.setRadius(50.f); 
    mShape.setFillColor(sf::Color::Yellow);
    
    sf::FloatRect bounds = mShape.getLocalBounds();
    setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f}); 
}


void Personaje::moverACasilla(int nuevaPosicion) {
    posicion = nuevaPosicion;
}

void Personaje::setPosicionVisual(sf::Vector2f coordenadas) {
    setPosition(coordenadas); 
}


void Personaje::modificarVidas(int cantidad) {
    vidas = std::max(0, vidas + cantidad);
}

void Personaje::agregarTurnoPerdido(int cantidad) {
    turnosPerdidos += cantidad;
}

void Personaje::descontarTurnoPerdido() {
    if (turnosPerdidos > 0) {
        --turnosPerdidos;
    }
}


bool Personaje::puedeJugar() { 
    return turnosPerdidos == 0; 
}

bool Personaje::estaVivo() { 
    return vidas > 0; 
}

int Personaje::getPosicion() { 
    return posicion; 
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) {
    states.transform *= getTransform(); 
    target.draw(mShape, states);
}