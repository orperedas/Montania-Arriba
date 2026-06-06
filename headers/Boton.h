#ifndef BOTON_H
#define BOTON_H

#include <SFML/Graphics.hpp>

class Boton {
private:
    sf::String textoBoton;
    sf::Vector2f posicionBoton;
    sf::Sprite spriteBoton;
    sf::Text etiquetaBoton;

public:
    Boton(const sf::String& texto, sf::Vector2f posicion, const sf::Font& fuente, const sf::Texture& textura);
    
    ~Boton() = default;

    void setSeleccionado(bool seleccionado);
    void dibujar(sf::RenderWindow& ventana);
};

#endif