#ifndef SONIDO_H
#define SONIDO_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <list> // Usamos list para limpiar fácilmente los sonidos terminados

enum class IDSonido {
    MenuDesplazar,
    MenuConfirmar,
    TirarDado,
    Victoria,
    Derrota,
    rujidoOso,
    avalancha,
    paso,
    masticar,
    ganarVida
};

class Sonido {
private:
    static std::map<IDSonido, sf::SoundBuffer> buffers;
    static std::list<sf::Sound> canales; // Ahora es una lista

public:
    static void cargarSonidos();
    static void reproducir(IDSonido id);
};

#endif