#ifndef BOTON_H
#define BOTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Boton {
private:
    std::string textoBoton;
    sf::Vector2f posicionBoton;
    sf::Sprite spriteBoton;
    sf::Text etiquetaBoton;
    sf::Vector2f mousePos;

public:
    Boton(const std::string& texto, sf::Vector2f posicion, const sf::Font& fuente, const sf::Texture& textura);
    
    ~Boton() = default;

    void setSeleccionado(bool seleccionado);
    void dibujar(sf::RenderWindow& ventana);
};

#endif