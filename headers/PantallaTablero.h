#ifndef PANTALLA_PRINCIPAL_H
#define PANTALLA_PRINCIPAL_H

#include "Estado.h"
#include "CasillaNormal.h"
#include "Castigo.h"
#include "Beneficio.h"
#include "Tablero.h"

class PantallaTablero : public Estado {
private:
    CasillaNormal normal;
    
public:
    PantallaTablero(float anchoVentana, float altoVentana);
    
    EstadoID manejarEventos(const sf::Event& evento) override;
    void actualizar() override;
    void dibujar(sf::RenderWindow& ventana) override;
};

#endif