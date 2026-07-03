#ifndef PARTIDA_MANAGER_H
#define PARTIDA_MANAGER_H

#include "Partida.h"

class PartidaManager {
private:
    Partida partida;

    int idPartida;
    std::string nombreJugador;
    int vidasJugador;
    int posicionJugador;
    bool jugadorActivo;
    bool ganador;

public:
    PartidaManager() = default;
    PartidaManager(int idPartida, std::string nombreJugador, int vidasJugador, int posicionJugador, bool jugadorActivo, bool ganador);

    void buscarPartida();
    void cargarPartida();
    void guardarPartida();

    ~PartidaManager() = default;
};

#endif