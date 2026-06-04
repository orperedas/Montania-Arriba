#include "headers/PantallaTablero.h"
#include "headers/Accesibilidad.h"
#include "headers/Casilla.h"
#include "headers/CasillaNormal.h"
#include "headers/Castigo.h"
#include "headers/Beneficio.h"
#include "headers/Tablero.h"

PantallaTablero::PantallaTablero(float anchoVentana, float altoVentana)
    : tablerro(anchoVentana, altoVentana) {}
    
EstadoID PantallaTablero::manejarEventos(const sf::Event& evento){


}
    
void PantallaTablero::actualizar() {
    
};
    
void PantallaTablero::dibujar(sf::RenderWindow& ventana) {
    tablerro.dibujar(ventana);
};