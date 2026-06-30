#include "headers/PantallaNombreJugador.h"
#include "headers/Accesibilidad.h"
#include "headers/Fuente.h"
#include <iostream>

PantallaNombreJugador::PantallaNombreJugador(float anchoVentana, float altoVentana) 
:   personaje(Fuente::getFuente(IDFuente::TituloPantalla), 3),
textoIndicacion(Fuente::getFuente(IDFuente::TituloPantalla), "Ingrese su nombre:"),
      n_textoVisual(Fuente::getFuente(IDFuente::BotonMenu), ""), 
      n_inputBuffer("")
{
    textoIndicacion.setPosition({anchoVentana / 2.f - 200.f, altoVentana / 2.f - 100.f});
    n_textoVisual.setPosition({anchoVentana / 2.f - 200.f, altoVentana / 2.f});
    
    n_textoVisual.setFillColor(sf::Color::Yellow);

    Accesibilidad::hablar("Ingrese su nombre");
}

EstadoID PantallaNombreJugador::manejarEventos(const sf::Event& evento) {
    
    if (const auto* textoEvento = evento.getIf<sf::Event::TextEntered>()) {
        char32_t codepoint = textoEvento->unicode;

        if (codepoint == 8) { // Backspace (Borrar)
            if (!n_inputBuffer.isEmpty()) {
                n_inputBuffer.erase(n_inputBuffer.getSize() - 1);
            }
        }
        else if (codepoint >= 32 && codepoint < 128 && n_inputBuffer.getSize() < 12) {
            n_inputBuffer += codepoint;
        }

        n_textoVisual.setString(n_inputBuffer);
    }

    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            Accesibilidad::hablar("Volviendo al menú principal");
            return EstadoID::MenuPrincipal; 
        }

        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            if (!n_inputBuffer.isEmpty()) {
                personaje.setNombre(n_inputBuffer.toAnsiString());
                
                Accesibilidad::hablar("Nombre guardado. Seleccione dificultad.");
                return EstadoID::Dificultad; // Avanzamos de pantalla
            } else {
                Accesibilidad::hablar("El nombre no puede estar vacío.");
            }
        }   
    }

    return EstadoID::Ninguno;
}

void PantallaNombreJugador::actualizar() {
}

void PantallaNombreJugador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(textoIndicacion);
    ventana.draw(n_textoVisual);
}