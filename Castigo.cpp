#include "headers/Castigo.h"
#include "headers/Accesibilidad.h"

Castigo::Castigo(int num, const sf::Texture& textura) : Casilla(num, textura) {
}

void Castigo::consecuencia(int numeroAleatorio, Personaje& personaje) {
std::string mActual = "";
    switch (numeroAleatorio) {
        case 1:
            mActual = ". ¡Un oso salvaje! Pierdes una vida.";
            Sonido::reproducir(IDSonido::rujidoOso);
            personaje.modificarVidas(-1);
            break;
        case 2:
            mActual = ". Caíste en una grieta. Pierdes un turno.";
            Sonido::reproducir(IDSonido::grito);
            Sonido::reproducir(IDSonido::hueso);
            personaje.agregarTurnoPerdido(1);
            break;
        case 3:
            mActual = ". Avalancha. Retrocedes 2 casillas.";
            Sonido::reproducir(IDSonido::avalancha);
            personaje.moverACasilla(personaje.getPosicion() -2);
            break;
        default:
            mensaje = "";
            break;
    }

    Accesibilidad::hablar(mensaje + mActual);
}