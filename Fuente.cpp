#include <iostream>
#include <unordered_map>

#include "headers/Fuente.h"

std::unordered_map<IDFuente, sf::Font> Fuente::fuentes;

void Fuente::cargarFuente(){
    if (!fuentes[IDFuente::BotonMenu].openFromFile("fuentes/ARIALNB.TTF")){
        std::cerr << "Error cargando ARIALNB.TTF" << std::endl;
    }
    if (!fuentes[IDFuente::InputNombre].openFromFile("fuentes/consolab.ttf")){
        std::cerr << "Error cargando consolas.ttf" << std::endl;
    };
    if (!fuentes[IDFuente::TituloPantalla].openFromFile("fuentes/verdanab.ttf")){
        std::cerr << "Error cargando verdanab.ttf" << std::endl;
    };

}


const sf::Font& Fuente::getFuente(IDFuente id) {
    return fuentes.at(id);
}