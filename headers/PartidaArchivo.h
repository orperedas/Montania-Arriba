#ifndef PARTIDA_ARCHIVO_H
#define PARTIDA_ARCHIVO_H

#include "Partida.h"
#include <vector>

class PartidaArchivo {
private:
    std::string _nombreArchivo;

public:
    PartidaArchivo();
    PartidaArchivo(std::string nombreArchivo);
    Partida cargarPartida(int indice); 
    void cargarPartidas();
    int tamanioArchivo() const;
    int tamanioRegistro() const;
    bool guardar(const Partida& partida);
    int contarPartidas(); 
bool modificar(Partida registro, int posicion);
std::vector<int> obtenerIdsPartidasActivas();
Partida leer(int posicion);
~PartidaArchivo() = default;
};

#endif