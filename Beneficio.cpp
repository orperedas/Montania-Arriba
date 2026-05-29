#include "headers/Beneficio.h"
#include "headers/Accesibilidad.h"

Beneficio::Beneficio(int num) : Casilla(num) {}

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