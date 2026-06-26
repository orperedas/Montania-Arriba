#include "headers/Sonido.h"
#include <iostream>

std::map<IDSonido, sf::SoundBuffer> Sonido::buffers;
std::list<sf::Sound> Sonido::canales;

void Sonido::cargarSonidos() {
    if (!buffers[IDSonido::MenuDesplazar].loadFromFile("sonidos/Menu/desplazamiento.wav")) {
        std::cerr << "Error cargando desplazamiento.wav" << std::endl;
    }
    if (!buffers[IDSonido::MenuConfirmar].loadFromFile("sonidos/Menu/enter.wav")) {
        std::cerr << "Error cargando enter.wav" << std::endl;
    }
    if (!buffers[IDSonido::TirarDado].loadFromFile("sonidos/gameplay/dado.wav")) {
        std::cerr << "Error cargando enter.wav" << std::endl;
    }
    if (!buffers[IDSonido::paso].loadFromFile("sonidos/gameplay/paso.wav")) {
        std::cerr << "Error cargando enter.wav" << std::endl;
    }
    if (!buffers[IDSonido::rujidoOso].loadFromFile("sonidos/gameplay/oso.wav")) {
        std::cerr << "Error cargando enter.wav" << std::endl;
    }
    if (!buffers[IDSonido::avalancha].loadFromFile("sonidos/gameplay/avalancha.wav")) {
        std::cerr << "Error cargando avalancha.wav" << std::endl;
    }
    if (!buffers[IDSonido::ganarVida].loadFromFile("sonidos/gameplay/ganar_vida.wav")) {
        std::cerr << "Error cargando ganar_vida.wav" << std::endl;
    }
    if (!buffers[IDSonido::Victoria].loadFromFile("sonidos/gameplay/victoria.wav")) {
        std::cerr << "Error cargando victoria.wav" << std::endl;
    }
    if (!buffers[IDSonido::suvida].loadFromFile("sonidos/gameplay/ojas.wav")) {
        std::cerr << "Error cargando ojas.wav" << std::endl;
    }
    if (!buffers[IDSonido::hueso].loadFromFile("sonidos/gameplay/huesoRoto.wav")) {
        std::cerr << "Error cargando huesoRoto.wav" << std::endl;
    }
    if (!buffers[IDSonido::grito].loadFromFile("sonidos/gameplay/dolor.wav")) {
        std::cerr << "Error cargando dolor.wav" << std::endl;
    }
    if (!buffers[IDSonido::pasoatras].loadFromFile("sonidos/gameplay/pasoatras.wav")) {
        std::cerr << "Error cargando pasoatras.wav" << std::endl;
    }

}


void Sonido::reproducir(IDSonido id) {
    canales.remove_if([](const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Status::Stopped; 
    });

    auto it = buffers.find(id);
    if (it != buffers.end()) {
        canales.emplace_back(it->second); 
        canales.back().play();
    }
}