#include "headers/PantallaNombreJugador.h"
#include "headers/Accesibilidad.h"
#include "headers/Fuente.h"
#include "headers/imagen.h"

#include <iostream>

PantallaNombreJugador::PantallaNombreJugador(float anchoVentana, float altoVentana) 
:   personaje(Fuente::getFuente(IDFuente::TituloPantalla), 3),
    textoIndicacion(Fuente::getFuente(IDFuente::TituloPantalla), "Ingrese su nombre:"),
    n_textoVisual(Fuente::getFuente(IDFuente::InputNombre), ""), 
    n_inputBuffer(""),
    logoTextura(Imagen::getImagen(IDImagen::LogoPequenio)),
    logoSprite(logoTextura)
{
    sf::FloatRect textoIndicacionBounds = textoIndicacion.getLocalBounds();
    sf::FloatRect textoVisualBounds = n_textoVisual.getGlobalBounds();
    sf::FloatRect inputBounds = textoIndicacion.getGlobalBounds();
    sf::FloatRect logoBounds = logoSprite.getGlobalBounds();

    sf::Color fondoBoxColor(0, 0, 0, 200);
    sf::Color inputBoxColor(10, 58, 94, 200);
    sf::Color inputColor(243, 210, 140, 255);
    
    fondoBox.setSize({anchoVentana / 2.f, altoVentana / 2.f});
    fondoBox.setOrigin({fondoBox.getSize().x / 2.f, fondoBox.getSize().y / 2.f});
    fondoBox.setPosition({anchoVentana / 2.f, altoVentana / 2.f});
    fondoBox.setFillColor(fondoBoxColor);
    fondoBox.setOutlineColor(inputColor);
    fondoBox.setOutlineThickness(3.f);

    logoSprite.setOrigin({logoBounds.size.x / 2.f, logoBounds.size.y / 2.f});
    logoSprite.setPosition({anchoVentana / 2.f, altoVentana / 2.f - textoIndicacionBounds.size.y - logoBounds.size.y});

    textoIndicacion.setOrigin({textoIndicacionBounds.size.x / 2.f, textoIndicacionBounds.size.y / 2.f});
    textoIndicacion.setPosition({anchoVentana / 2.f, (altoVentana / 2.f) - textoIndicacionBounds.size.y});

    inputBox.setSize({textoIndicacionBounds.size.x * 1.1f, textoIndicacionBounds.size.y * 1.25f});
    inputBox.setOrigin({inputBox.getSize().x / 2.f, 0.f});
    inputBox.setPosition({(anchoVentana / 2.f) + textoVisualBounds.size.x, (altoVentana + 50.f) / 2.f});
    inputBox.setFillColor(inputBoxColor);
    inputBox.setOutlineColor(inputColor);
    inputBox.setOutlineThickness(2.f);

    n_textoVisual.setPosition({(anchoVentana / 2.f) + textoVisualBounds.size.x, (altoVentana + 50.f) / 2.f});
    n_textoVisual.setOrigin({textoIndicacionBounds.size.x / 2.f, 0.f});
    n_textoVisual.setFillColor(sf::Color::White);

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
    ventana.draw(fondoBox);
    ventana.draw(logoSprite);
    ventana.draw(textoIndicacion);
    ventana.draw(inputBox);
    ventana.draw(n_textoVisual);
}