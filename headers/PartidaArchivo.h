#ifndef PARTIDA_ARCHIVO_H
#define PARTIDA_ARCHIVO_H

#include "Partida.h"

class PartidaArchivo {
private:
    std::string _nombreArchivo;

public:
    PartidaArchivo();
    PartidaArchivo(std::string nombreArchivo);
    Partida cargarPartida();

    int tamanioArchivo() const;
    int tamanioRegistro() const;
    bool guardar(const Partida& partida);

    ~PartidaArchivo() = default;
};

#endif