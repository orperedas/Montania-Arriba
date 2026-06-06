#include "headers/Castigo.h"
#include "headers/Accesibilidad.h"

Castigo::Castigo(int num) : Casilla(num) {
    casillaVisual.setSize({64.f, 64.f});
    casillaVisual.setFillColor(sf::Color::Red);
    casillaVisual.setOutlineThickness(2.f);
    casillaVisual.setOutlineColor(sf::Color::White);
}

void Castigo::consecuencia(int numeroAleatorio) {
    switch (numeroAleatorio) {
        case 1:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". ¡Un oso salvaje! Pierdes una vida.";
            break;
        case 2:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Caíste en una grieta. Pierdes un turno.";
            break;
        case 3:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Avalancha. Retrocedes 2 casillas.";
            break;
        default:
            mensaje = "";
            break;
    }

    Accesibilidad::hablar(mensaje);
}