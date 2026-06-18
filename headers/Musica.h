#ifndef MUSICA_H
#define MUSICA_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>

enum class IDMusica {
    FondoMenu,
    FondoTablero
};

class Musica {
private:
    static sf::Music reproductor;
    static std::map<IDMusica, std::string> rutas;

public:
    static void inicializar();
    static void reproducir(IDMusica id, bool loop = true);
    static void pausar();
    static void detener();
    static void setVolumen(float volumen);
};

#endif