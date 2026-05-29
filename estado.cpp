#include "headers/estado.h"
#include "headers/Accesibilidad.h"

void Estado::teclasGlobales(const sf::Event& evento) {

    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::A) {
            if (Accesibilidad::getCondicion()) {
                Accesibilidad::hablar("Estás desactivando la accesibilidad. No se proporcionará retroalimentación de voz.");
                Accesibilidad::setCondicion(false);
            } else {
                Accesibilidad::setCondicion(true);
                Accesibilidad::hablar("Accesibilidad activada. Se proporcionará retroalimentación de voz.");
            }
        }  
    }
}