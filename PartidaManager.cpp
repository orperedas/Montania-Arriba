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

void PartidaManager::listarPartidas() {
    PartidaArchivo pArchivo;
    Partida registro;
    
    int tam_registro = sizeof(Partida);
    int tam_archivo = pArchivo.tamanioArchivo();
    int cantidad_registros = tam_archivo / tam_registro;

    std::cout << "Cantidad de partidas guardadas: " << cantidad_registros << std::endl;

    /*
    for (int i = 0; i < cantidad_registros; ++i) {
        registro = pArchivo.cargarPartidas();
        std::cout << registro.mostrarPartida() << std::endl;
    }*/
}