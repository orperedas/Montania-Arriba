#ifndef PANEL_PERSONAJE_H
#define PANEL_PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Personaje.h"
#include "Visual.h"

class PanelPersonaje : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape fondo;
    sf::Font fuente;
    sf::Text textoNombre;
    sf::Text textoPosicion;
    sf::Text textoVidas;
    sf::Texture texturaCorazon;
    sf::Texture texturaPersonaje;
    sf::Sprite spritePersonaje;
    std::vector<sf::Sprite> corazones;

    Visual visual;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    PanelPersonaje(const sf::Font& fuente, const sf::Texture& texturaCorazonUI, const sf::Texture& texturaJugador, sf::Vector2f posicionPantalla);

    void actualizarDatos(Personaje& personaje);
    void setActivo(bool activo);
};

#endif