#include "headers/PantallaTablero.h"
#include "headers/Accesibilidad.h"

PantallaTablero::PantallaTablero(float anchoVentana, float altoVentana)
    : tablero(8), personaje(3), dado({580.f,660.f}), fondoDado(){ 
        /*
        fondoDado.setFillColor(sf::Color::Black);
        fondoDado.setSize({200.f, 80.f});
        fondoDado.setPosition({420.f, 610.f});
        */
}

EstadoID PantallaTablero::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            return EstadoID::MenuPrincipal; 
        }
        
        if (keyPressed->code == sf::Keyboard::Key::Space && faseActual == ESPERANDO_TIRO) {
            
            if (personaje.puedeJugar()) {
                casillasAAvanzar = dado.tirar();
                faseActual = ANIMANDO_DADO;
            } else {
                personaje.descontarTurnoPerdido();
                Accesibilidad::hablar("Pierdes este turno.");
            }
        }
    }
    
    return EstadoID::Ninguno;
}

void PantallaTablero::actualizar() {
    dado.actualizar();

    if (faseActual == ANIMANDO_DADO) {
        
        if (!dado.estaAnimando()) {
            
            int nuevaPosicion = personaje.getPosicion() + casillasAAvanzar;
            personaje.moverACasilla(nuevaPosicion);

            Casilla* casillaActual = tablero.obtenerCasilla(nuevaPosicion);
            if (casillaActual != nullptr) {
                casillaActual->consecuencia((rand() % 3) + 1, personaje);
            }

            faseActual = ESPERANDO_TIRO;
        }
    }

    Casilla* casillaVisual = tablero.obtenerCasilla(personaje.getPosicion());
    if (casillaVisual != nullptr) {
        sf::Vector2f coord = casillaVisual->getPosicionVisual();
        personaje.setPosicionVisual({coord.x + 25.f, coord.y + 25.f});
    }
}   
void PantallaTablero::dibujar(sf::RenderWindow& ventana) {
    tablero.dibujar(ventana);
    ventana.draw(personaje);
    //ventana.draw(fondoDado);
    dado.draw(ventana);
}