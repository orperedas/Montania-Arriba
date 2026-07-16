#ifndef PANTALLA_ESTADISTICAS_H
#define PANTALLA_ESTADISTICAS_H

#include "estado.h"
#include "Visual.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PantallaEstadisticas : public Estado {
private:
    Visual visual;
    std::vector<std::string> textosRanking;
    std::vector<sf::RectangleShape> cajas;
    std::vector<sf::Text> textosSfml;

    sf::Text textoTitulo;
    sf::Text textoSalir;

public:
    PantallaEstadisticas(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif