#include <iostream>
#include <cstdlib>  // para rand() y srand()
#include <ctime>    // para time(), usado en srand(time(0))

#include "headers/Casilla.h"
#include "headers/Tablero.h"

Tablero::Tablero() {
    crearTablero();
}

void Tablero::crearTablero() {
    int base = 8;
    int dimencionTablero = base * base;
    
    casillas.reserve(dimencionTablero);
    beneficios.resize((base + (base * 2)) / 2);
    castigos.resize((base + (base * 2)) / 4); 

    posicionesCasEspecial(beneficios, dimencionTablero);
    posicionesCasEspecial(castigos, dimencionTablero);
    
    std::cout << "Valores de beneficios: ";
    for (const auto& valor : beneficios) {
        std::cout << valor << " ";
    }
    std::cout << std::endl;

    std::cout << "Valores de castigos: ";
    for (const auto& valor : castigos) {
        std::cout << valor << " ";
    }
    std::cout << std::endl;
}

void Tablero::posicionesCasEspecial(std::vector<int>& posiciones, int dimencionTablero) {
    for (int casilla = 0; casilla < static_cast<int>(posiciones.size()); casilla++) {
        int aleatorio;
        bool repetido;
        
        do {
            aleatorio = 7 + rand() % (dimencionTablero - 4);
            repetido = false;
        
            for (int i = 0; i < static_cast<int>(posiciones.size()); i++) {
                if (posiciones[i] == aleatorio) {
                    repetido = true;
                    break;
                }
            }
        } while (repetido);
            posiciones[casilla] = aleatorio;
    }
}

int Tablero::getCantidadCasillas() const {
    return static_cast<int>(casillas.size());
}