#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>

class Personaje : public sf::Drawable, public sf::Transformable {
private:
    int posicion;
    int vidas;
    int turnosPerdidos;
    int cantTirada;
    bool turnoExtra = false;
    sf::CircleShape mShape;

    sf::String nombre;
    sf::Font fuenteNombre;
    sf::Text etiquetaNombre;

public:
    Personaje();
    Personaje(const sf::Font& fuenteNombre, int nj, int vidasIniciales = 3);
    
    void moverACasilla(int nuevaPosicion);
    void modificarVidas(int cantidad);
    void agregarTurnoPerdido(int cantidad);
    void descontarTurnoPerdido();
    bool puedeJugar();
    bool estaVivo();
    
    sf::String getNombre() const;
    sf::String getposicionVisual() const;

    int getPosicion();
    int getVida();
    void otorgarTurnoExtra() ;
    bool tieneTurnoExtra() const ;
    void usarTurnoExtra() ;
    
    void setNombre(sf::String nuevoNombre);
    void setPosicionVisual(sf::Vector2f coordenadas);
void sumarTirada();
int getTirada();
void cargaPersonaje(int v, int p, int t);

~Personaje() = default;    

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif