#ifndef BOTON_H
#define BOTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <functional>
#include <string>

#include "Visual.h"

class Boton{
private:
    std::string textoBoton;
    sf::Vector2f posicionBoton;
    sf::Sprite spriteBoton;
    sf::Text etiquetaBoton;
    sf::Vector2f mousePos;
    std::function<void()> onAction;

public:
    Boton(const std::string& texto, sf::Vector2f posicion, const sf::Font& fuente, const sf::Texture& textura, std::function<void()> accion = nullptr);
    
    ~Boton() = default;

    void setSeleccionado(bool seleccionado);
    void actualizarHover(sf::Vector2f mousePos);
    bool procesarClick(sf::Vector2f mousePos);
    void dibujar(sf::RenderWindow& ventana);
};

#endif