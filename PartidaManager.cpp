#include <iostream>

#include "headers/PartidaArchivo.h"
#include "headers/PartidaManager.h"

PartidaManager::PartidaManager(int idPartida, std::string nombreJugador, int vidasJugador, int posicionJugador, bool jugadorActivo, bool ganador) {}

void PartidaManager::buscarPartida() {
}

void PartidaManager::cargarPartida() {
    
}

void PartidaManager::guardarPartida() {
    PartidaArchivo pArchivo;
    Partida registro;

    int id = 1;
    std::string nombreJugador = partida.getNombreJugador();
    int vidasJugador = partida.getVidasJugador();
    int posicionJugador = partida.getPosicionJugador();
    bool jugadorActivo = false;
    bool ganador = false;

    registro = Partida{id, nombreJugador, vidasJugador, posicionJugador, jugadorActivo, ganador};

    if(pArchivo.guardar(registro)){
        std::cout << "Nuevo masajista guardado con ∩┐╜xito." << std::endl;
    }
    else{
        std::cout << "Error inesperado, no se guard∩┐╜ el registro" << std::endl;
    }
}
