#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include <cstring>

struct DatosJugador {
    char nombre[32];
    int vidas;
    int posicion;
    bool activo;
    bool ganador;
};

class Partida {
private:
    int _idPartida;
    int _dificultad;
    int _cantidadJugadores;
    
    DatosJugador _jugadores[4]; 

public:
    Partida();
    Partida(int idPartida, int dificultad, int cantidadJugadores);

    int getIdPartida() const;
    int getDificultad() const;
    void setDificultad(int dificultad);
    
    int getCantidadJugadores() const;
    void setCantidadJugadores(int cantidad);

    std::string getNombreJugador(int indice) const;
    void setNombreJugador(int indice, const std::string& nombre);
    
    int getVidasJugador(int indice) const;
    void setVidaJugador(int indice, int vidas);
    
    int getPosicionJugador(int indice) const;
    void setPosicionJugador(int indice, int posicion);
    
    bool getJugadorActivo(int indice) const;
    void setJugadorActivo(int indice, bool activo);
    
    bool getGanador(int indice) const;
    void setGanador(int indice, bool ganador);

    std::string mostrarPartida() const;
};

#endif