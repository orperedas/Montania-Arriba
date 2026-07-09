#include "headers/ReglasJuego.h"
#include "headers/Accesibilidad.h"
#include <string>
#include <cstdlib>

ReglasJuego::ReglasJuego(Dificultad dif, int totalCasillas) 
    : dificultad(dif), ultimaCasilla(totalCasillas - 1) {
    // Restamos 1 porque si hay 64 casillas, van de la 0 a la 63.
}

int ReglasJuego::calcularDestino(int posActual, int valorDado) {
    int destino = posActual + valorDado;

    switch (dificultad) {
        case Dificultad::FACIL:
            // Si se pasa, simplemente lo dejamos en la última casilla
            return (destino >= ultimaCasilla) ? ultimaCasilla : destino;

        case Dificultad::MEDIO: 
            // Enfoque rebotista
            if (destino > ultimaCasilla) {
                int exceso = destino - ultimaCasilla;
                int rebote = ultimaCasilla - exceso;
                Accesibilidad::hablar("Te pasaste. Reboto " + std::to_string(exceso) + " casillas.");
                return rebote;
            }
            return destino;

        case Dificultad::DIFICIL:
            // Enfoque exacto
            int distancia = ultimaCasilla - posActual;
            if (distancia <= 6) {
                if (valorDado == distancia) {
                    return ultimaCasilla; // Número exacto, gana
                } else {
                    Accesibilidad::hablar("Necesitas sacar un " + std::to_string(distancia) + " para avanzar y ganar.");
                    return posActual; // Se queda donde está
                }
            }
            // Si el destino es mayor que la última casilla y no estaba en zona <= 6 (por seguridad)
            if (destino > ultimaCasilla) return posActual; 
            
            return destino;
    }
    return destino;
}

void ReglasJuego::jugarTurno(Personaje& personaje, Tablero& tablero, int valorDado) {
    int posAnterior = personaje.getPosicion();
    
    // 1. Calculamos la nueva posición según la dificultad
    int nuevaPosicion = calcularDestino(posAnterior, valorDado);
    
    // 2. Movemos al personaje
    personaje.moverACasilla(nuevaPosicion);

    // 3. Verificamos si cayó en la meta
    if (nuevaPosicion == ultimaCasilla) {
        Accesibilidad::hablar("¡Llegaste a la cima! Has completado el recorrido.");
        return; // Cortamos el turno porque ya ganó
    }

    // 4. Ejecutamos la consecuencia de la casilla (solo si realmente se movió)
    if (nuevaPosicion != posAnterior) {
        Casilla* casillaActual = tablero.obtenerCasilla(nuevaPosicion);
        if (casillaActual != nullptr) {
            // Le pasamos el personaje por referencia para que le afecte la vida/turnos
            int cantJugadores = partida.getCantidadJugadores();
            if (cantJugadores > 1){
                casillaActual->consecuencia((rand() % 3) + 1, personaje);
            } else {
                casillaActual->consecuencia((rand() % 2) + 1, personaje);
            }
        }
    }
}

EstadoPartida ReglasJuego::evaluarEstadoDelJuego(Personaje& personaje) {
    if (!personaje.estaVivo()) {
        return EstadoPartida::DERROTA;
    }
    if (personaje.getPosicion() >= ultimaCasilla) {
        return EstadoPartida::VICTORIA;
    }
    return EstadoPartida::EN_CURSO;
}