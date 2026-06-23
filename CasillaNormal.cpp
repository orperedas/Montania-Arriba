#include <SFML/Graphics.hpp>

#include "headers/CasillaNormal.h"
#include "headers/Accesibilidad.h"

CasillaNormal::CasillaNormal(int num, const sf::Texture& textura) : Casilla(num, textura) {
}

void CasillaNormal::consecuencia(int numeroAleatorio, Personaje& personaje) {

    if (numeroAleatorio % 2 == 0) {
        mensaje += ". Terreno seguro. El clima es agradable.";
    } else {
        mensaje += ". Camino firme y despejado. Avanzas sin problemas.";
    }

    Accesibilidad::hablar(mensaje);
}