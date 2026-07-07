#ifndef VISUAL_H
#define VISUAL_H

#include <map>

#include <SFML/Graphics.hpp>

enum class IDVisual {
    ColorAzul,
    ColorNaranjaClaro,
    ColorNaranjaOscuro,
    ColorNegroTransparente,
    FondoTablero,
    FondoVentana
};

class Visual {
private:
    sf::RectangleShape fondoTransparente;
    sf::Texture texturaFondoTablero;
    sf::Sprite spriteFondoTablero;
    
    sf::Color azul;
    sf::Color naranjaClaro;
    sf::Color naranjaOscuro;
    sf::Color negroSolido;
    sf::Color negrotransparente;
    
    std::map<IDVisual, sf::Texture> visuales;

public:
    Visual();

    void inicializarVisual();
    sf::Texture& getVisual(IDVisual id);
    void fondoVentanaTablero(sf::Vector2f posicion, sf::Texture& fondo);
    void fondoVentanaTransparente(sf::Vector2f tamanio, sf::Vector2f posicion, sf::Color colorFondo);
    void dibujar(sf::RenderWindow& ventana);
    ~Visual() = default;
};

#endif