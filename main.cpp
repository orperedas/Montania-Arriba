#include <cstdlib>
#include <clocale>
#include <iostream>
#include <memory>
#include <windows.h>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "headers/Accesibilidad.h"
#include "headers/PantallaAccesibilidad.h"
#include "headers/PantallaPrincipal.h"
#include "headers/PantallaDificultad.h"
#include "headers/PantallaTablero.h"
#include "headers/Musica.h"
#include "headers/Sonido.h"


Dificultad Dif;
int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile("imagenes/fondo.png")) {
        std::cerr << "Error al cargar la textura de fondo." << std::endl;
    }

    sf::Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition({0.f, 0.f});

    Accesibilidad::cargarAccesibilidad();
Sonido::cargarSonidos();
    Musica::inicializar();
    sf::RenderWindow window(sf::VideoMode({1280, 720}), L"Montaña arriba");

    std::unique_ptr<Estado> estadoActual = std::make_unique<PantallaAccesibilidad>(1280.f, 700.f);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            estadoActual->teclasGlobales(*event);

            EstadoID proximoEstado = estadoActual->manejarEventos(*event);

            if (proximoEstado != EstadoID::Ninguno) {
                if (proximoEstado == EstadoID::MenuPrincipal) {
Musica::reproducir(IDMusica::FondoMenu);
                    estadoActual = std::make_unique<PantallaPrincipal>(1280.f, 720.f);
                }
                else if (proximoEstado == EstadoID::Dificultad) {
                     estadoActual = std::make_unique<PantallaDificultad>(1280.f, 700.f, Dif);
                }
                
                else if (proximoEstado == EstadoID::Jugando) {
Musica::reproducir(IDMusica::FondoTablero);
                    estadoActual = std::make_unique<PantallaTablero>(1280.f, 700.f, Dif);
                }
                else if (proximoEstado == EstadoID::Salir) {
                    window.close();
                }
            }
        }

        estadoActual->actualizar();

        window.clear();
        window.draw(spriteBackground);
        estadoActual->dibujar(window);
        window.display();
    }

    Accesibilidad::descargarAccesibilidad();
    return 0;
}