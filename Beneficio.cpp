#include "headers/Beneficio.h"
#include "headers/Accesibilidad.h"
#include "headers/Sonido.h"


Beneficio::Beneficio(int num, const sf::Texture& textura) : Casilla(num,textura) {}

std::string Beneficio::consecuencia(int numeroAleatorio, Personaje& personaje) {
std::string mActual = "";
    switch (numeroAleatorio) {
        case 1:
            mActual = ". Encuentras una vida.";
            Sonido::reproducir(IDSonido::ganarVida);
            personaje.modificarVidas(1);
            break;
        case 2: {
            int num = (rand() % 8) + 3;
            mActual = ". Avanzas " +  std::to_string(num) + " casillas.";
            Sonido::reproducir(IDSonido::suvida);
            personaje.moverACasilla(personaje.getPosicion() + num);
        } break;
        case 3: 
            mActual = ". Tiras el dado otra vez.";
            Sonido::reproducir(IDSonido::turno);
            personaje.otorgarTurnoExtra();
            break;
        default:
            mensaje = "";
            break;
    }

    std::string msjFinal = mensaje + mActual;
    Accesibilidad::hablar(msjFinal);
    return msjFinal;
}