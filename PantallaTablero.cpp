#include "headers/PantallaTablero.h"
#include "headers/Accesibilidad.h"

PantallaTablero::PantallaTablero(float anchoVentana, float altoVentana)
    : tablero(8), personaje(3) { 
}
    
EstadoID PantallaTablero::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            Accesibilidad::hablar("Volviendo al menú principal.");
            return EstadoID::MenuPrincipal; 
        }
        
    }
    
    return EstadoID::Ninguno;
}
    
void PantallaTablero::actualizar() {
    int casillaLogicaActual = personaje.getPosicion();

    Casilla* casillaActual = tablero.obtenerCasilla(casillaLogicaActual);

    if (casillaActual != nullptr) {
        sf::Vector2f coordenadasCasilla = casillaActual->getPosicionVisual();

        float centroX = coordenadasCasilla.x + 25.f;
        float centroY = coordenadasCasilla.y + 25.f;

        personaje.setPosicionVisual({centroX, centroY});
    }
}
    
void PantallaTablero::dibujar(sf::RenderWindow& ventana) {
    tablero.dibujar(ventana);
    ventana.draw(personaje);
}