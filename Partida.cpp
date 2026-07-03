#include "headers/Partida.h"

Partida::Partida() : _idPartida(0), _vidasJugador(0), _posicionJugador(0), _jugadorActivo(false), _ganador(false) {
    std::memset(_nombreJugador, 0, 32);
}

Partida::Partida(int idPartida, std::string nombreJugador, int vidasJugador, int posicionJugador, bool jugadorActivo, bool ganador)
  : _idPartida(idPartida),
    _vidasJugador(vidasJugador),
    _posicionJugador(posicionJugador),
    _jugadorActivo(jugadorActivo),
    _ganador(ganador) 
{
    setNombreJugador(nombreJugador);
}

std::string Partida::getNombreJugador() const {
    return std::string(_nombreJugador);
}

void Partida::setNombreJugador(const std::string &nombre) {
    std::strncpy(_nombreJugador, nombre.c_str(), 31);
    _nombreJugador[31] = '\0'; // Aseguramos el terminador nulo
}

int Partida::getIdPartida() const { return _idPartida; }
int Partida::getVidasJugador() const { return _vidasJugador; }
int Partida::getPosicionJugador() const { return _posicionJugador; }
bool Partida::getjugadorActivo() const { return _jugadorActivo; }
bool Partida::getGanador() const { return _ganador; }
void Partida::setDificultad(int dificultad) {
    _dificultad = dificultad;
}

int Partida::getDificultad() const {
    return _dificultad;
}
void Partida::setVidaJugador(int v){
    _vidasJugador=v;
    }