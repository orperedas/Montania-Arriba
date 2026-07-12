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
    colores[IDVisual::GrisOscuro_Solido] = sf::Color(32, 32, 32);
    colores[IDVisual::NaranjaClaro_Solido] = sf::Color(252, 219, 142);
    colores[IDVisual::NaranjaOscuro_Solido] = sf::Color(224, 112, 34);
    colores[IDVisual::Negro_Transparente] = sf::Color(0, 0, 0, 200);
}

sf::Color Visual::getColor(IDVisual id) {
    auto it = colores.find(id);
    if (it != colores.end()) {
        return it->second;
    }
    
    return getColor(IDVisual::Blanco_Solido);
}

sf::Texture& getVisual(IDVisual id){
    return visuales.at(id);
}

void Visual::fondoVentanaTablero(sf::Vector2f tamanio, sf::Vector2f posicion){
    spriteFondoTablero.setTexture(Imagen::getImagen(IDImagen::Tilegrass));
    texturaFondoTablero.setRepeated(true);
    spriteFondoTablero.setTextureRect(sf::IntRect({68, 68}, sf::Vector2i(static_cast<int>(tamanio.x), static_cast<int>(tamanio.y))));
    spriteFondoTablero.setOrigin({tamanio.x / 2.f, tamanio.y / 2.f});
    spriteFondoTablero.setPosition(posicion);
}

void Visual::fondoVentanaTransparente(sf::Vector2f tamanio, sf::Vector2f posicion, sf::Color colorFondo){
    fondoTransparente.setSize(tamanio);
    sf::FloatRect fondoLocalBounds = fondoTransparente.getGlobalBounds();
    fondoTransparente.setOrigin({fondoLocalBounds.size.x / 2.f, fondoLocalBounds.size.y / 2.f});
    fondoTransparente.setPosition(posicion);
    fondoTransparente.setFillColor(colores[IDVisual::Negro_Transparente]);
    fondoTransparente.setOutlineColor(colores[IDVisual::Azul_Solido]);
    fondoTransparente.setOutlineThickness(4.f);
}

void Visual::dibujar(sf::RenderWindow& ventana){
    ventana.draw(fondoTransparente);
    ventana.draw(spriteFondoTablero);
}