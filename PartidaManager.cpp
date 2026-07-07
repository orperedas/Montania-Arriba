#include <iostream>
#include "headers/PartidaArchivo.h"
#include "headers/PartidaManager.h"

// Inicializamos el manager copiando la partida actual
PartidaManager::PartidaManager(const Partida& p) : partida(p) {}

void PartidaManager::buscarPartida() {
}

void PartidaManager::cargarPartida() {
}

void PartidaManager::guardarPartida() {
    PartidaArchivo pArchivo;
    
    // 1. Leemos los datos globales de la partida que tiene el Manager
    int id = partida.getIdPartida();
    int dificultad = partida.getDificultad();
    int cantidad = partida.getCantidadJugadores();

    // 2. Creamos el objeto registro usando tu constructor de 3 parámetros
    Partida registro(id, dificultad, cantidad);

    for (int i = 0; i < cantidad; ++i) {
        // Usamos los métodos exactos que definiste en tu Partida.h
        registro.setNombreJugador(i, partida.getNombreJugador(i));
        
        registro.setVidaJugador(i, partida.getVidasJugador(i)); 
        
        registro.setPosicionJugador(i, partida.getPosicionJugador(i));
        registro.setJugadorActivo(i, partida.getJugadorActivo(i));
        registro.setGanador(i, partida.getGanador(i));
    }

    // 4. Guardamos el registro completo en el archivo binario
    if (pArchivo.guardar(registro)) {
        std::cout << "Partida guardada con éxito." << std::endl;
    } else {
        std::cout << "Error inesperado, no se guardó el registro." << std::endl;
    }
}

void PartidaManager::listarPartidas() {
}