#ifndef PANTALLA_TABLERO_H
#define PANTALLA_TABLERO_H

#include "Estado.h"
#include "Tablero.h"
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "Dado.h"

enum FaseTurno {
    ESPERANDO_TIRO,
    ANIMANDO_DADO
};
class PantallaTablero : public Estado {
private:
    Tablero tablero;
        Personaje personaje;
Dado dado;
    FaseTurno faseActual = ESPERANDO_TIRO;
    int casillasAAvanzar = 0;
public:
    PantallaTablero(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif