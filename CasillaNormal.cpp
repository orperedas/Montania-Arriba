#include <SFML/Graphics.hpp>

#include "headers/CasillaNormal.h"
#include "headers/Accesibilidad.h"

CasillaNormal::CasillaNormal(int num, const sf::Texture& textura) : Casilla(num, textura) {
}

void CasillaNormal::consecuencia(int numeroAleatorio, Personaje& personaje) {
std::string mActual = "";
    if (numeroAleatorio % 2 == 0) {
        mActual = ". Terreno seguro. El clima es agradable.";
    } else {
        mActual = ". Camino firme y despejado. Avanzas sin problemas.";
    }

    Accesibilidad::hablar(mensaje + mActual);
}