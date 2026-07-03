#include "headers/Partida.h"

Partida::Partida() {}

Partida::Partida(int idPartida, std::string nombreJugador, int vidasJugador, int posicionJugador, bool jugadorActivo, bool ganador)
  : _idPartida(idPartida),
    _nombreJugador(nombreJugador),
    _vidasJugador(vidasJugador),
    _posicionJugador(posicionJugador),
    _jugadorActivo(jugadorActivo),
    _ganador(ganador) {}


std::string Partida::getNombreJugador() const {
    return _nombreJugador;
}

void Partida::setNombreJugador(std::string &nombre) {
    _nombreJugador = nombre;
}

int Partida::getVidasJugador() const {
    return _vidasJugador;
}

int Partida::getPosicionJugador() const {
    return _posicionJugador;
}

bool Partida::getjugadorActivo() const {
    return _jugadorActivo;
}

bool Partida::getGanador() const {
    return _ganador;
}