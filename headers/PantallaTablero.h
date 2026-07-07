#ifndef PANTALLA_TABLERO_H
#define PANTALLA_TABLERO_H

#include "Boton.h"
#include "Estado.h"
#include "Tablero.h"
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "Dado.h"
#include "ReglasJuego.h"
#include "PanelPersonaje.h"
#include "Partida.h"

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
    std::vector<PanelPersonaje> panelesJugadores; // Un panel por cada jugador
    Partida &partida;
    Personaje personaje;
    ReglasJuego reglas;
    Tablero tablero;
    
    EstadoID estadoPendiente = EstadoID::Ninguno;

    int posicionObjetivo;
    sf::Clock relojMovimiento;
    int casillasAAvanzar = 0;
    sf::RectangleShape fondoDado;
    sf::Texture texturaFondoTablero;
    sf::Sprite spriteFondoTablero;
    sf::Vector2f casillaInicial;

public:
    PantallaTablero(float anchoVentana, float altoVentana, Partida& p);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
    EstadoID getEstadoPendiente() const override { 
        return estadoPendiente; 
    }
};

#endif