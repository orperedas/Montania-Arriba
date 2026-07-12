#include "headers/Accesibilidad.h"
#include "headers/Estado.h"
#include "headers/Fuente.h"
#include "headers/Imagen.h"
#include "headers/PantallaTablero.h"
#include "headers/PartidaArchivo.h"
#include "headers/PartidaManager.h"
#include "headers/Sonido.h"
#include "headers/Visual.h"


PantallaTablero::PantallaTablero(float anchoVentana, float altoVentana, Partida& p, bool carga)
  : tablero(8),
    dado({anchoVentana / 2.f + 80, altoVentana / 2.f}),
    fondoDado(),
    reglas(static_cast<Dificultad>(p.getDificultad()), 64),
    partida(p),
    turnoActual(0)
{ 
    visual.fondoVentanaTablero(
        {anchoVentana / 5.f * 4.f, altoVentana / 5.f * 4.f},
        {anchoVentana / 2.f, altoVentana / 2.f} );

    int cantidad = partida.getCantidadJugadores();
    float posicionVertical = 130.f;
    float espacioVertical = 120.f;

    for (int i = 0; i < cantidad; ++i) {
        Personaje nuevoPersonaje(Fuente::getFuente(IDFuente::TituloPantalla), i);
        nuevoPersonaje.setNombre(partida.getNombreJugador(i)); 
        
        nuevoPersonaje.moverACasilla(partida.getPosicionJugador(i));
        jugadores.push_back(nuevoPersonaje);

        PanelPersonaje panel(Fuente::getFuente(IDFuente::TituloPantalla), 
                             Imagen::getImagen(IDImagen::Corazon),
                             jugadores[i].getTexture(),
                             {anchoVentana - 580.f, 120.f + (i * espacioVertical)});
        
        panelesJugadores.push_back(panel);
    }

    if (partida.getIdPartida() == 0) {
        guardarDatosTablero(false); 
    }
    
    Accesibilidad::hablar("Comienza tirando " + jugadores[turnoActual].getNombre().toAnsiString());
}


EstadoID PantallaTablero::manejarEventos(const sf::Event& evento) {
    if (!posicionInicialEstablecida) {
        for (size_t i = 0; i < jugadores.size(); ++i) {
            int posGuardada = jugadores[i].getPosicion();

            if (posGuardada == -1) {
                // Nueva partida: Ubicar debajo de la casilla 0
                Casilla* casillaCero = tablero.obtenerCasilla(0);
                if (casillaCero != nullptr) {
                    sf::Vector2f coordInicial = casillaCero->getPosicionVisual();
                    jugadores[i].setPosition({coordInicial.x + (i * 12.f), coordInicial.y + 75.f});
                }
            } else {
                // Partida cargada: Ubicar exactamente sobre su casilla
                Casilla* casillaGuardada = tablero.obtenerCasilla(posGuardada);
                if (casillaGuardada != nullptr) {
                    sf::Vector2f coordCasilla = casillaGuardada->getPosicionVisual();
                    jugadores[i].setPosition({coordCasilla.x + (i * 12.f), coordCasilla.y});
                }
            }
        }
        posicionInicialEstablecida = true; // Nos aseguramos de que esto corra UNA sola vez
    }

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

        if (keyPressed->code == sf::Keyboard::Key::T) {
            Accesibilidad::hablar("Tenés " + std::to_string(jugadores[turnoActual].getTirada()) + " tiradas");
        }

        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            return EstadoID::MenuPrincipal; 
        }
        
        if (keyPressed->code == sf::Keyboard::Key::Space && faseActual == ESPERANDO_TIRO) {
            if (jugadores[turnoActual].puedeJugar()) {
                casillasAAvanzar = dado.tirar();
                faseActual = ANIMANDO_DADO;
                jugadores[turnoActual].sumarTirada();
            }
        }
    }
    
    return EstadoID::Ninguno;
}


