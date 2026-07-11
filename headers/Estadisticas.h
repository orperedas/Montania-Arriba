#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include <vector>
#include <string>
#include "Partida.h"

struct DatosGanador {
    std::string nombre;
    int tiradas;
    int idPartida;
    int vida;
};

class Estadisticas {
private:
    std::string _nombreArchivo;

public:
    Estadisticas();
    
    std::vector<DatosGanador> obtenerRankingGanadores();
};

#endif