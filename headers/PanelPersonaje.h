#ifndef PANEL_PERSONAJE_H
#define PANEL_PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Personaje.h"

class PanelPersonaje : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape fondo;
    
    sf::Text textoNombre;
    sf::Text textoPosicion;
    
    sf::Texture texturaCorazon;
    std::vector<sf::Sprite> corazones;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    PanelPersonaje(const sf::Font& fuente, const sf::Texture& texturaCorazonUI, sf::Vector2f posicionPantalla);

    void actualizarDatos(Personaje& personaje);
};

#endif