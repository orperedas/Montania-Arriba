#include <iostream>
#include <vector>

#include "headers/PartidaArchivo.h"

PartidaArchivo::PartidaArchivo() {
    _nombreArchivo = "archivos/partidas.dat";
}

PartidaArchivo::PartidaArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

Partida PartidaArchivo::cargarPartida() {
    Partida registro;
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");

    if (pArchivo == nullptr) {
        return registro;
    }

    fread(&registro, sizeof(Partida), 1, pArchivo);
    fclose(pArchivo);

    return registro;
}

void PartidaArchivo::cargarPartidas() {
    Partida registro;
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");

    if (pArchivo == nullptr) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    std::vector<Partida> listaPartidas;

    while (fread(&registro, sizeof(Partida), 1, pArchivo) == 1) {
        listaPartidas.push_back(registro);
    }

    fclose(pArchivo);

    for (const auto& partida : listaPartidas) {
        std::cout << partida.mostrarPartida() << std::endl;
    }
}

bool PartidaArchivo::guardar(const Partida& partida) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    bool exito;
    
    if (pArchivo == nullptr) {
        return false;
    }

    exito = fwrite(&partida, sizeof(Partida), 1, pArchivo);

    fclose(pArchivo);

    return exito;
}

int PartidaArchivo::tamanioArchivo() const {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);
    int tamanio = ftell(pArchivo);
    fclose(pArchivo);

    return tamanio;
}

int PartidaArchivo::tamanioRegistro() const {
    return sizeof(Partida);
}