void PantallaTablero::actualizar() {
    dado.actualizar();

    for (auto& jugador : jugadores){
        jugador.actualizar();
    }

    if (faseActual == ANIMANDO_DADO) {
        if (!dado.estaAnimando()) {
            posicionObjetivo = reglas.calcularDestino(jugadores[turnoActual].getPosicion(), casillasAAvanzar);
            faseActual = MOVIENDO_PERSONAJE; 
            primerPaso = true;
        }
    }
    else if (faseActual == MOVIENDO_PERSONAJE) {   
        if (!jugadores[turnoActual].estaAnimando() || primerPaso) {      
            primerPaso = false;
            
            int posActual = jugadores[turnoActual].getPosicion();    

            if (posActual < posicionObjetivo) {
                Sonido::reproducir(IDSonido::paso);
                
                int siguientePos = posActual + 1;

                jugadores[turnoActual].moverACasilla(siguientePos);

                Casilla* casillaVisual = tablero.obtenerCasilla(siguientePos);
                if (casillaVisual != nullptr) {
                    sf::Vector2f coord = casillaVisual->getPosicionVisual();
                    sf::Vector2f destinoFinal = {coord.x + 0.f + (turnoActual * 10.f), coord.y + 0.f};
                    jugadores[turnoActual].comenzarMovimiento(destinoFinal);
                }
            } 
            else if (posActual > posicionObjetivo) {
                Sonido::reproducir(IDSonido::pasoatras);
                
                int siguientePos = posActual - 1;

                jugadores[turnoActual].moverACasilla(siguientePos);

                Casilla* casillaVisual = tablero.obtenerCasilla(siguientePos >= 0 ? siguientePos : 0);
                if (casillaVisual != nullptr) {
                    sf::Vector2f coord = casillaVisual->getPosicionVisual();
                    sf::Vector2f destinoFinal = {coord.x + 0.f + (turnoActual * 10.f), coord.y + 0.f};
                    jugadores[turnoActual].comenzarMovimiento(destinoFinal);
                }
            } 
            else {
                int posAntes = jugadores[turnoActual].getPosicion();
                
                Casilla* casillaActual = tablero.obtenerCasilla(posActual);
                
                if (casillaActual != nullptr) {
                    if (partida.getCantidadJugadores() > 1){
                        casillaActual->consecuencia((rand() % 3) + 1, jugadores[turnoActual]);
                    } else {
                        casillaActual->consecuencia((rand() % 2) + 1, jugadores[turnoActual]);
                    }
                }

                int posDespues = jugadores[turnoActual].getPosicion();

                if (posAntes != posDespues) {
                    jugadores[turnoActual].moverACasilla(posAntes); 
                    posicionObjetivo = posDespues;
                } else {
                    EstadoPartida estado = reglas.evaluarEstadoDelJuego(jugadores[turnoActual]);

                    if (estado == EstadoPartida::VICTORIA) {
                        guardarDatosTablero(true);
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
                            jugadores[turnoActual].usarTurnoExtra();
                            faseActual = ESPERANDO_TIRO;
                        } 
                        else {
                            int turnoAnterior = turnoActual;
                            turnoActual = (turnoActual + 1) % jugadores.size();
                            
                            while (!jugadores[turnoActual].puedeJugar()) {
                                jugadores[turnoActual].descontarTurnoPerdido();
                                Accesibilidad::hablar(jugadores[turnoActual].getNombre().toAnsiString() + " sigue bloqueado.");
                                turnoActual = (turnoActual + 1) % jugadores.size();
                            }
                            
                            if (turnoActual < turnoAnterior) {
                                guardarDatosTablero(false);
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
    }
}

void PantallaTablero::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(*this);
}

void PantallaTablero::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    
    visual.dibujar(target);
    tablero.dibujar(target);
    
    for (auto& jugador : jugadores) {
        target.draw(jugador, states);
    }
    
    for (auto& panel : panelesJugadores) {
        target.draw(panel, states);
    }
    
    dado.draw(target, states);
}

void PantallaTablero::guardarDatosTablero(bool finalizada) {
    for (size_t i = 0; i < jugadores.size(); ++i) {
        partida.setVidaJugador(i, jugadores[i].getVida());
        partida.setPosicionJugador(i, jugadores[i].getPosicion());
        partida.setTiradaJugador(i, jugadores[i].getTirada());
        
        partida.setJugadorActivo(i, (i == turnoActual));
        
        if (finalizada) {
            partida.setGanador(i, (i == turnoActual) && jugadores[i].estaVivo());
        } else {
            partida.setGanador(i, false);
        }
    }
    
    partida.setEstadoPartida(finalizada);
    PartidaManager manager(partida); 
    int idGuardado = manager.guardarPartida();
    partida.setIdPartida(idGuardado);         
}