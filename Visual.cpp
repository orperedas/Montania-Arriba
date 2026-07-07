#include <SFML/Graphics.hpp>

#include "headers/imagen.h"
#include "headers/Visual.h"

std::map<IDVisual, sf::Texture> visuales;

Visual::Visual()
:   texturaFondoTablero(Imagen::getImagen(IDImagen::Tilegrass)),
    spriteFondoTablero(texturaFondoTablero)
{
    inicializarVisual();
}

void Visual::inicializarVisual(){
    colores[IDVisual::Azul_Solido] = sf::Color(12, 58, 95);
    colores[IDVisual::Blanco_Solido] = sf::Color(255, 255, 255);
    colores[IDVisual::GrisClaro_Solido] = sf::Color(200, 200, 200);
    colores[IDVisual::GrisMedio_Solido] = sf::Color(100, 100, 100);
    colores[IDVisual::GrisOscuro_Solido] = sf::Color(25, 25, 25);
    colores[IDVisual::NaranjaClaro_Solido] = sf::Color(255, 165, 0);
    colores[IDVisual::NaranjaOscuro_Solido] = sf::Color(204, 85, 0);
    colores[IDVisual::Negro_Transparente] = sf::Color(0, 0, 0, 180);
}

sf::Color Visual::getColor(IDVisual id) {
    auto it = colores.find(id);
    if (it != colores.end()) {
        return it->second;
    }
    return sf::Color::White; // Color por defecto en caso de error
}

sf::Texture& getVisual(IDVisual id){
    return visuales.at(id);
}

void Visual::fondoVentanaTablero(sf::Vector2f tamanio, sf::Vector2f posicion){
    texturaFondoTablero.setRepeated(true);
    sf::FloatRect bounds = spriteFondoTablero.getLocalBounds();
    spriteFondoTablero.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    spriteFondoTablero.setPosition(posicion);
    spriteFondoTablero.setTextureRect(sf::IntRect(sf::Vector2i(68, 68), sf::Vector2i(static_cast<int>(tamanio.x), static_cast<int>(tamanio.y))));
}

void Visual::fondoVentanaTransparente(sf::Vector2f tamanio, sf::Vector2f posicion, sf::Color colorFondo){
    fondoTransparente.setSize(tamanio);
    sf::FloatRect fondoLocalBounds = fondoTransparente.getGlobalBounds();
    fondoTransparente.setOrigin({fondoLocalBounds.size.x / 2.f, fondoLocalBounds.size.y / 2.f});
    fondoTransparente.setPosition(posicion);
    fondoTransparente.setFillColor(colores[IDVisual::Negro_Transparente]);
    fondoTransparente.setOutlineColor(colores[IDVisual::Azul_Solido]);
    fondoTransparente.setOutlineThickness(3.f);
}

void Visual::dibujar(sf::RenderWindow& ventana){
    ventana.draw(fondoTransparente);
    ventana.draw(spriteFondoTablero);
}