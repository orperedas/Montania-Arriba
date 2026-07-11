#ifndef PANTALLA_CARGAR_PARTIDA_H
#define PANTALLA_CARGAR_PARTIDA_H

#include "estado.h"
#include "Menu.h"
#include "Partida.h"
#include <vector>
#include <string>

class PantallaCargarPartida : public Estado {
private:
    Partida& partida;
    std::vector<int> idsActivos;

    Menu menu;

    static std::vector<std::string> generarOpcionesMenu(std::vector<int>& idsCargados);

public:
    PantallaCargarPartida(float anchoVentana, float altoVentana, Partida& p);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif