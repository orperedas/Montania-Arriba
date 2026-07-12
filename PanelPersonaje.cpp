#include "headers/Fuente.h"
#include "headers/imagen.h"
#include "headers/PanelPersonaje.h"
#include "headers/Visual.h"

PanelPersonaje::PanelPersonaje(const sf::Font& fuente, const sf::Texture& texturaCorazonUI, const sf::Texture& texturaJugador, sf::Vector2f posicionPantalla) 
  : textoNombre(fuente),
    textoPosicion(fuente),
    textoVidas(fuente),
    spritePersonaje(texturaJugador)
{
    setPosition(posicionPantalla);

    fondo.setSize({370.f, 100.f});
    fondo.setFillColor(visual.getColor(IDVisual::GrisOscuro_Solido));
    fondo.setOutlineThickness(3.f);
    fondo.setOutlineColor(visual.getColor(IDVisual::GrisMedio_Solido));

    texturaPersonaje = texturaJugador;
    spritePersonaje.setTextureRect(sf::IntRect({15, 140}, {50, 40}));
    spritePersonaje.setScale({2.0f, 2.0f});
    spritePersonaje.setPosition({10.f, 10.f});

    textoNombre.setCharacterSize(20);
    textoNombre.setFillColor(visual.getColor(IDVisual::GrisClaro_Solido));
    textoNombre.setPosition({90.f, 10.f});

    textoPosicion.setCharacterSize(18);
    textoPosicion.setFillColor(visual.getColor(IDVisual::NaranjaClaro_Solido));
    textoPosicion.setPosition({90.f, 40.f});

    textoVidas.setCharacterSize(18);
    textoVidas.setFillColor(visual.getColor(IDVisual::Blanco_Solido));
    textoVidas.setPosition({90.f, 70.f});

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
        corazon.setPosition({190.f + (i * 20.f), 75.f});
        corazones.push_back(corazon);
    }
}

void PanelPersonaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    
    target.draw(fondo, states);
    target.draw(spritePersonaje, states);
    target.draw(textoNombre, states);
    target.draw(textoPosicion, states);
    target.draw(textoVidas, states);

    for (const auto& corazon : corazones) {
        target.draw(corazon, states);
    }
}