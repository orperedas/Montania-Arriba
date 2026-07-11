#include <iostream>
#include "headers/PartidaArchivo.h"
#include "headers/PartidaManager.h"

PartidaManager::PartidaManager(const Partida& p) : partida(p) {}

void PartidaManager::buscarPartida() {
}

void PartidaManager::cargarPartida() {
}
int PartidaManager::guardarPartida() {
    PartidaArchivo pArchivo;
    
    int id = partida.getIdPartida();
    bool esNueva = (id == 0);

    if (esNueva) {
        int tamArchivo = pArchivo.tamanioArchivo();
        int tamRegistro = pArchivo.tamanioRegistro();
        id = (tamArchivo / tamRegistro) + 1; 
        
        partida.setIdPartida(id);
    }

    Partida registro(id, partida.getDificultad(), partida.getCantidadJugadores());
    registro.setEstadoPartida(partida.getEstadoPartida());

    for (int i = 0; i < partida.getCantidadJugadores(); ++i) {
        registro.setNombreJugador(i, partida.getNombreJugador(i));
        registro.setVidaJugador(i, partida.getVidasJugador(i)); 
        registro.setPosicionJugador(i, partida.getPosicionJugador(i));
        registro.setJugadorActivo(i, partida.getJugadorActivo(i));
        registro.setGanador(i, partida.getGanador(i));
        registro.setTiradaJugador(i, partida.getTiradaJugador(i)); 
    }

    if (esNueva) {
        if (pArchivo.guardar(registro)) {
            std::cout << "Nueva partida guardada con éxito. ID: " << id << std::endl;
        }
    } else {
        int posicion = id - 1; // El ID 1 está en la posición 0 del archivo
        if (pArchivo.modificar(registro, posicion)) {
            std::cout << "Partida actualizada con éxito. ID: " << id << std::endl;
        }
    }
return id;
}
void PartidaManager::listarPartidas() {
}