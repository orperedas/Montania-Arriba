#include "headers/Accesibilidad.h"
#include "headers/Boton.h"
#include "headers/Fuente.h"
#include "headers/Imagen.h"

Boton::Boton(const std::string& texto, sf::Vector2f posicion, const sf::Font& fuente, const sf::Texture& textura, std::function<void()> accion) 
    : posicionBoton(posicion), 
      spriteBoton(textura), 
      etiquetaBoton(Fuente::getFuente(IDFuente::TextoBotonMenu)) 
{
    spriteBoton.setTextureRect({{0, 0}, {280, 72}});
    spriteBoton.setPosition(posicionBoton);
    spriteBoton.setScale({1.0f, 1.0f});
    
    etiquetaBoton.setString(sf::String::fromUtf8(texto.begin(), texto.end()));
    etiquetaBoton.setCharacterSize(22);
    
    sf::FloatRect spriteBounds = spriteBoton.getGlobalBounds();
    sf::FloatRect etiquetaBounds = etiquetaBoton.getLocalBounds();
    
    etiquetaBoton.setOrigin({etiquetaBounds.size.x / 2.0f, etiquetaBounds.size.y / 2.0f});
    
    float centroX = spriteBounds.position.x + (spriteBounds.size.x / 2.f);
    float centroY = spriteBounds.position.y + (spriteBounds.size.y / 2.5f);
    
    etiquetaBoton.setPosition({centroX, centroY});
    
    setSeleccionado(false); 
}


void Boton::setSeleccionado(bool seleccionado) {
    if (seleccionado) {
        spriteBoton.setTextureRect({{280, 0}, {560 , 72}});
        sf::Color seleccionadoColor(visual.getColor(IDVisual::NaranjaClaro_Solido));
        etiquetaBoton.setFillColor(seleccionadoColor);
    } else {
        spriteBoton.setTextureRect({{0, 0}, {280, 72}});
        sf::Color noSeleccionadoColor(visual.getColor(IDVisual::GrisClaro_Solido));
        etiquetaBoton.setFillColor(noSeleccionadoColor);
    }
}


void Boton::actualizarHover(sf::Vector2f mousePos){
    if (spriteBoton.getGlobalBounds().contains(mousePos)) {
        setSeleccionado(true);
    } else {
        setSeleccionado(false);
    }
}


bool Boton::procesarClick(sf::Vector2f mousePos){
    if (spriteBoton.getGlobalBounds().contains(mousePos)) {
        if (onAction) onAction();
        
        return true;
    }
    
    return false;
}


void Boton::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteBoton);
    ventana.draw(etiquetaBoton);
}