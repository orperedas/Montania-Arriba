#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Boton.h"
#include <vector>
#include <optional>

class Menu {
private:
    int indiceSeleccionado;
    sf::Font fuente;
    sf::Texture texturaBoton;
    
    sf::Texture texturaFondo;
    std::optional<sf::Sprite> spriteFondo;

    std::vector<sf::Text> contenedorTitulo; 
    std::vector<sf::String> opciones;
    std::vector<Boton> botones;

public:
    Menu(float anchoVentana, float altoVentana, const sf::String& titulo, const std::vector<sf::String>& items);
    
    void moverArriba();
    void moverAbajo();
    int obtenerSeleccion() const;
    void dibujar(sf::RenderWindow& ventana);
};

#endif