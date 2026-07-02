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

Dificultad Dif;

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    sf::RenderWindow window(sf::VideoMode({1440, 810}), L"Montaña arriba");
    
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    
    float anchoVentana = static_cast<float>(desktopMode.size.x);
    float altoVentana = static_cast<float>(desktopMode.size.y);

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
    
    const float proporcionObjetivo = 16.0f / 9.0f;

    std::unique_ptr<Estado> estadoActual = std::make_unique<PantallaAccesibilidad>(anchoVentana, altoVentana);

    while (window.isOpen()) {
        EstadoID proximoEstado = EstadoID::Ninguno; // Variable maestra para controlar el cambio

        while (const std::optional event = window.pollEvent()) {

            if (const auto* resized = event->getIf<sf::Event::Resized>()) { // [5, 7]
        
                float anchoVentana = 1440;
                float altoVentana = 810;
                float proporcionVentana = anchoVentana / altoVentana;

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

                sf::View view = window.getView();
                view.setViewport(viewport); // [9]
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
            if (proximoEstado == EstadoID::NombreJugador) {
                estadoActual = std::make_unique<PantallaNombreJugador>(anchoVentana, altoVentana);
            }
            else if (proximoEstado == EstadoID::Dificultad) {
                 estadoActual = std::make_unique<PantallaDificultad>(anchoVentana, altoVentana, Dif);
            }
            else if (proximoEstado == EstadoID::Jugando) {
                Musica::reproducir(IDMusica::FondoTablero);
                estadoActual = std::make_unique<PantallaTablero>(anchoVentana, altoVentana, Dif);
            }
            else if (proximoEstado == EstadoID::Victoria) {
                Musica::reproducir(IDMusica::FondoTablero);
                estadoActual = std::make_unique<PantallaVictoria>(anchoVentana, altoVentana);
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