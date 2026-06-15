#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Boton.h"
#include <vector>
#include <optional>
#include <string>

class Menu {
private:
    int indiceSeleccionado;
    sf::Font fuente;
    sf::Texture texturaBoton;
    std::optional<sf::Sprite> spriteFondo;

    std::vector<sf::Text> contenedorTitulo; 
    std::vector<std::string> opciones;
    std::vector<Boton> botones;

public:
    Menu(float anchoVentana, float altoVentana, const std::string& titulo, const std::vector<std::string>& items);
    
    void moverArriba();
    void moverAbajo();
    int obtenerSeleccion() const;
    void dibujar(sf::RenderWindow& ventana);
};

#endif