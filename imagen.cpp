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
    if (!imagenes[IDImagen::Pasto].loadFromFile("imagenes/pasto.png")){
        std::cout << "Error cargando pasto.png" << std::endl;
    }
    if (!imagenes[IDImagen::Personaje_1_verde].loadFromFile("imagenes/personaje1.png")){
        std::cout << "Error cargando personaje1.png" << std::endl;
    }
    if (!imagenes[IDImagen::Personaje_2_rojo].loadFromFile("imagenes/personaje2.png")){
        std::cout << "Error cargando personaje2.png" << std::endl;
    }
    if (!imagenes[IDImagen::Personaje_3_amarillo].loadFromFile("imagenes/personaje3.png")){
        std::cout << "Error cargando personaje3.png" << std::endl;
    }
    if (!imagenes[IDImagen::Personaje_4_azul].loadFromFile("imagenes/personaje4.png")){
        std::cout << "Error cargando personaje4.png" << std::endl;
    }
    if (!imagenes[IDImagen::Tilegrass].loadFromFile("imagenes/tile_grass.png")){
        std::cout << "Error cargando tilegrass.png" << std::endl;
    }
    if (!imagenes[IDImagen::TileSand].loadFromFile("imagenes/Tile_sand.png")){
        std::cout << "Error cargando Tile_sand.png" << std::endl;
    }
    if (!imagenes[IDImagen::casillaEspecial].loadFromFile("imagenes/casillaEspecial.png")){
        std::cout << "Error cargando casillaEspecial.png" << std::endl;
    }
}


const sf::Texture& Imagen::getImagen(IDImagen id) {
    return imagenes.at(id);
}