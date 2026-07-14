#include "headers/Beneficio.h"
#include "headers/Accesibilidad.h"
#include "headers/Sonido.h"


Beneficio::Beneficio(int num) : Casilla(num) {}

void Beneficio::consecuencia(int numeroAleatorio, Personaje& personaje) {
std::string mActual = "";
    switch (numeroAleatorio) {
        case 1:
            mActual = ". Refugio seguro. Recuperas una vida.";
            Sonido::reproducir(IDSonido::ganarVida);
            personaje.modificarVidas(1);
            break;
        case 2: {
            int num = (rand() % 8) + 3;
            mActual = ". Atajo encontrado. Avanzas " +  std::to_string(num) + " casillas.";
            Sonido::reproducir(IDSonido::suvida);
            personaje.moverACasilla(personaje.getPosicion() + num);
        } break;
        case 3: 
            mActual = ". beneficio. Tiras el dado otra vez.";
            Sonido::reproducir(IDSonido::turno);
            personaje.otorgarTurnoExtra();
            break;
        default:
            mensaje = "";
            break;
    }

    Accesibilidad::hablar(mensaje + mActual);
}