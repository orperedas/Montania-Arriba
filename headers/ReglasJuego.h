#ifndef REGLASJUEGO_H
#define REGLASJUEGO_H

#include "Partida.h"
#include "Personaje.h"
#include "Tablero.h"

// Definimos los tres enfoques de dificultad que charlamos
enum class Dificultad { FACIL, MEDIO, DIFICIL };

// Definimos los estados posibles para saber si el juego debe terminar
enum class EstadoPartida { EN_CURSO, VICTORIA, DERROTA };

class ReglasJuego {
private:
    Partida partida;
    Dificultad dificultad;
    int ultimaCasilla;


public:
    // El constructor recibe qué dificultad queremos y cuántas casillas tiene el tablero
    ReglasJuego(Dificultad dif, int totalCasillas);

    // Método principal que ejecuta toda la lógica de un turno
    void jugarTurno(Personaje& personaje, Tablero& tablero, int valorDado);
    // Método privado porque solo a esta clase le importa el cálculo matemático
    int calcularDestino(int posActual, int valorDado);

    // Método para preguntarle a las reglas cómo está la partida
    EstadoPartida evaluarEstadoDelJuego(Personaje& personaje);
};

#endif