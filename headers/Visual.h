#ifndef VISUAL_H
#define VISUAL_H

#include <map>

#include <SFML/Graphics.hpp>

enum class IDVisual {
    Azul_Solido,
    Blanco_Solido,
    GrisClaro_Solido,
    GrisMedio_Solido,
    GrisOscuro_Solido,
    NaranjaClaro_Solido,
    NaranjaOscuro_Solido,
    Negro_Transparente,

    FondoTablero,
    FondoVentana
};

class Visual {
private:
    sf::RectangleShape fondoTransparente;
    sf::Texture texturaFondoTablero;
    sf::Sprite spriteFondoTablero;
    
    std::map<IDVisual, sf::Color> colores;
    std::map<IDVisual, sf::Texture> visuales;
    
public:
    Visual();

    sf::Texture& getVisual(IDVisual id);
    sf::Color getColor(IDVisual id);

    void inicializarVisual();
    void fondoVentanaTablero(sf::Vector2f tamanio, sf::Vector2f posicion);
    void fondoVentanaTransparente(sf::Vector2f tamanio, sf::Vector2f posicion, sf::Color colorFondo);
    void dibujar(sf::RenderWindow& ventana);
    
    ~Visual() = default;
};

#endif