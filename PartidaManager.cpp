#include <iostream>
#include "headers/PartidaArchivo.h"
#include "headers/PartidaManager.h"

PartidaManager::PartidaManager(const Partida& p) : partida(p) {}

void PartidaManager::buscarPartida() {
}

void PartidaManager::cargarPartida() {
}

void PartidaManager::guardarPartida() {
    PartidaArchivo pArchivo;
    
    int id = partida.getIdPartida();
    
    if (id == 0) {
        id = pArchivo.contarPartidas() + 1;
    }

    int dificultad = partida.getDificultad();
    int cantidad = partida.getCantidadJugadores();

    Partida registro(id, dificultad, cantidad);
    for (int i = 0; i < cantidad; ++i) {
        registro.setNombreJugador(i, partida.getNombreJugador(i));
        
        registro.setVidaJugador(i, partida.getVidasJugador(i)); 
        
        registro.setPosicionJugador(i, partida.getPosicionJugador(i));
        registro.setJugadorActivo(i, partida.getJugadorActivo(i));
        registro.setGanador(i, partida.getGanador(i));
    }

    if (pArchivo.guardar(registro)) {
        std::cout << "Partida guardada con éxito." << std::endl;
    } else {
        std::cout << "Error inesperado, no se guardó el registro." << std::endl;
    }
}

void PartidaManager::listarPartidas() {
}