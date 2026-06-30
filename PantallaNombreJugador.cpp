#include <iostream>
#include <String>

#include "headers/PantallaNombreJugador.h"
#include "headers/Accesibilidad.h"
#include "headers/Estado.h"
#include "headers/Fuente.h"
#include "headers/Personaje.h"

PantallaNombreJugador::PantallaNombreJugador(float anchoVentana, float altoVentana) 
:   personaje(Fuente::getFuente(IDFuente::TituloPantalla), 3),
    n_textoVisual(Fuente::getFuente(IDFuente::BotonMenu), ""), 
    n_inputBuffer(std::string("¿Ingrese su nombre:"))
    {
}


EstadoID PantallaNombreJugador::manejarEventos(const sf::Event& evento){
    
    if (const auto* textoEvento = evento.getIf<sf::Event::TextEntered>()){
        char32_t codepoint = textoEvento->unicode;

        if (codepoint == 8){
            if(!n_inputBuffer.isEmpty()){
                n_inputBuffer.erase(n_inputBuffer.getSize() - 1);
            }
        }
        else if (codepoint == 13 || codepoint == 10){
            if(!n_inputBuffer.isEmpty()){
                personaje.setNombre(n_inputBuffer);
            }
        }
        else if (codepoint < 128 && n_inputBuffer.getSize() < 12) {
            n_inputBuffer += codepoint;
        }

        n_textoVisual.setString(n_inputBuffer);

        if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
    Accesibilidad::hablar("Volviendo al menú principal");
                return EstadoID::MenuPrincipal; 
            }

            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                return EstadoID::Dificultad;
            }   
        }
    }

    return EstadoID::Ninguno;
}


void PantallaNombreJugador::actualizar(){


}


void PantallaNombreJugador::dibujar(sf::RenderWindow& ventana){
    ventana.draw(n_textoVisual);
    //ventana.draw(n_inputBuffer);
}