#include "headers/Accesibilidad.h"
#include "headers/Fuente.h"
#include "headers/Sonido.h"
#include "headers/Estado.h"
#include "headers/Imagen.h"
#include "headers/PantallaTablero.h"
#include "headers/PartidaArchivo.h"
#include "headers/Visual.h"
#include "headers/PartidaManager.h"


PantallaTablero::PantallaTablero(float anchoVentana, float altoVentana, Partida& p)
  : tablero(8),
    dado({anchoVentana / 2.f, altoVentana / 2.f}),
    fondoDado(),
    reglas(static_cast<Dificultad>(p.getDificultad()), 64),
    partida(p),
    turnoActual(0)
{ 
    visual.fondoVentanaTablero(
        {anchoVentana / 2.f, altoVentana / 2.f},
        {anchoVentana / 2.f, altoVentana / 2.f} );

    int cantidad = partida.getCantidadJugadores();
    float espacioVertical = 120.f;

    for (int i = 0; i < cantidad; ++i) {
        Personaje nuevoPersonaje(Fuente::getFuente(IDFuente::TituloPantalla), i);
        nuevoPersonaje.setNombre(partida.getNombreJugador(i)); 
        nuevoPersonaje.moverACasilla(-1);
        jugadores.push_back(nuevoPersonaje);

        PanelPersonaje panel(Fuente::getFuente(IDFuente::TituloPantalla), 
                             Imagen::getImagen(IDImagen::Corazon), 
                             {anchoVentana - 450.f, 120.f + (i * espacioVertical)});
        panelesJugadores.push_back(panel);
    }
Accesibilidad::hablar("Comienza tirando " + jugadores[turnoActual].getNombre().toAnsiString());
}

EstadoID PantallaTablero::manejarEventos(const sf::Event& evento) {
    if (estadoPendiente != EstadoID::Ninguno) {
        return estadoPendiente;
    }
    
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::N) {
            Accesibilidad::hablar(jugadores[turnoActual].getNombre().toAnsiString() + 
                      ", te encuentras en la casilla " + 
                      std::to_string(jugadores[turnoActual].getPosicion() + 1));
        }
        
        if (keyPressed->code == sf::Keyboard::Key::V) {
            Accesibilidad::hablar("Tenés " + std::to_string(jugadores[turnoActual].getVida()) + " vidas");
        }
        
        
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            return EstadoID::MenuPrincipal; 
        }
        
        if (keyPressed->code == sf::Keyboard::Key::Space && faseActual == ESPERANDO_TIRO) {
            if (jugadores[turnoActual].puedeJugar()) {
                casillasAAvanzar = dado.tirar();
                faseActual = ANIMANDO_DADO;
            }
        }
    }
    
    return EstadoID::Ninguno;
}


