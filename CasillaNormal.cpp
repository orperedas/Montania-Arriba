#include <SFML/Graphics.hpp>

#include "headers/CasillaNormal.h"
#include "headers/Accesibilidad.h"

CasillaNormal::CasillaNormal(int num, const sf::Texture& textura) : Casilla(num,textura) {}

std::string CasillaNormal::consecuencia(int numeroAleatorio, Personaje& personaje) {
std::string mActual = "";
    if (numeroAleatorio % 2 == 0) {
Sonido::reproducir(IDSonido::calma1);
        mActual = ". Terreno seguro.";
    } else {
Sonido::reproducir(IDSonido::calma2);
        mActual = ". Camino firme.";
    }
    std::string msjFinal = mensaje + mActual;
    Accesibilidad::hablar(msjFinal);
    return msjFinal;
}