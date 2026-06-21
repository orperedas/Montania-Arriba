#ifndef PANTALLA_VICTORIA_H
#define PANTALLA_VICTORIA_H

#include "Estado.h"
#include "Menu.h"

class PantallaVictoria : public Estado {
private:
    Menu menu;
    
public:
    PantallaVictoria(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif