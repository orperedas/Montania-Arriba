#include <iostream>
#include <windows.h>
#include "headers/Sonido.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "headers/Accesibilidad.h"
#include "headers/Menu.h"

Menu::Menu(float anchoVentana, float altoVentana, const std::string& titulo, const std::vector<std::string>& items) : spriteLogo(texturaLogo) {

    if (!fuente.openFromFile("fuentes/verdanab.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }

    if (!texturaBoton.loadFromFile("imagenes/menu_boton.png")) {
        std::cerr << "Error al cargar la textura del botón." << std::endl;
    }

    if (!texturaLogo.loadFromFile("imagenes/montania_arriba_logo_pequenio.png")) {
        std::cerr << "Error al cargar la textura del botón." << std::endl;
    }

    spriteLogo.setTexture(texturaLogo, true);

    sf::FloatRect boundsLogo = spriteLogo.getGlobalBounds();
    spriteLogo.setOrigin({boundsLogo.size.x / 2.f, 0.f});
    spriteLogo.setPosition({anchoVentana / 2.f, 30.f});
    
    sf::Color tituloColor(255, 222, 148, 255);
    sf::Color tituloColorBorde(12, 58, 94, 255);
    sf::Text textoTit(fuente);
    
    textoTit.setString(sf::String::fromUtf8(titulo.begin(), titulo.end()));
    textoTit.setCharacterSize(40);
    textoTit.setFillColor(tituloColor);
    textoTit.setStyle(sf::Text::Bold);
    textoTit.setPosition({(anchoVentana - textoTit.getLocalBounds().size.x) / 2.0f, spriteLogo.getPosition().y + boundsLogo.size.y + 30.f});
    textoTit.setOutlineThickness(4.f);
    textoTit.setOutlineColor(tituloColorBorde);
    
    contenedorTitulo.push_back(textoTit);

    opciones = items;
    indiceSeleccionado = 0;
    
    sf::FloatRect boundsTextoTit = textoTit.getGlobalBounds();
    std::cout << "spriteLogo position: " << spriteLogo.getPosition().y << std::endl;
    std::cout << "spriteLogo GlogalBounds: " << boundsLogo.size.y << std::endl;
    std::cout << "textoTit position: " << textoTit.getPosition().y << std::endl;
    std::cout << "textoTit GlogalBounds: " << boundsTextoTit.size.y << std::endl;

    for (size_t i = 0; i < opciones.size(); ++i) {
        float xPos = (anchoVentana - (texturaBoton.getSize().x / 2.0f)) / 2.0f;
        float yPos = altoVentana / (opciones.size() + 2) * (i + 1.1);
        
        //float yPos = boundsTextoTit.position.y + boundsTextoTit.size.y + 30.f;
        sf::Vector2f posicionElemento = {xPos, yPos};


        Boton nuevoBoton(opciones[i], posicionElemento, fuente, texturaBoton);
        //std::cout << "Botón : " << i << nuevoBoton.getPosition().y << std::endl;
        
        if (i == 0) {
            nuevoBoton.setSeleccionado(true);
        }
        
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
    if (spriteFondo.has_value()) {
        ventana.draw(*spriteFondo);
    }
    
    ventana.draw(spriteLogo);
        
    for (auto& t : contenedorTitulo) {
        ventana.draw(t);
    }
    
    for (auto& boton : botones) {
        boton.dibujar(ventana);
    }
}