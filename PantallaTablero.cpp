#include "headers/PantallaTablero.h"
#include "headers/Accesibilidad.h"
#include "headers/Fuente.h"
#include "headers/Sonido.h"
#include "headers/Estado.h"

PantallaTablero::PantallaTablero(float anchoVentana, float altoVentana, Dificultad difElegida)
    : tablero(8), personaje(Fuente::getFuente(IDFuente::TituloPantalla), 3), dado({580.f,660.f}), fondoDado(), reglas(difElegida, 64){ 
        /*
        fondoDado.setFillColor(sf::Color::Black);
        fondoDado.setSize({200.f, 80.f});
        fondoDado.setPosition({420.f, 610.f});
        */

        personaje.moverACasilla(-1);
}

EstadoID PantallaTablero::manejarEventos(const sf::Event& evento) {
    if (estadoPendiente != EstadoID::Ninguno) {
        return estadoPendiente;
    }
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::N) {
Accesibilidad::hablar("Estás en la casilla " + std::to_string(personaje.getPosicion()));
            Accesibilidad::hablar(personaje.getNombre());
        }
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
            posicionObjetivo = reglas.calcularDestino(personaje.getPosicion(), casillasAAvanzar);
            
            faseActual = MOVIENDO_PERSONAJE; 
            relojMovimiento.restart(); 
        }
    }
    
    else if (faseActual == MOVIENDO_PERSONAJE) {
        
        if (relojMovimiento.getElapsedTime() >= sf::seconds(0.6f)) {
            
            int posActual = personaje.getPosicion();    

            if (posActual < posicionObjetivo) {
                Sonido::reproducir(IDSonido::paso);
                personaje.moverACasilla(posActual + 1);
            } 
            else if (posActual > posicionObjetivo) {
                Sonido::reproducir(IDSonido::pasoatras);
                personaje.moverACasilla(posActual - 1);
            } 
            else {
                int posAntes = personaje.getPosicion();
                
                Casilla* casillaActual = tablero.obtenerCasilla(posActual);
                if (casillaActual != nullptr) {
                    casillaActual->consecuencia((rand() % 3) + 1, personaje);
                }

                int posDespues = personaje.getPosicion();

                if (posAntes != posDespues) {
                    personaje.moverACasilla(posAntes); 
                    posicionObjetivo = posDespues;
                } else {
                    EstadoPartida estado = reglas.evaluarEstadoDelJuego(personaje);

                    if (estado == EstadoPartida::VICTORIA) {
                        estadoPendiente = EstadoID::Victoria;
                    } else if (estado == EstadoPartida::DERROTA) {
                        Accesibilidad::hablar("Te has quedado sin vidas. Fin del juego.");
                    }
                    
                    faseActual = ESPERANDO_TIRO; 
                }
            }
            
            relojMovimiento.restart();
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