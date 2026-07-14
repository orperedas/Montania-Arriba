#include <cstdlib>
#include <clocale>
#include <iostream>
#include <memory>
#include <windows.h>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "headers/Accesibilidad.h"
#include "headers/Fuente.h"
#include "headers/imagen.h"
#include "headers/Musica.h"
#include "headers/PantallaAccesibilidad.h"
#include "headers/PantallaPrincipal.h"
#include "headers/PantallaDificultad.h"
#include "headers/PantallaNombreJugador.h"
#include "headers/PantallaTablero.h"
#include "headers/PantallaVictoria.h"
#include "headers/Sonido.h"
#include "headers/Partida.h"
#include "headers/PartidaArchivo.h"
#include "headers/PartidaManager.h"
#include "headers/Visual.h"
#include "headers/PantallaCantidadJugadores.h"
#include "headers/PantallaDerrota.h"
#include "headers/PantallaCargarPartida.h"
#include "headers/PantallaEstadisticas.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    sf::RenderWindow window(sf::VideoMode({1440, 810}), L"Montaña arriba");
    
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    float anchoVentana = 1440.f;
    float altoVentana = 810.f;

    const float proporcionObjetivo = 16.0f / 9.0f;
    
    Imagen::cargarImagen();

    sf::Texture textureBackground = Imagen::getImagen(IDImagen::Fondo);

    sf::Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition({0.f, 0.f});

    float fondoTamanioX = spriteBackground.getGlobalBounds().size.x;
    float fondoTamanioY = spriteBackground.getGlobalBounds().size.y;

    spriteBackground.scale({anchoVentana / fondoTamanioX, altoVentana / fondoTamanioY});

    Accesibilidad::cargarAccesibilidad();
    Fuente::cargarFuente();
    Sonido::cargarSonidos();
    Musica::inicializar();

    PartidaArchivo partidaArchivo;
    PartidaManager partidaManager;
    Partida partida;

    partidaArchivo.cargarPartidas();
    
    std::cout << std::endl;

    std::unique_ptr<Estado> estadoActual = std::make_unique<PantallaAccesibilidad>(anchoVentana, altoVentana);

    while (window.isOpen()) {
        EstadoID proximoEstado = EstadoID::Ninguno;

        while (const std::optional event = window.pollEvent()) {

            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                float nuevoAncho = static_cast<float>(resized->size.x);
                float nuevoAlto = static_cast<float>(resized->size.y);
                float proporcionVentana = nuevoAncho / nuevoAlto;

                sf::FloatRect viewport{{0.f, 0.f}, {1.f, 1.f}};
                bool necesitaAjuste = false;

                if (proporcionVentana > proporcionObjetivo) {
                    viewport.size.x = proporcionObjetivo / proporcionVentana;
                    viewport.position.x = (1.f - viewport.size.x) / 2.f;
                    necesitaAjuste = true;
                } 
                else if (proporcionVentana < proporcionObjetivo) {
                    viewport.size.y = proporcionVentana / proporcionObjetivo;
                    viewport.position.y = (1.f - viewport.size.y) / 2.f;
                    necesitaAjuste = true;
                }

                //sf::View view = window.getView();
                sf::View view;
                view.setSize({1440.f, 810.f});
                view.setCenter({1440.f / 2.f, 810.f / 2.f});
                view.setViewport(viewport);
                window.setView(view);
            }
            
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            estadoActual->teclasGlobales(*event);

            EstadoID estadoPorEvento = estadoActual->manejarEventos(*event);
            if (estadoPorEvento != EstadoID::Ninguno) {
                proximoEstado = estadoPorEvento;
            }
        }

        estadoActual->actualizar();

        if (proximoEstado == EstadoID::Ninguno) {
            proximoEstado = estadoActual->getEstadoPendiente();
        }

        if (proximoEstado != EstadoID::Ninguno) {
            if (proximoEstado == EstadoID::MenuPrincipal) {
                Musica::reproducir(IDMusica::FondoMenu);
                estadoActual = std::make_unique<PantallaPrincipal>(anchoVentana, altoVentana);
            }
            if (proximoEstado == EstadoID::Cantidad) {
Partida nuevaPartida;
partida = nuevaPartida;
                estadoActual = std::make_unique<PantallaCantidadJugadores>(anchoVentana, altoVentana,partida);
            }
            if (proximoEstado == EstadoID::NombreJugador) {
                estadoActual = std::make_unique<PantallaNombreJugador>(anchoVentana, altoVentana,partida);
            }
            else if (proximoEstado == EstadoID::Dificultad) {
                 estadoActual = std::make_unique<PantallaDificultad>(anchoVentana, altoVentana, partida);
            }
            else if (proximoEstado == EstadoID::Jugando) {
                Musica::reproducir(IDMusica::FondoTablero);
                estadoActual = std::make_unique<PantallaTablero>(anchoVentana, altoVentana, partida);
            }
            else if (proximoEstado == EstadoID::Victoria) {
                estadoActual = std::make_unique<PantallaVictoria>(anchoVentana, altoVentana,partida);
            }
            else if (proximoEstado == EstadoID::Derrota) {
                estadoActual = std::make_unique<PantallaDerrota>(anchoVentana, altoVentana,partida);
            }
            else if (proximoEstado == EstadoID::CargarPartida) {
                 estadoActual = std::make_unique<PantallaCargarPartida>(anchoVentana, altoVentana, partida);
            }
            else if (proximoEstado == EstadoID::estadisticas) {
                 estadoActual = std::make_unique<PantallaEstadisticas>(anchoVentana, altoVentana);
            }
            else if (proximoEstado == EstadoID::juegoCargado) {
                Musica::reproducir(IDMusica::FondoTablero);
                estadoActual = std::make_unique<PantallaTablero>(anchoVentana, altoVentana, partida,true);
            }
            else if (proximoEstado == EstadoID::Salir) {
                window.close();
            }
        }

        window.clear();
        window.draw(spriteBackground);
        estadoActual->dibujar(window);
        window.display();
    }

    Accesibilidad::descargarAccesibilidad();
    return 0;
}