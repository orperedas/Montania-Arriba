#include <iostream>
#include <windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "headers/Accesibilidad.h"
#include "headers/Fuente.h"
#include "headers/imagen.h"
#include "headers/Menu.h"
#include "headers/Sonido.h"
#include "headers/Visual.h"

Menu::Menu(float anchoVentana, float altoVentana, const std::string& titulo, const std::vector<std::string>& items)
:   texturaLogo(Imagen::getImagen(IDImagen::LogoPequenio)),
    spriteLogo(texturaLogo),
    fuenteTitulo(Fuente::getFuente(IDFuente::TituloPantalla)),
    fuenteBoton(Fuente::getFuente(IDFuente::TextoBotonMenu)),
    texturaBoton(Imagen::getImagen(IDImagen::BotonMenu))
{
    fondoBox.fondoVentanaTransparente(
        {anchoVentana / 2.f, altoVentana / 3.f * 2.f},
        {anchoVentana / 2.f, altoVentana / 2.f},
        visual.getColor(IDVisual::Negro_Transparente));

    sf::FloatRect boundsLogo = spriteLogo.getGlobalBounds();
    spriteLogo.setOrigin({boundsLogo.size.x / 2.f, 0.f});
    spriteLogo.setPosition({anchoVentana / 2.f, 30.f});
    std::cout << "Logo position: (" << spriteLogo.getPosition().x << ", " << spriteLogo.getPosition().y << ")" << std::endl;
    
    sf::Color tituloColor(255, 222, 148, 255);
    sf::Color tituloColorBorde(12, 58, 94, 255);
    sf::Text textoTit(fuenteTitulo);
    
    
    textoTit.setString(sf::String::fromUtf8(titulo.begin(), titulo.end()));
    textoTit.setCharacterSize(30);
    textoTit.setFillColor(tituloColor);
    textoTit.setStyle(sf::Text::Bold);
    textoTit.setPosition({(anchoVentana - textoTit.getLocalBounds().size.x) / 2.0f, spriteLogo.getPosition().y + boundsLogo.size.y + 30.f});
    textoTit.setOutlineThickness(4.f);
    textoTit.setOutlineColor(tituloColorBorde);
    
    contenedorTitulo.push_back(textoTit);

    opciones = items;
    indiceSeleccionado = 0;
    
    sf::FloatRect boundsTextoTit = textoTit.getGlobalBounds();
    float xPos = (anchoVentana - (texturaBoton.getSize().x / 2.0f)) / 2.0f;
    float yPos = boundsTextoTit.position.y + boundsTextoTit.size.y + 70.0f;

    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Vector2f posicionElemento = {xPos, yPos};
        
        Boton nuevoBoton(opciones[i], posicionElemento, fuenteBoton, texturaBoton);
        
        if (i == 0) {
            nuevoBoton.setSeleccionado(true);
        }
        
        yPos += texturaBoton.getSize().y * 1.1;
        
        botones.push_back(nuevoBoton);
    }

    std::string mensajeInicial = titulo + ". " + opciones[indiceSeleccionado];
    Accesibilidad::hablar(mensajeInicial);
}


void Menu::moverArriba() {
    if (indiceSeleccionado - 1 >= 0) {
        botones[indiceSeleccionado].setSeleccionado(false);
        indiceSeleccionado--;
        botones[indiceSeleccionado].setSeleccionado(true);
        Sonido::reproducir(IDSonido::MenuDesplazar);
        Accesibilidad::hablar(opciones[indiceSeleccionado], true);
    }
}


void Menu::moverAbajo() {
    if (indiceSeleccionado + 1 < opciones.size()) {
        botones[indiceSeleccionado].setSeleccionado(false);
        indiceSeleccionado++;
        botones[indiceSeleccionado].setSeleccionado(true);
        Sonido::reproducir(IDSonido::MenuDesplazar);
                Accesibilidad::hablar(opciones[indiceSeleccionado], true);
    }
}


int Menu::obtenerSeleccion() const {
        Sonido::reproducir(IDSonido::MenuConfirmar);
    return indiceSeleccionado;
}


void Menu::dibujar(sf::RenderWindow& ventana) {
    fondoBox.dibujar(ventana);

    if (spriteFondo.has_value()) {
        ventana.draw(*spriteFondo);
    }
    
    //ventana.draw(spriteLogo);
        
    for (auto& t : contenedorTitulo) {
        ventana.draw(t);
    }
    
    for (auto& boton : botones) {
        boton.dibujar(ventana);
    }
}