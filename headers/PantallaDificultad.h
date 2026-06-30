#ifndef PANTALLA_DIFICULTAD_H
#define PANTALLA_DIFICULTAD_H

#include "Estado.h"
#include "Menu.h"
#include "ReglasJuego.h"

class PantallaDificultad : public Estado {
private:
    Menu menu;
    Dificultad& dificultadGlobal; 
public:
    PantallaDificultad(float anchoVentana, float altoVentana, Dificultad& di);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif