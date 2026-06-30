#ifndef PANTALLA_NOMBRE_JUGADOR_H
#define PANTALLA_NOMBRE_JUGADOR_H

#include "Estado.h"
#include "Personaje.h"

class PantallaNombreJugador : public Estado {
private:
    Personaje personaje;

    sf::Text textoIndicacion;
    sf::Text n_textoVisual;
    sf::String n_inputBuffer;

public:
    PantallaNombreJugador(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif