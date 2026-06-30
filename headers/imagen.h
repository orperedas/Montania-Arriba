#ifndef IMAGEN_H
#define IMAGEN_H

#include <map>

#include <SFML/Graphics.hpp>

enum class IDImagen{
    Abalancha,
    BotonMenu,
    Casilla,
    Dado,
    Fondo,
    LogoGrande,
    LogoPequenio,
    Personaje
};

class Imagen{
private:
    static std::map<IDImagen, sf::Texture> imagenes;

public:
    static void cargarImagen();
    static const sf::Texture& getImagen(IDImagen id);
};

#endif