void PantallaTablero::actualizar() {
    dado.actualizar();

    if (faseActual == ANIMANDO_DADO) {
        if (!dado.estaAnimando()) {
            posicionObjetivo = reglas.calcularDestino(jugadores[turnoActual].getPosicion(), casillasAAvanzar);
            faseActual = MOVIENDO_PERSONAJE; 
            relojMovimiento.restart(); 
        }
    }
    else if (faseActual == MOVIENDO_PERSONAJE) {   
        if (relojMovimiento.getElapsedTime() >= sf::seconds(0.5f)) {      
            int posActual = jugadores[turnoActual].getPosicion();    

            if (posActual < posicionObjetivo) {
                Sonido::reproducir(IDSonido::paso);
                jugadores[turnoActual].moverACasilla(posActual + 1);
            } 
            else if (posActual > posicionObjetivo) {
                Sonido::reproducir(IDSonido::pasoatras);
                jugadores[turnoActual].moverACasilla(posActual - 1);
            } 
            else {
                int posAntes = jugadores[turnoActual].getPosicion();
                
                Casilla* casillaActual = tablero.obtenerCasilla(posActual);
                
                if (casillaActual != nullptr) {
                    casillaActual->consecuencia((rand() % 3) + 1, jugadores[turnoActual]);
                }

                int posDespues = jugadores[turnoActual].getPosicion();

                if (posAntes != posDespues) {
                    jugadores[turnoActual].moverACasilla(posAntes); 
                    posicionObjetivo = posDespues;
                } else {
                    EstadoPartida estado = reglas.evaluarEstadoDelJuego(jugadores[turnoActual]);

                    if (estado == EstadoPartida::VICTORIA) {
                        
                        for (size_t i = 0; i < jugadores.size(); ++i) {
                            partida.setVidaJugador(i, jugadores[i].getVida());
                            partida.setPosicionJugador(i, jugadores[i].getPosicion());
                            partida.setGanador(i, (i == turnoActual)); // Solo es true si es su turno
                        }

PartidaManager manager(partida); 
manager.guardarPartida();
                        Accesibilidad::hablar("¡Victoria de " + jugadores[turnoActual].getNombre().toAnsiString() + "!");
                        estadoPendiente = EstadoID::Victoria;
                        
                    } else if (estado == EstadoPartida::DERROTA) {
    Accesibilidad::hablar("¡Oh no! " + jugadores[turnoActual].getNombre().toAnsiString() + " se ha quedado sin vidas y queda eliminado.");
    bool todosMuertos = true;
    for (auto& jugador : jugadores) {
        if (jugador.estaVivo()) { 
            todosMuertos = false;
            break; 
        }
    }

    if (todosMuertos) {
        Accesibilidad::hablar("Todos los jugadores han sido eliminados. Fin del juego.");
        estadoPendiente = EstadoID::Derrota; 
    }
                    }
                    
                    if (estadoPendiente == EstadoID::Ninguno) {
                        if (jugadores[turnoActual].tieneTurnoExtra()) {
                            Accesibilidad::hablar("¡Turno extra! Vuelves a tirar.");
                            jugadores[turnoActual].usarTurnoExtra(); // Consumimos el beneficio
                            faseActual = ESPERANDO_TIRO; // No cambiamos de jugador
                        } 
                        else {
                            turnoActual = (turnoActual + 1) % jugadores.size();
                            
                            while (!jugadores[turnoActual].puedeJugar()) {
                                jugadores[turnoActual].descontarTurnoPerdido(); // Cumple su castigo
                                Accesibilidad::hablar(jugadores[turnoActual].getNombre().toAnsiString() + " sigue bloqueado.");
                                turnoActual = (turnoActual + 1) % jugadores.size();
                            }
                            
                            Accesibilidad::hablar("Es el turno de " + jugadores[turnoActual].getNombre().toAnsiString());
                            faseActual = ESPERANDO_TIRO; 
                        }
                    }
                }
            }
            
            relojMovimiento.restart();
        }
    }

    for (size_t i = 0; i < jugadores.size(); ++i) {
        panelesJugadores[i].actualizarDatos(jugadores[i]);
        
        if (jugadores[i].getPosicion() == -1) {
            Casilla* casillaCero = tablero.obtenerCasilla(0);
            if (casillaCero != nullptr) {
                casillaInicial = casillaCero->getPosicionVisual();
                jugadores[i].setPosicionVisual({casillaInicial.x + 25.f + (i * 10.f), casillaInicial.y + 70.f});
            }
        } 
        else {
            Casilla* casillaVisual = tablero.obtenerCasilla(jugadores[i].getPosicion());
            if (casillaVisual != nullptr) {
                sf::Vector2f coord = casillaVisual->getPosicionVisual();
                jugadores[i].setPosicionVisual({coord.x + 25.f + (i * 10.f), coord.y + 25.f});
            }
        }    
    }
}

void PantallaTablero::dibujar(sf::RenderWindow& ventana) {
    tablero.dibujar(ventana);
    
    for (auto& jugador : jugadores) {
        ventana.draw(jugador);
    }
    
    for (auto& panel : panelesJugadores) {
        ventana.draw(panel);
    }
    
    dado.draw(ventana);
}