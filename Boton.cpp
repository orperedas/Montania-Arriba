#include "headers/Boton.h"

Boton::Boton(const sf::String& texto, sf::Vector2f posicion, const sf::Font& fuente, const sf::Texture& textura) 
    : posicionBoton(posicion), 
      spriteBoton(textura), 
      etiquetaBoton(fuente) 
{
    spriteBoton.setPosition(posicionBoton);
    spriteBoton.setTextureRect({{0, 0}, {257, 64}});

    etiquetaBoton.setString(texto);
    etiquetaBoton.setCharacterSize(24);
    etiquetaBoton.setPosition({posicionBoton.x + 20.f, posicionBoton.y + 10.f});
    
    setSeleccionado(false); 
}

void Boton::setSeleccionado(bool seleccionado) {
    if (seleccionado) {
        spriteBoton.setTextureRect({{258, 0}, {518 , 64}});
        etiquetaBoton.setFillColor(sf::Color::Yellow);
    } else {
        spriteBoton.setTextureRect({{0, 0}, {257, 64}});
        etiquetaBoton.setFillColor(sf::Color::White);
    }
}

void Boton::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteBoton);
    ventana.draw(etiquetaBoton);
}