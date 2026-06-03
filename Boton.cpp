#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "headers/Accesibilidad.h"
#include "headers/Boton.h"

void Boton::menuBoton(const sf::String& texto, sf::Vector2f posicion) {
    sf::Texture texturaBoton;
    if (!texturaBoton.loadFromFile("imagenes/menu_boton.png")) {
        std::cerr << "Error al cargar la textura del botón." << std::endl;
    }

    sf::Font fuenteBoton;
    if (!fuenteBoton.openFromFile("fuentes/sansation.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
    }

    spriteBoton.setTexture(texturaBoton);
    spriteBoton.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(texturaBoton.getSize().x), static_cast<int>(texturaBoton.getSize().y)}));
    posicionBoton = posicion;
    spriteBoton.setPosition(posicionBoton);

    etiquetaBoton.setFont(fuenteBoton);
    etiquetaBoton.setString(texto);
    etiquetaBoton.setCharacterSize(24);
    etiquetaBoton.setFillColor(sf::Color::White);
    etiquetaBoton.setPosition(sf::Vector2f(posicionBoton.x + 10.f, posicionBoton.y + 10.f));
}

void Boton::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteBoton);
    ventana.draw(etiquetaBoton);
}