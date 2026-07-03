#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>

#include "Partida.h"
#include "Personaje.h"

class Partida {
private:
    Personaje personaje;

    int _idPartida;
    std::string _nombreJugador;
    int _vidasJugador;
    int _posicionJugador;
    bool _jugadorActivo;
    bool _ganador;

public:
    Partida();
    Partida(int idPartida, std::string nombreJugador, int vidasJugador, int posicionJugador, bool jugadorActivo, bool ganador);

    int getIdPartida() const;
    std::string getNombreJugador() const;
    int getVidasJugador() const;
    int getPosicionJugador() const;
    bool getjugadorActivo() const;
    bool getGanador() const;

    void setNombreJugador(std::string& nombre);
};

#endif