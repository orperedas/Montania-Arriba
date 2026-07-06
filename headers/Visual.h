#ifndef VISUAL_H
#define VISUAL_H

#include <map>

#include <SFML/Graphics.hpp>

enum class IDVisual {
    ColorNegroTransparente,
    ColorAzul,
    ColorNaranjaClaro,
    ColorNaranjaOscuro,
    FondoTablero,
    FondoVentana
};

class Visual {
private:
    static sf::RectangleShape fondoVentanaTransparente;
    static const sf::Texture texturaFondoTablero;
    static sf::Sprite spriteFondoTablero;
    
    static const sf::Color azul;
    static const sf::Color naranjaClaro;
    static const sf::Color naranjaOscuro;
    static const sf::Color negroSolido;
    static const sf::Color negrotransparente;
    
    static std::map<IDVisual, sf::Texture> visuales;

public:
    Visual();

    static void inicializarVisual();
    static const sf::Texture& getVisual(IDVisual id);
    static void ventanafondoTablero(sf::Vector2f posicion, sf::Texture& fondo);
    static void ventanaFondoTransparente(sf::Vector2f tamanio, sf::Vector2f posicion, sf::Color colorFondo);
    ~Visual() = default;
};

#endif