#include "headers/PantallaCantidadJugadores.h"
#include "headers/Accesibilidad.h"

PantallaCantidadJugadores::PantallaCantidadJugadores(float anchoVentana, float altoVentana, Partida& p) 
    : menu(anchoVentana, altoVentana, "Elije la cantidad de jugadores que habrá en la partida", {"1", "2", "3", "4"}), 
      partida(p) 
{
}

EstadoID PantallaCantidadJugadores::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) menu.moverArriba();
        if (keyPressed->code == sf::Keyboard::Key::Down) menu.moverAbajo();
        
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            Accesibilidad::hablar("Volviendo al menú principal");
            return EstadoID::MenuPrincipal; 
        }        
        
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            int seleccion = menu.obtenerSeleccion();
            
            int cantidadJugadores = seleccion + 1; 
            
            partida.setCantidadJugadores(cantidadJugadores); 
            
            
            return EstadoID::Dificultad; 
        }
    } 

    return EstadoID::Ninguno; 
}

void PantallaCantidadJugadores::actualizar() {
}

void PantallaCantidadJugadores::dibujar(sf::RenderWindow& ventana) {
    menu.dibujar(ventana);
}