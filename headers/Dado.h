#ifndef DADO_H
#define DADO_H

#include <SFML/Graphics.hpp>

class Dado {
private:
    sf::Texture texturaDado;
    sf::Sprite spriteDado;
    
    bool animando;
    sf::Clock relojAnimacion;
    int contadorCambios;
    int resultadoFinal;

public:
    Dado(sf::Vector2f posicion);
    
    int tirar(); 
    void actualizar(); 
    void draw(sf::RenderWindow& ventana);
    
    bool estaAnimando() const;
};

#endif