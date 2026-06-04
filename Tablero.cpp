#include <iostream>
#include <algorithm>                // para std::find
#include <cstdlib>                  // para rand() y srand()
#include <ctime>                    // para time(), usado en srand(time(0))
#include <vector>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include "headers/Casilla.h"
#include "headers/CasillaNormal.h"
#include "headers/Beneficio.h"
#include "headers/Castigo.h"
#include "headers/Tablero.h"

Tablero::Tablero() {
    crearTablero();
}

void Tablero::crearTablero() {
    int base = 8;
    int dimencionTablero = base * base;
    
    casillas.reserve(dimencionTablero);
    beneficios.resize((base + (base * 2)) / 4);
    castigos.resize((base + (base * 2)) / 4); 

    posicionesCasEspecial(castigos, beneficios, dimencionTablero);
    
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

    asignarCasillas(casillas, dimencionTablero);
}

void Tablero::posicionesCasEspecial(std::vector<int>& posVector1, std::vector<int>& posVector2, int dimencionTablero) {
    std::unordered_set<int> numerosUsados;
    
    // 1. Llenamos posVector1 sin repetidos
    for (size_t i = 0; i < posVector1.size(); i++) {
        int aleatorio;
        do {
            aleatorio = 7 + rand() % 54;
        } while (numerosUsados.count(aleatorio));
        
        posVector1[i] = aleatorio;
        numerosUsados.insert(aleatorio);
    }

    // 2. Llenamos posVector2 sin repetidos (ni internos ni cruzados)
    for (size_t i = 0; i < posVector2.size(); i++) {
        int aleatorio;
        do {
            aleatorio = 7 + rand() % 54;
        } while (numerosUsados.count(aleatorio));
        
        posVector2[i] = aleatorio;
        numerosUsados.insert(aleatorio);
    }

    // 3. Ordenamos ambos vectores de forma ascendente
    std::sort(posVector1.begin(), posVector1.end());
    std::sort(posVector2.begin(), posVector2.end());
}

void Tablero::asignarCasillas(std::vector<Casilla*>& casillas, int dimencionTablero) {
    for (int casilla = 0; casilla < dimencionTablero; casilla ++) {
        if (std::find(beneficios.begin(), beneficios.end(), casilla) != beneficios.end()) {
            casillas.push_back(new Beneficio(casilla));
        } else if (std::find(castigos.begin(), castigos.end(), casilla) != castigos.end()) {
            casillas.push_back(new Castigo(casilla));
        } else {
            casillas.push_back(new CasillaNormal(casilla));
        }
    }

    for (const auto& casilla : casillas) {
        std::cout << "Casilla " << casilla->getNumeroPosicion() << ": " << typeid(*casilla).name() << std::endl;
    }
}

int Tablero::getCantidadCasillas() const {
    return casillas.size();
}

void Tablero::dibujar(sf::RenderWindow& ventana) {
    
}