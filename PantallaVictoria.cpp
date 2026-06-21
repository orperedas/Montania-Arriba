#include <iostream>

#include "headers/PantallaVictoria.h"
#include "headers/Accesibilidad.h"
#include "headers/Boton.h"
#include "headers/Sonido.h"

PantallaVictoria::PantallaVictoria(float anchoVentana, float altoVentana) 
    : menu(anchoVentana, altoVentana, "¡Felicidades! ganaste la partida!",{"Volver al menú principal","Salir del juego"}) {
        Sonido::reproducir(IDSonido::Victoria);
}

EstadoID PantallaVictoria::manejarEventos(const sf::Event& evento) {
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

void PantallaVictoria::actualizar() {
}

void PantallaVictoria::dibujar(sf::RenderWindow& ventana) {
    menu.dibujar(ventana);
}