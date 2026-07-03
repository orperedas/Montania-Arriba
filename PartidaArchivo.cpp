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