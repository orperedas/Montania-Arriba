#include "headers/PantallaAccesibilidad.h"
#include "headers/Accesibilidad.h"

PantallaAccesibilidad::PantallaAccesibilidad(float anchoVentana, float altoVentana) 
    : menu(anchoVentana, altoVentana, L"¿Desea que el juego inicie con accesibilidad?",{L"Si, usar accesibilidad", L"No, gracias"}) {
}

EstadoID PantallaAccesibilidad::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) menu.moverArriba();
        if (keyPressed->code == sf::Keyboard::Key::Down) menu.moverAbajo();
        
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            int seleccion = menu.obtenerSeleccion();
            
            if (seleccion == 0) {
                Accesibilidad::hablar("Accesibilidad activada.");
            } else {
Accesibilidad::setCondicion(false);
            }
            
            return EstadoID::MenuPrincipal; 
        }
    }
    
    return EstadoID::Ninguno; 
}

void PantallaAccesibilidad::actualizar() {
}

void PantallaAccesibilidad::dibujar(sf::RenderWindow& ventana) {
    menu.dibujar(ventana);
}