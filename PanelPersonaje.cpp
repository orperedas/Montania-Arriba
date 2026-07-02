#include "headers/PanelPersonaje.h"

PanelPersonaje::PanelPersonaje(const sf::Font& fuente, const sf::Texture& texturaCorazonUI, sf::Vector2f posicionPantalla) 
    : textoNombre(fuente), textoPosicion(fuente) // <-- ACÁ LE DECIMOS QUÉ FUENTE USAN
{
    setPosition(posicionPantalla);

    fondo.setSize({250.f, 120.f});
    fondo.setFillColor(sf::Color(0, 0, 0, 150)); // Negro con transparencia
    fondo.setOutlineThickness(2.f);
    fondo.setOutlineColor(sf::Color::White);

    textoNombre.setCharacterSize(20);
    textoNombre.setFillColor(sf::Color::White);
    textoNombre.setPosition({10.f, 10.f});

    textoPosicion.setCharacterSize(18);
    textoPosicion.setFillColor(sf::Color::Yellow);
    textoPosicion.setPosition({10.f, 40.f});

    texturaCorazon = texturaCorazonUI;
}

void PanelPersonaje::actualizarDatos(Personaje& personaje) {
    textoNombre.setString("Jugador: " + personaje.getNombre());
    
    if (personaje.getPosicion() == -1) {
        textoPosicion.setString("Posicion: Inicio");
    } else {
        textoPosicion.setString("Posicion: " + std::to_string(personaje.getPosicion()));
    }

    corazones.clear();
    int vidas = personaje.getVida();
    for (int i = 0; i < vidas; ++i) {
        sf::Sprite corazon(texturaCorazon);
        corazon.setPosition({10.f + (i * 35.f), 75.f}); 
        corazones.push_back(corazon);
    }
}

void PanelPersonaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    
    target.draw(fondo, states);
    target.draw(textoNombre, states);
    target.draw(textoPosicion, states);
    
    for (const auto& corazon : corazones) {
        target.draw(corazon, states);
    }
}