#include "headers/PanelPersonaje.h"

PanelPersonaje::PanelPersonaje(const sf::Font& fuente, const sf::Texture& texturaCorazonUI, sf::Vector2f posicionPantalla) 
    : textoNombre(fuente), textoPosicion(fuente), textoVidas(fuente) // <-- ACÁ LE DECIMOS QUÉ FUENTE USAN
{
    setPosition(posicionPantalla);

    fondo.setSize({350.f, 100.f});
    fondo.setFillColor(sf::Color(20, 20, 20));
    fondo.setOutlineThickness(3.f);
    fondo.setOutlineColor(sf::Color(100, 100, 100));

    textoNombre.setCharacterSize(20);
    textoNombre.setFillColor(sf::Color(200, 200, 200));
    textoNombre.setPosition({10.f, 10.f});

    textoPosicion.setCharacterSize(18);
    textoPosicion.setFillColor(sf::Color::White);
    textoPosicion.setPosition({10.f, 40.f});

    textoVidas.setCharacterSize(18);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition({10.f, 70.f});

    texturaCorazon = texturaCorazonUI;
}

void PanelPersonaje::actualizarDatos(Personaje& personaje) {
    textoNombre.setString("Jugador: " + personaje.getNombre());
    textoVidas.setString("Vidas: ");

    if (personaje.getPosicion() == -1) {
        textoPosicion.setString("Posicion: Inicio");
    } else {
        textoPosicion.setString("Posicion: " + std::to_string(personaje.getPosicion() + 1));
    }

    corazones.clear();
    
    int vidas = personaje.getVida();

    for (int i = 0; i < vidas; ++i) {
        sf::Sprite corazon(texturaCorazon);
        corazon.setPosition({110.f + (i * 20.f), 75.f});
        corazones.push_back(corazon);
    }
}

void PanelPersonaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    
    target.draw(fondo, states);
    target.draw(textoNombre, states);
    target.draw(textoPosicion, states);
    target.draw(textoVidas, states);

    for (const auto& corazon : corazones) {
        target.draw(corazon, states);
    }
}