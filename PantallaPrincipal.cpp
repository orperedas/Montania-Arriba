#include "headers/PantallaPrincipal.h"
#include "headers/Accesibilidad.h"

PantallaPrincipal::PantallaPrincipal(float anchoVentana, float altoVentana) 
    : menu(anchoVentana, altoVentana, L"Subida al monte", {L"Iniciar juego", L"Cargar partida", L"Estadísticas", L"Créditos", L"Salir"}) {
}

EstadoID PantallaPrincipal::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) menu.moverArriba();
        if (keyPressed->code == sf::Keyboard::Key::Down) menu.moverAbajo();
        
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            int seleccion = menu.obtenerSeleccion();
            
            if (seleccion == 0) {
                Accesibilidad::hablar("Iniciando juego...");
            } else if (seleccion == 1) {
                Accesibilidad::hablar("Cargando partida...");
            } else if (seleccion == 2) {
                Accesibilidad::hablar("Viendo estadísticas...");
            } else if (seleccion == 3) {
                Accesibilidad::hablar("Viendo créditos...");
            } else if (seleccion == 4) {
                Accesibilidad::hablar("Saliendo...");
                return EstadoID::Salir;
            }
        }
    } 

    return EstadoID::Ninguno; 
}

void PantallaPrincipal::actualizar() {
    // Lógica de actualización
}

void PantallaPrincipal::dibujar(sf::RenderWindow& ventana) {
    menu.dibujar(ventana);
}