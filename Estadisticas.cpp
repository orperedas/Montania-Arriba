#include "headers/Estadisticas.h"
#include <cstdio>
#include <algorithm>

Estadisticas::Estadisticas() {
    _nombreArchivo = "archivos/partidas.dat"; 
}

std::vector<DatosGanador> Estadisticas::obtenerRankingGanadores() {
    std::vector<DatosGanador> ranking;
    Partida registro;
    
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return ranking;
    }

    while (fread(&registro, sizeof(Partida), 1, pArchivo) == 1) {
        
        if (registro.getEstadoPartida() == true) {
            
            for (int i = 0; i < registro.getCantidadJugadores(); ++i) {
                if (registro.getGanador(i) == true) {
                    DatosGanador ganador;
                    ganador.nombre = registro.getNombreJugador(i);
                    ganador.tiradas = registro.getTiradaJugador(i);
                    ganador.idPartida = registro.getIdPartida();
                    ganador.vida = registro.getVidasJugador(i);
                    
                    ranking.push_back(ganador);
                }
            }
        }
    }
    
    fclose(pArchivo);

    std::sort(ranking.begin(), ranking.end(), [](const DatosGanador& a, const DatosGanador& b) {
        return a.tiradas < b.tiradas;
    });

    return ranking;
}