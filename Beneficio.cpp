#include "headers/Beneficio.h"
#include "headers/Accesibilidad.h"
#include "headers/Sonido.h"


Beneficio::Beneficio(int num, const sf::Texture& textura) : Casilla(num, textura) {
}

void Beneficio::consecuencia(int numeroAleatorio, Personaje& personaje) {
std::string mActual = "";
    switch (numeroAleatorio) {
        case 1:
            mActual = ". Refugio seguro. Recuperas una vida.";
            Sonido::reproducir(IDSonido::ganarVida);
            personaje.modificarVidas(1);
            break;
        case 2:
            mActual = ". Atajo encontrado. Avanzas 3 casillas.";
            Sonido::reproducir(IDSonido::suvida);
            personaje.moverACasilla(personaje.getPosicion() + 3);
            break;
        case 3:
            mActual = ". beneficio. Tiras el dado otra vez.";
            personaje.otorgarTurnoExtra(); // ACTIVAMOS EL TURNO EXTRA
            break;
        default:
            mensaje = "";
            break;
    }

    Accesibilidad::hablar(mensaje + mActual);
}