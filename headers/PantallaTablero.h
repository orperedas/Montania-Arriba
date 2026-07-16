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
#include "Visual.h"

enum FaseTurno {
    ANIMANDO_DADO,
    ANIMANDO_PERSONAJE,
    ESPERANDO_TIRO,
    MOVIENDO_PERSONAJE
};

class PantallaTablero : public Estado, public sf::Drawable, public sf::Transformable {
private:
    Dado dado;
    EstadoID estadoPendiente = EstadoID::Ninguno;
    Partida &partida;
    FaseTurno faseActual = ESPERANDO_TIRO;
    ReglasJuego reglas;
    Tablero tablero;
    Visual visual;
    
    int turnoActual; 
    int posicionObjetivo;
    int casillasAAvanzar = 0;
    bool posicionInicialEstablecida = false;
    bool primerPaso = false;
    
    std::vector<Personaje> jugadores; 
    std::vector<PanelPersonaje> panelesJugadores;
    
    sf::Clock relojMovimiento;
    sf::RectangleShape fondoDado;
    sf::RectangleShape fondoOscuro;
    sf::Vector2f casillaInicial;
    sf::RectangleShape cajaMensaje;
    sf::Text textoMensaje;
    sf::Clock relojMensaje;
    bool mostrarMensaje = false;
    void guardarDatosTablero(bool finalizada);

public:
    PantallaTablero(float anchoVentana, float altoVentana, Partida& p, bool carga = false);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    EstadoID getEstadoPendiente() const override { 
        return estadoPendiente; 
    }
};

#endif