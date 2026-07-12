#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>

class Personaje : public sf::Drawable, public sf::Transformable {
private:
    enum class Direccion { Arriba = 0, Izquierda = 1, Abajo = 2, Derecha = 3 };
    Direccion direccionActual;

    bool animando;
    bool turnoExtra = false;

    float tiempoProgreso;
    float tiempoAcumuladoAnimacion;
    float velocidadAnimacion;

    int cantTirada;
    int contadorCambios;
    int cuadroActual;
    int posicion;
    int turnosPerdidos;
    int vidas;

    sf::Vector2f posicionOrigen;
    sf::Vector2f posicionDestino;
    
    sf::Clock relojAnimacion;
    
    sf::String nombre;
    sf::Font fuenteNombre;
    sf::Text etiquetaNombre;

    sf::Texture personajeTextura;
    sf::Sprite personajeSprite;

public:
    Personaje();
    Personaje(const sf::Font& fuenteNombre, int nj, int vidasIniciales = 3);

    void comenzarMovimiento(sf::Vector2f coordenadasDestino);
    
    void moverACasilla(int nuevaPosicion);
    void modificarVidas(int cantidad);
    void agregarTurnoPerdido(int cantidad);
    void descontarTurnoPerdido();
    bool puedeJugar();
    bool estaVivo();
    
    sf::String getNombre() const;
    sf::String getposicionVisual() const;
    sf::Texture& getTexture();

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
    bool estaAnimando() const;

    void actualizar();

~Personaje() = default;    

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif