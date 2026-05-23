#ifndef PANTALLA_PRINCIPAL_H
#define PANTALLA_PRINCIPAL_H

#include "Estado.h"
#include "Menu.h"

class PantallaPrincipal : public Estado {
private:
    Menu menu;

public:
    PantallaPrincipal(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif