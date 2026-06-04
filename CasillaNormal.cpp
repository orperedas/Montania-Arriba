#include <SFML/Graphics.hpp>

#include "headers/CasillaNormal.h"
#include "headers/Accesibilidad.h"

CasillaNormal::CasillaNormal(int num) : Casilla(num) {}

void CasillaNormal::consecuencia(int numeroAleatorio) {
    
    if (numeroAleatorio % 2 == 0) {
        mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Terreno seguro. El clima es agradable.";
    } else {
        mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Camino firme y despejado. Avanzas sin problemas.";
    }

    sf::RectangleShape casillaNormal;
    casillaNormal.setSize({50.f, 50.f});
    casillaNormal.setFillColor(sf::Color::White);
    casillaNormal.setPosition({0.f, 0.f});
    casillaNormal.setOutlineThickness(2.f);
    casillaNormal.setOutlineColor(sf::Color::Yellow);

    Accesibilidad::hablar(mensaje);
}

void CasillaNormal::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(casillaNormal);
}