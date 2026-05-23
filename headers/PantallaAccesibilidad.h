#ifndef PANTALLA_ACCESIBILIDAD_H
#define PANTALLA_ACCESIBILIDAD_H

#include "Estado.h"
#include "Menu.h"

class PantallaAccesibilidad : public Estado {
private:
    Menu menu;

public:
    PantallaAccesibilidad(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif