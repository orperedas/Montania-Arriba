#include "headers/Fuente.h"
#include "headers/Partida.h"
#include "headers/Personaje.h"

#include <algorithm>

Personaje::Personaje() : posicion(0), vidas(3), turnosPerdidos(0), etiquetaNombre(fuenteNombre) {
}

Personaje::Personaje(const sf::Font& fuente, int vidasIniciales) : posicion(0), vidas(vidasIniciales), turnosPerdidos(0), etiquetaNombre(fuente) {
    mShape.setRadius(15.f); 
    mShape.setFillColor(sf::Color::Yellow);
    
    sf::FloatRect bounds = mShape.getLocalBounds();
    setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    Partida partida;
    nombre = partida.getNombreJugador();
}


void Personaje::moverACasilla(int nuevaPosicion) {
    posicion = nuevaPosicion;
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


sf::String Personaje::getNombre() const{
    return nombre;
}

int Personaje::getPosicion() { 
    return posicion; 
}

int Personaje::getVida() { 
    return vidas; 
}


void Personaje::setNombre(sf::String nuevoNombre){
    nombre = nuevoNombre;
}

void Personaje::setPosicionVisual(sf::Vector2f coordenadas) {
    setPosition(coordenadas); 
}



void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform(); 
    target.draw(mShape, states);
    target.draw(etiquetaNombre, states);
}