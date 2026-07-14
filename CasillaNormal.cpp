#include <SFML/Graphics.hpp>

#include "headers/CasillaNormal.h"
#include "headers/Accesibilidad.h"

CasillaNormal::CasillaNormal(int num) : Casilla(num) {}

void CasillaNormal::consecuencia(int numeroAleatorio, Personaje& personaje) {
std::string mActual = "";
    if (numeroAleatorio % 2 == 0) {
Sonido::reproducir(IDSonido::calma1);
        mActual = ". Terreno seguro. El clima es agradable.";
    } else {
Sonido::reproducir(IDSonido::calma2);
        mActual = ". Camino firme y despejado. Avanzas sin problemas.";
    }

    Accesibilidad::hablar(mensaje + mActual);
}