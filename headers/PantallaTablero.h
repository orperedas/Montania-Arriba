#ifndef PANTALLA_TABLERO_H
#define PANTALLA_TABLERO_H

#include "Boton.h"
#include "Estado.h"
#include "Tablero.h"
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "Dado.h"
#include "ReglasJuego.h"

enum FaseTurno {
    ESPERANDO_TIRO,
    ANIMANDO_DADO,
    MOVIENDO_PERSONAJE
};
class PantallaTablero : public Estado {
private:
    Tablero tablero;
    Personaje personaje;
    Dado dado;
    FaseTurno faseActual = ESPERANDO_TIRO;
    int posicionObjetivo;
    sf::Clock relojMovimiento;
    ReglasJuego reglas;
    int casillasAAvanzar = 0;
    sf::RectangleShape fondoDado;
    sf::RectangleShape fondoOscuro;
    EstadoID estadoPendiente = EstadoID::Ninguno;
    public:
    PantallaTablero(float anchoVentana, float altoVentana, Dificultad difElegida);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
    EstadoID getEstadoPendiente() const override { 
        return estadoPendiente; 
    }
};

#endif