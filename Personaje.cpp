#include "headers/Fuente.h"
#include "headers/imagen.h"
#include "headers/Partida.h"
#include "headers/Personaje.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>


Personaje::Personaje()
  : posicion(0),
    vidas(3),
    turnosPerdidos(0),
    cantTirada(0),
    etiquetaNombre(fuenteNombre),
    personajeSprite(personajeTextura) {}

Personaje::Personaje(const sf::Font& fuente, int nj, int vidasIniciales) 
  : posicion(0),
    vidas(vidasIniciales),
    turnosPerdidos(0),
    cantTirada(0),
    etiquetaNombre(fuente),
    animando(false),
    contadorCambios(0),
    personajeSprite(personajeTextura),
    tiempoProgreso(0.f),
    velocidadAnimacion(1.75f),
    direccionActual(Direccion::Abajo),
    tiempoAcumuladoAnimacion(0.f),
    cuadroActual(0)
{
    switch (nj) {
        case 0:
            personajeSprite.setTexture(Imagen::getImagen(IDImagen::Personaje_1_verde));
            break;
        case 1:
            personajeSprite.setTexture(Imagen::getImagen(IDImagen::Personaje_2_rojo));
            break;
        case 2:
            personajeSprite.setTexture(Imagen::getImagen(IDImagen::Personaje_3_amarillo));
            break;
        case 3:
            personajeSprite.setTexture(Imagen::getImagen(IDImagen::Personaje_4_azul));
            break;
        default:
            personajeSprite.setTexture(Imagen::getImagen(IDImagen::Personaje_1_verde));
            break;
    }

    sf::FloatRect personajeBounds = personajeSprite.getLocalBounds();
    personajeSprite.setOrigin({personajeBounds.position.x + 16, personajeBounds.size.y / 2.f});
    personajeSprite.setTextureRect(sf::IntRect({0, 128}, {64, 64}));
}


void Personaje::comenzarMovimiento(sf::Vector2f coordenadasDestino) {
    posicionOrigen = getPosition();
    posicionDestino = coordenadasDestino;
    tiempoProgreso = 0.0f;
    animando = true;
    tiempoAcumuladoAnimacion = 0.f;
    cuadroActual = 0;

    float deltaX = posicionDestino.x - posicionOrigen.x;
    float deltaY = posicionDestino.y - posicionOrigen.y;

    if (std::abs(deltaX) > std::abs(deltaY)) {
        direccionActual = (deltaX > 0) ? Direccion::Derecha : Direccion::Izquierda;
    } else {
        direccionActual = (deltaY > 0) ? Direccion::Abajo : Direccion::Arriba;
    }

    relojAnimacion.restart();
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
    return (turnosPerdidos == 0) && (vidas > 0); }

bool Personaje::estaVivo() { 
    return vidas > 0; 
}


sf::Texture& Personaje::getTexture() {
    return const_cast<sf::Texture&>(personajeSprite.getTexture());
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

sf::String Personaje::getposicionVisual() const{
    return "Usted se encuentra en la posición visual: " + std::to_string(getPosition().x) + ", " + std::to_string(getPosition().y);
}


void Personaje::otorgarTurnoExtra() { turnoExtra = true; }
bool Personaje::tieneTurnoExtra() const { return turnoExtra; }
void Personaje::usarTurnoExtra() { turnoExtra = false; }
bool Personaje::estaAnimando() const {return animando;}

void Personaje::sumarTirada()  {
    cantTirada++;
}

    
int Personaje::getTirada() {
    return cantTirada;
}
    
void Personaje::cargaPersonaje(int v, int p, int t) {
    vidas = v;
    posicion = p;
    cantTirada = t;
}


void Personaje::actualizar(){
    
    if (!animando) return;
        
    float dt = relojAnimacion.restart().asSeconds();
    tiempoProgreso += dt * velocidadAnimacion;

    if (tiempoProgreso > 1.0f) {
        tiempoProgreso = 1.0f;
    }

    sf::Vector2f posicionActual = posicionOrigen + tiempoProgreso * (posicionDestino - posicionOrigen);
    setPosition(posicionActual);

    tiempoAcumuladoAnimacion += dt;
    
    if (tiempoAcumuladoAnimacion >= 0.06f) {
        cuadroActual = (cuadroActual + 1) % 9;
        tiempoAcumuladoAnimacion = 0.f;
    }

    int posX = cuadroActual * 64; 
    int posY = static_cast<int>(direccionActual) * 64;

    personajeSprite.setTextureRect(sf::IntRect({posX, posY}, {64, 64}));

    if (tiempoProgreso >= 1.0f) {
        animando = false;
        personajeSprite.setTextureRect(sf::IntRect({0, posY}, {64, 64}));
    }
}

    
void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(personajeSprite, states);
    target.draw(etiquetaNombre, states);
}