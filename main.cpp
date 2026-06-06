#include <SFML/Graphics.hpp>
#include <memory>
#include <ctime>
#include <cstdlib>
#include "headers/Accesibilidad.h"
#include "headers/PantallaAccesibilidad.h"
#include "headers/PantallaPrincipal.h"
#include "headers/PantallaTablero.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Accesibilidad::cargarAccesibilidad();

    sf::RenderWindow window(sf::VideoMode({1280, 700}), "SFML 3 + Tolk - UTN");

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
                     estadoActual = std::make_unique<PantallaPrincipal>(1280.f, 700.f);
                }
                if (proximoEstado == EstadoID::Jugando) {
                     estadoActual = std::make_unique<PantallaTablero>(1280.f, 700.f);
                }
                else if (proximoEstado == EstadoID::Salir) {
                    window.close();
                }
            }
        }

        estadoActual->actualizar();

        window.clear();
        estadoActual->dibujar(window);
        window.display();
    }

    Accesibilidad::descargarAccesibilidad();
    return 0;
}