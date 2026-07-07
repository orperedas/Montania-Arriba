#include <SFML/Graphics.hpp>

#include "headers/imagen.h"
#include "headers/Visual.h"

std::map<IDVisual, sf::Texture> visuales;

Visual::Visual()
:   azul(sf::Color({12, 58, 95, 255})),
    naranjaClaro(sf::Color({251, 219, 144, 255})),
    naranjaOscuro(sf::Color({233, 111, 38, 255})),
    negroSolido(sf::Color({0, 0, 0, 255})),
    negrotransparente(sf::Color({0, 0, 0, 180})),
    texturaFondoTablero(Imagen::getImagen(IDImagen::Tilegrass)),
    spriteFondoTablero(texturaFondoTablero)
 {
 }

void Visual::inicializarVisual(){
    
}

sf::Texture& getVisual(IDVisual id){
    return visuales.at(id);
}

void Visual::fondoVentanaTablero(sf::Vector2f posicion){
    texturaFondoTablero.setRepeated(true);
    spriteFondoTablero.setOrigin({100.f, 100.f});
    spriteFondoTablero.setPosition(posicion);
    spriteFondoTablero.setTextureRect(sf::IntRect({{68, 68}, {1100, 600}}));
}

void Visual::fondoVentanaTransparente(sf::Vector2f tamanio, sf::Vector2f posicion, sf::Color colorFondo){
    fondoTransparente.setSize(tamanio);
    sf::FloatRect fondoLocalBounds = fondoTransparente.getGlobalBounds();
    fondoTransparente.setOrigin({fondoLocalBounds.size.x / 2.f, fondoLocalBounds.size.y / 2.f});
    fondoTransparente.setPosition(posicion);
    fondoTransparente.setFillColor(negrotransparente);
    fondoTransparente.setOutlineColor(azul);
    fondoTransparente.setOutlineThickness(3.f);
}

void Visual::dibujar(sf::RenderWindow& ventana){
    ventana.draw(fondoTransparente);
    ventana.draw(spriteFondoTablero);
}