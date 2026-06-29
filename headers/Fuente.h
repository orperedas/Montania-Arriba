#ifndef FUENTE_H
#define FUENTE_H

#include <map>

#include <SFML/Graphics.hpp>

enum class IDFuente{
    BotonMenu,
    InputNombre,
    TituloPantalla
};

class Fuente{
private:
    static std::map<IDFuente, sf::Font> fuentes;

public:
    static void cargarFuente();
    static const sf::Font& getFuente(IDFuente id);
};

#endif