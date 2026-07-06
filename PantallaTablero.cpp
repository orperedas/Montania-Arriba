#include "headers/PantallaTablero.h"
#include "headers/Accesibilidad.h"
#include "headers/Fuente.h"
#include "headers/Sonido.h"
#include "headers/Estado.h"
#include "headers/Imagen.h"
#include "headers/PartidaArchivo.h"

PantallaTablero::PantallaTablero(float anchoVentana, float altoVentana, Partida& p)
  : tablero(8),
    personaje(Fuente::getFuente(IDFuente::TituloPantalla), 3),
    dado({anchoVentana / 2.f, altoVentana / 2.f}),
    fondoDado(),
    reglas(static_cast<Dificultad>(p.getDificultad()), 64),
    panelInfo(Fuente::getFuente(IDFuente::TituloPantalla), Imagen::getImagen(IDImagen::Corazon), {anchoVentana - 450.f, 120.f}),
    partida(p)
{ 
    personaje.moverACasilla(-1);
    personaje.setNombre(partida.getNombreJugador()); // Usamos los datos de la partida
}
EstadoID PantallaTablero::manejarEventos(const sf::Event& evento) {
    if (estadoPendiente != EstadoID::Ninguno) {
        return estadoPendiente;
    }
    
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::N) {
Accesibilidad::hablar(personaje.getNombre().toAnsiString() + 
                      ", te encuentras en la casilla " + 
                      std::to_string(personaje.getPosicion() + 1));
        }
        
        if (keyPressed->code == sf::Keyboard::Key::V) {
            Accesibilidad::hablar("Tenés " + std::to_string(personaje.getVida()) + " vidas");
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
        if (relojMovimiento.getElapsedTime() >= sf::seconds(0.5f)) {      
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
partida.setVidaJugador(personaje.getVida());
    PartidaArchivo pArchivo;
    
    // Guardamos el objeto partida actual
    if(pArchivo.guardar(partida)) {
        Accesibilidad::hablar("Partida guardada exitosamente.");
    } else {
        Accesibilidad::hablar("Error al guardar la partida.");
    }
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

    panelInfo.actualizarDatos(personaje);
    
    Casilla* casillaVisual = tablero.obtenerCasilla(personaje.getPosicion());
    
    if (casillaVisual != nullptr) {
        if (personaje.getPosicion() == -1){
            casillaInicial = tablero.obtenerCasilla(0)->getPosicionVisual();
            personaje.setPosicionVisual({casillaInicial.x + 25.f, casillaInicial.y + 70.f});
        }else {
            sf::Vector2f coord = casillaVisual->getPosicionVisual();
            personaje.setPosicionVisual({coord.x + 25.f, coord.y + 25.f});
        }
    }
}

void PantallaTablero::dibujar(sf::RenderWindow& ventana) {
    tablero.dibujar(ventana);
    ventana.draw(personaje);
    ventana.draw(panelInfo);
    dado.draw(ventana);
}