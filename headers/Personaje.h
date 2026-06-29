#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>

class Personaje : public sf::Drawable, public sf::Transformable {
private:
    int posicion;
    int vidas;
    int turnosPerdidos;

    sf::CircleShape mShape;

    sf::String nombre;
    sf::Font fuenteNombre;
    sf::Text etiquetaNombre;

public:
    Personaje(int vidasIniciales = 3);

    sf::String getNombre() const { return nombre; };

    void moverACasilla(int nuevaPosicion);
    void setPosicionVisual(sf::Vector2f coordenadas);

    void modificarVidas(int cantidad);
    void agregarTurnoPerdido(int cantidad);
    void descontarTurnoPerdido();

    bool puedeJugar();
    bool estaVivo();
    int getPosicion();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif