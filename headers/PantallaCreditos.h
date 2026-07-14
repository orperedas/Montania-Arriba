#ifndef PANTALLA_CREDITOS_H
#define PANTALLA_CREDITOS_H

#include "estado.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PantallaCreditos : public Estado {
private:
    std::vector<std::string> textosCreditos;
    std::vector<sf::RectangleShape> cajas;
    std::vector<sf::Text> textosSfml;

    sf::Text textoTitulo;
    sf::Text textoSalir;

public:
    PantallaCreditos(float anchoVentana, float altoVentana);

    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif