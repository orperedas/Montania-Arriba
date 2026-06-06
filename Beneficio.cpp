#include "headers/Beneficio.h"
#include "headers/Accesibilidad.h"

Beneficio::Beneficio(int num) : Casilla(num) {
    casillaVisual.setSize({64.f, 64.f});
    casillaVisual.setFillColor(sf::Color::Green);
    casillaVisual.setOutlineThickness(2.f);
    casillaVisual.setOutlineColor(sf::Color::White);
}

void Beneficio::consecuencia(int numeroAleatorio) {
    switch (numeroAleatorio) {
        case 1:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Refugio seguro. Recuperas una vida.";
            break;
        case 2:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Atajo encontrado. Avanzas 3 casillas.";
            break;
        case 3:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". beneficio. Tiras el dado otra vez.";
            break;
        default:
            mensaje = "";
            break;
    }

    Accesibilidad::hablar(mensaje);
}