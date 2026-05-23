#ifndef ESTADO_H
#define ESTADO_H

#include <SFML/Graphics.hpp>

enum class EstadoID {
    Ninguno,
    Accesibilidad,
    MenuPrincipal,
    Jugando,
    Salir
};

class Estado {
public:
    virtual ~Estado() = default;
    
    virtual EstadoID manejarEventos(const sf::Event& evento) = 0;
    virtual void actualizar() = 0;
    virtual void dibujar(sf::RenderWindow& ventana) = 0;
};

#endif