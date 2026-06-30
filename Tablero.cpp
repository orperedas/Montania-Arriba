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

Tablero::Tablero(int baseNum) : base(baseNum) {
    if (!texturaNormal.loadFromFile("imagenes/normal.png")) {
        std::cerr << "Error al cargar casilla_normal.png" << std::endl;
    }
    if (!texturaBeneficio.loadFromFile("imagenes/beneficio.png")) {
        std::cerr << "Error al cargar casilla_beneficio.png" << std::endl;
    }
    if (!texturaCastigo.loadFromFile("imagenes/castigo.png")) {
        std::cerr << "Error al cargar casilla_castigo.png" << std::endl;
    }
    crearTablero();
}


void Tablero::crearTablero() {
    int dimencionTablero = base * base;     
    casillas.reserve(dimencionTablero);
    beneficios.resize(base);
    castigos.resize(base); 

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

    std::vector<int> disponibles;
    for (int i = 7; i <= 60; i++) {
        disponibles.push_back(i);
    }

    auto seleccionarYLimpiar = [&]() -> int {
        if (disponibles.empty()) return -1; // por si se acaban los números

        int indiceAleatorio = rand() % disponibles.size();
        int numeroElegido = disponibles[indiceAleatorio];

        disponibles.erase(
            std::remove_if(disponibles.begin(), disponibles.end(), [numeroElegido](int x) {
                return std::abs(x - numeroElegido) < 3;
            }),
            disponibles.end()
        );

        return numeroElegido;
    };

    for (size_t i = 0; i < posVector1.size(); i++) {
        posVector1[i] = seleccionarYLimpiar();
    }

    for (size_t i = 0; i < posVector2.size(); i++) {
        posVector2[i] = seleccionarYLimpiar();
    }

    std::sort(posVector1.begin(), posVector1.end());
    std::sort(posVector2.begin(), posVector2.end());
}


void Tablero::asignarCasillas(std::vector<Casilla*>& casillas, int dimencionTablero) {
    for (int casilla = 0; casilla < dimencionTablero; casilla ++) {
        if (std::find(beneficios.begin(), beneficios.end(), casilla) != beneficios.end()) {
            casillas.push_back(new Beneficio(casilla, texturaBeneficio));
        } else if (std::find(castigos.begin(), castigos.end(), casilla) != castigos.end()) {
            casillas.push_back(new Castigo(casilla, texturaCastigo));
        } else {
            casillas.push_back(new CasillaNormal(casilla, texturaNormal));
        }
    }

    for (const auto& casilla : casillas) {
        std::cout << "Casilla " << casilla->getNumeroPosicion() << ": " << typeid(*casilla).name() << std::endl;
    }
}


int Tablero::getCantidadCasillas() const {
    return casillas.size();
}
Casilla* Tablero::obtenerCasilla(int posicion) {
    if (posicion >= 0 && posicion < casillas.size()) {
        return casillas[posicion];
    }
    
    return nullptr; 
}


void Tablero::dibujar(sf::RenderWindow& ventana) {
    float tamanoCasilla = 64.f;
    float offsetX = 100.f;       
    float offsetY = 100.f;       

    for (int i = 0; i < casillas.size(); ++i) {
        int pasoVisual = (casillas.size() - 1) - i;

        int fila = pasoVisual / base;
        int columna = 0;

        if (fila % 2 == 0) {
            columna = pasoVisual % base;
        } else {
            columna = (base - 1) - (pasoVisual % base);
        }

        float x = offsetX + (columna * tamanoCasilla + 20.f);
        float y = offsetY + (fila * tamanoCasilla);

        casillas[i]->setPosicionVisual({x, y});
        casillas[i]->dibujar(ventana);
    }
}