#ifndef PANTALLA_NOMBRE_JUGADOR_H
#define PANTALLA_NOMBRE_JUGADOR_H

#include <SFML/Graphics.hpp>

#include "Estado.h"
#include "Partida.h"
#include "PartidaManager.h"
#include "Personaje.h"

class PantallaNombreJugador : public Estado {
private:
    Personaje personaje;
    Partida partida;

    sf::Text textoIndicacion;
    sf::Text n_textoVisual;
    sf::String n_inputBuffer;

    sf::RectangleShape fondoBox;
    sf::RectangleShape inputBox;
    
    sf::Texture logoTextura;
    sf::Sprite logoSprite;

    sf::Clock n_relojCursor;
    bool n_mostrarCursor;

public:
    PantallaNombreJugador(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif