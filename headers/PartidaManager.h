#ifndef PARTIDA_MANAGER_H
#define PARTIDA_MANAGER_H

#include "Partida.h"

class PartidaManager {
private:
    Partida partida; // El Manager guarda una instancia de la partida actual

public:
    PartidaManager() = default;
    
    PartidaManager(const Partida& p);

    void buscarPartida();
    void cargarPartida();
    int guardarPartida();
    void listarPartidas();

    ~PartidaManager() = default;
};

#endif