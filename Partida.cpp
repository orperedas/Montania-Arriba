#include <iostream>
#include <cstring>
#include "headers/Partida.h"

Partida::Partida() : _idPartida(0), _dificultad(0), _cantidadJugadores(1) {
    std::memset(_jugadores, 0, sizeof(_jugadores));
}

Partida::Partida(int idPartida, int dificultad, int cantidadJugadores)
  : _idPartida(idPartida),
    _dificultad(dificultad),
    _cantidadJugadores(cantidadJugadores) 
{
    std::memset(_jugadores, 0, sizeof(_jugadores));
}

int Partida::getIdPartida() const { return _idPartida; }
int Partida::getDificultad() const { return _dificultad; }
void Partida::setDificultad(int dificultad) { _dificultad = dificultad; }
int Partida::getCantidadJugadores() const { return _cantidadJugadores; }
void Partida::setCantidadJugadores(int cantidad) { _cantidadJugadores = cantidad; }


std::string Partida::getNombreJugador(int indice) const {
    if (indice >= 0 && indice < 4) {
        return std::string(_jugadores[indice].nombre);
    }
    return "Desconocido";
}

void Partida::setNombreJugador(int indice, const std::string &nombre) {
    if (indice >= 0 && indice < 4) {
        std::strncpy(_jugadores[indice].nombre, nombre.c_str(), 31);
        _jugadores[indice].nombre[31] = '\0';
    }
}

int Partida::getVidasJugador(int indice) const {
    if (indice >= 0 && indice < 4) return _jugadores[indice].vidas;
    return 0;
}

void Partida::setVidaJugador(int indice, int vidas) {
    if (indice >= 0 && indice < 4) _jugadores[indice].vidas = vidas;
}

int Partida::getPosicionJugador(int indice) const {
    if (indice >= 0 && indice < 4) return _jugadores[indice].posicion;
    return -1;
}

void Partida::setPosicionJugador(int indice, int posicion) {
    if (indice >= 0 && indice < 4) _jugadores[indice].posicion = posicion;
}

bool Partida::getJugadorActivo(int indice) const {
    if (indice >= 0 && indice < 4) return _jugadores[indice].activo;
    return false;
}

void Partida::setJugadorActivo(int indice, bool activo) {
    if (indice >= 0 && indice < 4) _jugadores[indice].activo = activo;
}

bool Partida::getGanador(int indice) const {
    if (indice >= 0 && indice < 4) return _jugadores[indice].ganador;
    return false;
}

void Partida::setGanador(int indice, bool ganador) {
    if (indice >= 0 && indice < 4) _jugadores[indice].ganador = ganador;
}

std::string Partida::mostrarPartida() const {
    std::string info = "ID: " + std::to_string(_idPartida) +
                       ", Dificultad: " + std::to_string(_dificultad) +
                       ", Cantidad Jugadores: " + std::to_string(_cantidadJugadores) + "\n";
    
    for (int i = 0; i < _cantidadJugadores; ++i) {
        info += "  -> Jugador [" + std::to_string(i + 1) + "]: " +
                std::string(_jugadores[i].nombre) +
                " | Vidas: " + std::to_string(_jugadores[i].vidas) +
                " | Posicion: " + std::to_string(_jugadores[i].posicion) +
                " | Activo: " + (_jugadores[i].activo ? "Si" : "No") +
                " | Ganador: " + (_jugadores[i].ganador ? "Si" : "No") + "\n";
    }
    return info;
}