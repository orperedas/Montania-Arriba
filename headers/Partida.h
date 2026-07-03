#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include <cstring>

class Partida {
private:
    int _dificultad;
    int _idPartida;
    char _nombreJugador[32]; // Tamaño fijo para el archivo binario
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

    void setNombreJugador(const std::string& nombre);
    void setDificultad(int dificultad);
    int getDificultad() const;
 void setVidaJugador(int v);
};

#endif