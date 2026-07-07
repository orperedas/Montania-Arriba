#ifndef MENU_H
#define MENU_H

#include <optional>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Boton.h"
#include "Visual.h"

class Menu {
private:
    Visual fondoBox;
    Visual visual;

    int indiceSeleccionado;
    sf::Texture texturaBoton;
    std::optional<sf::Sprite> spriteFondo;
    sf::Texture texturaLogo;
    sf::Sprite spriteLogo;
    
    sf::Font fuenteTitulo;
    sf::Font fuenteBoton;
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