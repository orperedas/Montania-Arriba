#include <iostream>

#include "headers/PantallaDerrota.h"
#include "headers/Accesibilidad.h"
#include "headers/Boton.h"
#include "headers/Sonido.h"

PantallaDerrota::PantallaDerrota(float anchoVentana, float altoVentana, Partida& p) 
    : menu(anchoVentana, altoVentana, "¡Perdieron todos!",{"Volver al menú principal","Salir del juego"}), partida(p) {
        Sonido::reproducir(IDSonido::Derrota);
}

EstadoID PantallaDerrota::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) menu.moverArriba();
        if (keyPressed->code == sf::Keyboard::Key::Down) menu.moverAbajo();
        
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            int seleccion = menu.obtenerSeleccion();
            
            if (seleccion == 0) {
                Accesibilidad::hablar("Volviendo al menú principal...");
            return EstadoID::MenuPrincipal; 
            }
            else if (seleccion == 1) {
                Accesibilidad::hablar("Saliendo...");
            return EstadoID::Salir; 
            }
            
        }
    }
    
    return EstadoID::Ninguno; 
}

void PantallaDerrota::actualizar() {
}

void PantallaDerrota::dibujar(sf::RenderWindow& ventana) {
    menu.dibujar(ventana);
}