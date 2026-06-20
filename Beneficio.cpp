#include "headers/Beneficio.h"
#include "headers/Accesibilidad.h"
#include "headers/Sonido.h"


Beneficio::Beneficio(int num, const sf::Texture& textura) : Casilla(num, textura) {
}

void Beneficio::consecuencia(int numeroAleatorio, Personaje& personaje) {
    switch (numeroAleatorio) {
        case 1:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Refugio seguro. Recuperas una vida.";
            Sonido::reproducir(IDSonido::ganarVida);
            personaje.modificarVidas(1);
            break;
        case 2:
            mensaje = "Casilla " + std::to_string(numeroPosicion) + ". Atajo encontrado. Avanzas 3 casillas.";
            personaje.moverACasilla(personaje.getPosicion() + 3);
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