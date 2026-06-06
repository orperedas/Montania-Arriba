#include <SFML/Graphics.hpp>

#include "headers/CasillaNormal.h"
#include "headers/Accesibilidad.h"

CasillaNormal::CasillaNormal(int num) : Casilla(num) {
    casillaVisual.setSize({64.f, 64.f});
    casillaVisual.setFillColor(sf::Color::Blue);
    casillaVisual.setOutlineThickness(2.f);
    casillaVisual.setOutlineColor(sf::Color::White);
}

void CasillaNormal::consecuencia(int numeroAleatorio) {
    
    if (numeroAleatorio % 2 == 0) {
        mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Terreno seguro. El clima es agradable.";
    } else {
        mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Camino firme y despejado. Avanzas sin problemas.";
    }

    Accesibilidad::hablar(mensaje);
}