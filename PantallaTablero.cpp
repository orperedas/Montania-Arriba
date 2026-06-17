#include "headers/PantallaTablero.h"
#include "headers/Accesibilidad.h"
#include "headers/Sonido.h"

PantallaTablero::PantallaTablero(float anchoVentana, float altoVentana, Dificultad difElegida)
    : tablero(8), personaje(3), dado({580.f,660.f}), fondoDado(), reglas(difElegida, 64){ 
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

    // --- FASE 1: DADO TERMINA DE GIRAR ---
    if (faseActual == ANIMANDO_DADO) {
        if (!dado.estaAnimando()) {
            // Calculamos el destino final según la dificultad (ReglasJuego)
            posicionObjetivo = reglas.calcularDestino(personaje.getPosicion(), casillasAAvanzar);
            
            // Pasamos a la fase de movimiento animado
            faseActual = MOVIENDO_PERSONAJE; 
            relojMovimiento.restart(); 
        }
    }
    
    // --- FASE 2: CAMINANDO PASO A PASO ---
    else if (faseActual == MOVIENDO_PERSONAJE) {
        
        // Control de velocidad: 0.2f segundos entre cada paso
        if (relojMovimiento.getElapsedTime() >= sf::seconds(0.6f)) {
            
            int posActual = personaje.getPosicion();

            // Avanza o retrocede de a uno hasta llegar a la meta
            if (posActual < posicionObjetivo) {
Sonido::reproducir(IDSonido::paso);
                personaje.moverACasilla(posActual + 1);
            } 
            else if (posActual > posicionObjetivo) {
Sonido::reproducir(IDSonido::paso);
                personaje.moverACasilla(posActual - 1);
            } 
            else {
                // LLEGÓ A LA META (posActual == posicionObjetivo)
                int posAntes = personaje.getPosicion();
                
                // Ejecutamos la consecuencia de la casilla actual
                Casilla* casillaActual = tablero.obtenerCasilla(posActual);
                if (casillaActual != nullptr) {
                    casillaActual->consecuencia((rand() % 3) + 1, personaje);
                }

                int posDespues = personaje.getPosicion();

                // ¿La consecuencia nos teletransportó? (ej. castigo que retrocede)
                if (posAntes != posDespues) {
                    // Deshacemos el salto instantáneo y fijamos el nuevo objetivo
                    personaje.moverACasilla(posAntes); 
                    posicionObjetivo = posDespues;
                } else {
                    // Si no hubo salto extra, evaluamos fin de juego
                    EstadoPartida estado = reglas.evaluarEstadoDelJuego(personaje);

                    if (estado == EstadoPartida::VICTORIA) {
                        Accesibilidad::hablar("¡Llegaste a la cima! Has completado el recorrido.");
                    } else if (estado == EstadoPartida::DERROTA) {
                        Accesibilidad::hablar("Te has quedado sin vidas. Fin del juego.");
                    }
                    
                    // Finalizamos el turno volviendo a esperar
                    faseActual = ESPERANDO_TIRO; 
                }
            }
            relojMovimiento.restart();
        }
    }

    // --- ACTUALIZACIÓN VISUAL ---
    Casilla* casillaVisual = tablero.obtenerCasilla(personaje.getPosicion());
    if (casillaVisual != nullptr) {
        sf::Vector2f coord = casillaVisual->getPosicionVisual();
        personaje.setPosicionVisual({coord.x + 25.f, coord.y + 25.f});
    }
}
/*
void PantallaTablero::actualizar() {
    dado.actualizar();

    if (faseActual == ANIMANDO_DADO) {
        
        if (!dado.estaAnimando()) {
            
    // El cerebro se encarga de todo el turno
    reglas.jugarTurno(personaje, tablero, casillasAAvanzar);
    faseActual = ESPERANDO_TIRO;
        
    // Preguntamos si el juego terminó
    EstadoPartida estado = reglas.evaluarEstadoDelJuego(personaje);

    if (estado == EstadoPartida::VICTORIA) {
        // Lógica para volver al menú o ir a pantalla de victoria
        return; // o cambiar de estado
    } else if (estado == EstadoPartida::DERROTA) {
        Accesibilidad::hablar("Te has quedado sin vidas. Fin del juego.");
        // Lógica para Game Over
        return;
    }
        }
    }

    Casilla* casillaVisual = tablero.obtenerCasilla(personaje.getPosicion());
    if (casillaVisual != nullptr) {
        sf::Vector2f coord = casillaVisual->getPosicionVisual();
        personaje.setPosicionVisual({coord.x + 25.f, coord.y + 25.f});
    }
}   
*/
void PantallaTablero::dibujar(sf::RenderWindow& ventana) {
    tablero.dibujar(ventana);
    ventana.draw(personaje);
    //ventana.draw(fondoDado);
    dado.draw(ventana);
}