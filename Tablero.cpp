#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include "headers/Casilla.h"
#include "headers/CasillaNormal.h"
#include "headers/Beneficio.h"
#include "headers/Castigo.h"
#include "headers/Imagen.h"
#include "headers/Tablero.h"

Tablero::Tablero(int baseNum)
:   base(baseNum)
{    
    crearTablero();
}


void Tablero::crearTablero() {
    int dimencionTablero = base * base;     
    casillas.reserve(dimencionTablero);
    beneficios.resize(base);
    castigos.resize(base); 

    posicionesCasEspecial(castigos, beneficios, dimencionTablero);
    
    asignarCasillas(casillas, dimencionTablero);
}


void Tablero::posicionesCasEspecial(std::vector<int>& posVector1, std::vector<int>& posVector2, int dimencionTablero) {

    std::vector<int> disponibles;
    for (int i = 7; i <= 60; i++) {
        disponibles.push_back(i);
    }

    auto seleccionarYLimpiar = [&]() -> int {
        if (disponibles.empty()) return -1;

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
            casillas.push_back(new Beneficio(casilla,Imagen::getImagen(IDImagen::casillaEspecial)));
        } else if (std::find(castigos.begin(), castigos.end(), casilla) != castigos.end()) {
            casillas.push_back(new Castigo(casilla, Imagen::getImagen(IDImagen::casillaEspecial)));
        } else {
            casillas.push_back(new CasillaNormal(casilla,Imagen::getImagen(IDImagen::CasillaNormal)));
        }
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


void Tablero::dibujar(sf::RenderTarget& target) const {
    float tamanioCasilla = 64.f;
    float offsetX = 150.f;
    float altoTablero = base * tamanioCasilla;
    float offsetY = (static_cast<float>(target.getSize().y) - altoTablero) / 2.f - (tamanioCasilla);  

    const sf::Texture& texturaHoja = Imagen::getImagen(IDImagen::TileSand); 

    sf::Sprite spriteBorde(texturaHoja);

    sf::IntRect subRects[3][3] = {
        { sf::IntRect({2, 2}, {66, 66}),   sf::IntRect({68, 2}, {66, 66}),   sf::IntRect({134, 2}, {66, 66}) },
        { sf::IntRect({2, 66}, {66, 66}),  sf::IntRect({68, 66}, {66, 66}),  sf::IntRect({134, 66}, {66, 66}) },
        { sf::IntRect({0, 136}, {66, 66}), sf::IntRect({68, 134}, {66, 66}), sf::IntRect({134, 134}, {66, 66}) }
    };

    for (int filaFrame = -1; filaFrame <= base; ++filaFrame) {
        for (int colFrame = -1; colFrame <= base; ++colFrame) {
            if (filaFrame >= 0 && filaFrame < base && colFrame >= 0 && colFrame < base) {
                continue;
            }

            float x = offsetX + (colFrame * tamanioCasilla);
            float y = offsetY + (filaFrame * tamanioCasilla + (tamanioCasilla * 0.5f));

            int indiceFila = (filaFrame == -1) ? 0 : (filaFrame == base ? 2 : 1);
            int indiceCol = (colFrame == -1) ? 0 : (colFrame == base ? 2 : 1);

            spriteBorde.setTextureRect(subRects[indiceFila][indiceCol]);
            spriteBorde.setPosition({x, y});
            
            target.draw(spriteBorde);
        }
    }

    for (int i = 0; i < casillas.size(); ++i) {
        int pasoVisual = (casillas.size() - 1) - i;

        int fila = pasoVisual / base;
        int columna = 0;

        if (fila % 2 == 0) {
            columna = pasoVisual % base;
        } else {
            columna = (base - 1) - (pasoVisual % base);
        }

        float x = offsetX + (columna * tamanioCasilla);
        float y = offsetY + (fila * tamanioCasilla + (tamanioCasilla * 0.5f));

        casillas[i]->setPosicionVisual({x, y});
        casillas[i]->dibujar(target);
    }
}

void Tablero::actualizar() {
    for (auto& casilla : casillas) {
        casilla->actualizar();
    }
}