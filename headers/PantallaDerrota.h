#ifndef PANTALLA_DERROTA_H
#define PANTALLA_DERROTA_H

#include "Estado.h"
#include "Menu.h"
#include "Partida.h"

class PantallaDerrota: public Estado {
private:
    Menu menu;
    Partida& partida;
public:
PantallaDerrota(float anchoVentana, float altoVentana, Partida& p);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif