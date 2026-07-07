#ifndef PANTALLA_CANTIDAD_JUGADORES_H
#define PANTALLA_CANTIDAD_JUGADORES_H

#include "Estado.h"
#include "Menu.h"
#include "Partida.h"

class PantallaCantidadJugadores: public Estado {
private:
    Menu menu;
    Partida& partida; 
public:
    PantallaCantidadJugadores(float anchoVentana, float altoVentana, Partida& p);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif