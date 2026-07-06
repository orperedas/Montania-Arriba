#include <iostream>

#include "headers/Imagen.h"

std::map<IDImagen, sf::Texture> Imagen::imagenes;

void Imagen::cargarImagen(){
    if (!imagenes[IDImagen::Abalancha].loadFromFile("imagenes/abalancha.png")){
        std::cerr << "Error cargando abalancha.png" << std::endl;
    }
    if (!imagenes[IDImagen::BotonMenu].loadFromFile("imagenes/menu_boton.png")){
        std::cerr << "Error cargando ARIALNB.TTF" << std::endl;
    }
    if (!imagenes[IDImagen::CasillaNormal].loadFromFile("imagenes/normal.png")){
        std::cerr << "Error cargando consolas.ttf" << std::endl;
    }
    if (!imagenes[IDImagen::CasillaBeneficio].loadFromFile("imagenes/beneficio.png")){
        std::cerr << "Error cargando beneficio.png" << std::endl;
    }
    if (!imagenes[IDImagen::CasillaCastigo].loadFromFile("imagenes/castigo.png")){
        std::cerr << "Error cargando castigo.png" << std::endl;
    }
    if (!imagenes[IDImagen::Corazon].loadFromFile("imagenes/corazon.png")){
        std::cerr << "Error cargando corazon.png" << std::endl;
    }
    if (!imagenes[IDImagen::Dado].loadFromFile("imagenes/dado_sprites.png")){
        std::cerr << "Error cargando verdanab.ttf" << std::endl;
    };
    if (!imagenes[IDImagen::Fondo].loadFromFile("imagenes/fondo.png")){
        std::cout << "Error cargando fondo.png0" << std::endl;
    }
    if (!imagenes[IDImagen::LogoGrande].loadFromFile("imagenes/montania_arriba_logo_pequenio.png")){
        std::cout << "Error cargendo montania_arriba_logo_grande.png" << std::endl;
    };
    if (!imagenes[IDImagen::LogoPequenio].loadFromFile("imagenes/montania_arriba_logo_pequenio.png")){
        std::cout << "Error cargando montania_arriga_logo_pequenio.png" << std::endl;
    }
    if (!imagenes[IDImagen::Tilegrass].loadFromFile("imagenes/tilegrass.png")){
        std::cout << "Error cargando tilegrass.png" << std::endl;
    }
}


const sf::Texture& Imagen::getImagen(IDImagen id) {
    return imagenes.at(id);
}