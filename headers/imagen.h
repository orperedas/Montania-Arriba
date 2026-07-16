#ifndef IMAGEN_H
#define IMAGEN_H

#include <map>

#include <SFML/Graphics.hpp>

enum class IDImagen{
    Abalancha,
    BotonMenu,
    CasillaNormal,
    CasillaBeneficio,
    CasillaCastigo,
    Corazon,
    Dado,
    Fondo,
    LogoGrande,
    LogoPequenio,
    Pasto,
    Personaje_1_verde,
    Personaje_2_rojo,
    Personaje_3_amarillo,
    Personaje_4_azul,
    TileSand,
    Tilegrass,
    casillaEspecial
};

class Imagen{
private:
    static std::map<IDImagen, sf::Texture> imagenes;

public:
    static void cargarImagen();
    static const sf::Texture& getImagen(IDImagen id);
};

#endif