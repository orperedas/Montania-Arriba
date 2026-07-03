#ifndef PANTALLA_DIFICULTAD_H
#define PANTALLA_DIFICULTAD_H

#include "Estado.h"
#include "Menu.h"
#include "Partida.h"

class PantallaDificultad : public Estado {
private:
    Menu menu;
    Partida& partida; 
public:
    PantallaDificultad(float anchoVentana, float altoVentana, Partida& p);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif