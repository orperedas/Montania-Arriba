#ifndef PANTALLA_ESTADISTICAS_H
#define PANTALLA_ESTADISTICAS_H

#include "estado.h"
#include "Menu.h"
#include <vector>
#include <string>

class PantallaEstadisticas : public Estado {
private:
    Menu menu;

    static std::vector<std::string> generarOpcionesRanking();

public:
    PantallaEstadisticas(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif