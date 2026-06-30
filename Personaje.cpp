#include "headers/Personaje.h"

#include <algorithm>

Personaje::Personaje(const sf::Font& fuente, int vidasIniciales) : posicion(0), vidas(vidasIniciales), turnosPerdidos(0), etiquetaNombre(fuente) {
    mShape.setRadius(15.f); 
    mShape.setFillColor(sf::Color::Yellow);
    
    sf::FloatRect bounds = mShape.getLocalBounds();
    setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f}); 
}


void Personaje::setNombre(sf::String nuevoNombre){
    nombre = "Otto";
    etiquetaNombre.setString(nombre);
    etiquetaNombre.setFillColor(sf::Color::Black);
    etiquetaNombre.setCharacterSize(20);

    //sf::FloatRect etiquetaBounds = etiquetaNombre.getLocalBounds();
    //etiquetaNombre.setOrigin({etiquetaBounds.size.x / 2.f, etiquetaBounds.size.y + 20.f});

    sf::FloatRect mShapeBounds = mShape.getGlobalBounds();
    //etiquetaNombre.setPosition({mShapeBounds.position.x + (mShapeBounds.size.x /2), mShapeBounds.position.y + (mShapeBounds.size.y / 2)});
    etiquetaNombre.setPosition({150.f, 300.f});
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

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform(); 
    target.draw(mShape, states);
    target.draw(etiquetaNombre, states);
}