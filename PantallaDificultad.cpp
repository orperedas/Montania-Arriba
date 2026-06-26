#include "headers/PantallaDificultad.h"
#include "headers/Accesibilidad.h"

PantallaDificultad::PantallaDificultad(float anchoVentana, float altoVentana, Dificultad& di) 
    : menu(anchoVentana, altoVentana, "Elije la dificultad de la partida", {"Fácil","Medio", "Difícil"}), dificultadGlobal(di) {
}

EstadoID PantallaDificultad::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) menu.moverArriba();
        if (keyPressed->code == sf::Keyboard::Key::Down) menu.moverAbajo();
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
Accesibilidad::hablar("Volviendo al menú principal");
            return EstadoID::MenuPrincipal; 
        }        
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            int seleccion = menu.obtenerSeleccion();
            
            if (seleccion == 0) {
                dificultadGlobal = Dificultad::FACIL;
                Accesibilidad::hablar("Iniciando en dificultad Fácil.");
            } else if (seleccion == 1) {
                dificultadGlobal = Dificultad::MEDIO;
                Accesibilidad::hablar("Iniciando en dificultad Medio.");
            } else if (seleccion == 2) {
                dificultadGlobal = Dificultad::DIFICIL;
                Accesibilidad::hablar("Iniciando en dificultad Difícil.");
            }            
            
            return EstadoID::Jugando; 
        }
    } 

    return EstadoID::Ninguno; 
}

void  PantallaDificultad::actualizar() {
    // Lógica de actualización
}

void PantallaDificultad::dibujar(sf::RenderWindow& ventana) {
    menu.dibujar(ventana);
}