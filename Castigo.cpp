#include "headers/Castigo.h"
#include "headers/Accesibilidad.h"

Castigo::Castigo(int num, const sf::Texture& textura) : Casilla(num, textura) {
}

void Castigo::consecuencia(int numeroAleatorio, Personaje& personaje) {
    switch (numeroAleatorio) {
        case 1:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". ¡Un oso salvaje! Pierdes una vida.";
            Sonido::reproducir(IDSonido::rujidoOso);
            personaje.modificarVidas(-1);
            break;
        case 2:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Caíste en una grieta. Pierdes un turno.";
            personaje.descontarTurnoPerdido();
            break;
        case 3:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Avalancha. Retrocedes 2 casillas.";
            Sonido::reproducir(IDSonido::avalancha);
            personaje.moverACasilla(personaje.getPosicion() -2);
            break;
        default:
            mensaje = "";
            break;
    }

    Accesibilidad::hablar(mensaje);
}