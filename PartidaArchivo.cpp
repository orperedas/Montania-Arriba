#include <iostream>
#include <vector>

#include "headers/PartidaArchivo.h"

PartidaArchivo::PartidaArchivo() {
    _nombreArchivo = "archivos/partidas.dat";
}

PartidaArchivo::PartidaArchivo(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

Partida PartidaArchivo::cargarPartida(int indice) {
    Partida registro;
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");

    if (pArchivo == nullptr) return registro;

    fseek(pArchivo, indice * sizeof(Partida), SEEK_SET); 
    
    fread(&registro, sizeof(Partida), 1, pArchivo);
    fclose(pArchivo);

    return registro;
}

int PartidaArchivo::contarPartidas() {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) return 0; // Si no hay archivo, hay 0 partidas

    fseek(pArchivo, 0, SEEK_END); // Nos vamos al final del archivo
    int bytes = ftell(pArchivo);  // Preguntamos en qué byte estamos
    fclose(pArchivo);

    return bytes / sizeof(Partida); // Dividimos el total por lo que pesa una partida
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

bool PartidaArchivo::modificar(Partida registro, int posicion) {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == nullptr) return false;

    fseek(pArchivo, posicion * sizeof(Partida), SEEK_SET);
    bool resultado = fwrite(&registro, sizeof(Partida), 1, pArchivo);

    fclose(pArchivo);
    return resultado;
}

std::vector<int> PartidaArchivo::obtenerIdsPartidasActivas() {
    std::vector<int> ids;
    Partida registro;
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    
    if (pArchivo != nullptr) {
        while (fread(&registro, sizeof(Partida), 1, pArchivo) == 1) {
            if (!registro.getEstadoPartida()) {
                ids.push_back(registro.getIdPartida());
            }
        }
        fclose(pArchivo);
    }
    return ids;
}

Partida PartidaArchivo::leer(int posicion) {
    Partida registro;
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    
    if (pArchivo != nullptr) {
        fseek(pArchivo, posicion * sizeof(Partida), SEEK_SET);
        fread(&registro, sizeof(Partida), 1, pArchivo);
        fclose(pArchivo);
    }
    return registro; 
}