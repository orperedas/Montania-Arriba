#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
private:
    std::vector<sf::Text> contenedorTitulo; 
    std::vector<sf::String> opciones;
    std::vector<sf::Text> textosSFML;
    int indiceSeleccionado;
    sf::Font fuente;

public:
    Menu(float anchoVentana, float altoVentana, const sf::String& titulo, const std::vector<sf::String>& items);
    
    void moverArriba();
    void moverAbajo();
    int obtenerSeleccion() const;
    void dibujar(sf::RenderWindow& ventana);
};

#endif