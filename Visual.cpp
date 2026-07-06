#include <SFML/Graphics.hpp>

#include "headers/imagen.h"
#include "headers/Visual.h"

sf::RectangleShape Visual::fondoVentanaTransparente;
const sf::Texture texturaFondoTablero = Imagen::getImagen(IDImagen::Tilegrass);
sf::Sprite spriteFondoTablero(texturaFondoTablero);
    
const sf::Color Visual::azul = sf::Color({12, 58, 95, 255});
const sf::Color Visual::naranjaClaro = sf::Color({251, 219, 144, 255});
const sf::Color Visual::naranjaOscuro = sf::Color({233, 111, 38, 255});
const sf::Color Visual::negroSolido = sf::Color({0, 0, 0, 255});
const sf::Color Visual::negrotransparente = sf::Color({0, 0, 0, 180});

std::map<IDVisual, sf::Texture> visuales;

Visual::Visual() {}

void Visual::inicializarVisual(){
    
}

const sf::Texture& getVisual(IDVisual id){
    return visuales.at(id);
}

void Visual::ventanafondoTablero(sf::Vector2f posicion, sf::Texture& fondo){
    
}

void Visual::ventanaFondoTransparente(sf::Vector2f tamanio, sf::Vector2f posicion, sf::Color colorFondo){
    sf::FloatRect fondoLocalBounds = fondoVentanaTransparente.getLocalBounds();
    fondoVentanaTransparente.setSize(tamanio);
    fondoVentanaTransparente.setOrigin({fondoLocalBounds.size.x / 2.f, fondoLocalBounds.size.y});
    fondoVentanaTransparente.setPosition(posicion);
    fondoVentanaTransparente.setFillColor(negrotransparente);
    fondoVentanaTransparente.setOutlineColor(azul);
    fondoVentanaTransparente.setOutlineThickness(3.f);
}