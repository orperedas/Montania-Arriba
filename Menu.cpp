#include <iostream>
#include <windows.h>

#include "headers/Accesibilidad.h"
#include "headers/Menu.h"

Menu::Menu(float anchoVentana, float altoVentana, const sf::String& titulo, const std::vector<sf::String>& items) {
    //std::setlocale(LC_ALL, "es_ES.UTF-8");
    //std::setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    if (!fuente.openFromFile("fuentes/verdanab.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }
    if (!texturaBoton.loadFromFile("imagenes/menu_boton.png")) {
        std::cerr << "Error al cargar la textura del botón." << std::endl;
    }
    
    sf::Color tituloColor(239, 231, 170, 255);
    sf::Color tituloColorBorde(78, 140, 52, 255);
    sf::Text textoTit(fuente);
    textoTit.setString(titulo);
    textoTit.setCharacterSize(40);
    textoTit.setFillColor(tituloColor);
    textoTit.setStyle(sf::Text::Bold);
    textoTit.setPosition({(anchoVentana - textoTit.getLocalBounds().size.x) / 2.0f, 30.f});
    textoTit.setOutlineThickness(4.f);
    textoTit.setOutlineColor(tituloColorBorde);
    
    contenedorTitulo.push_back(textoTit);

    opciones = items;
    indiceSeleccionado = 0;

    for (size_t i = 0; i < opciones.size(); ++i) {
        float xPos = (anchoVentana - (texturaBoton.getSize().x / 2.0f)) / 2.0f;
        float yPos = altoVentana / (opciones.size() + 2) * (i + 1.5);
        sf::Vector2f posicionElemento = {xPos, yPos};

        Boton nuevoBoton(opciones[i], posicionElemento, fuente, texturaBoton);
        
        if (i == 0) {
            nuevoBoton.setSeleccionado(true);
        }
        
        botones.push_back(nuevoBoton);
    }

    std::string mensajeInicial = titulo.toAnsiString() + ". " + opciones[indiceSeleccionado].toAnsiString();
    Accesibilidad::hablar(mensajeInicial + ", botón");
}


void Menu::moverArriba() {
    if (indiceSeleccionado - 1 >= 0) {
        botones[indiceSeleccionado].setSeleccionado(false);
        indiceSeleccionado--;
        botones[indiceSeleccionado].setSeleccionado(true);
        
        Accesibilidad::hablar(opciones[indiceSeleccionado].toAnsiString() + ", botón");
    }
}


void Menu::moverAbajo() {
    if (indiceSeleccionado + 1 < opciones.size()) {
        botones[indiceSeleccionado].setSeleccionado(false);
        indiceSeleccionado++;
        botones[indiceSeleccionado].setSeleccionado(true);
        
        Accesibilidad::hablar(opciones[indiceSeleccionado].toAnsiString() + ", botón");
    }
}


int Menu::obtenerSeleccion() const {
    return indiceSeleccionado;
}


void Menu::dibujar(sf::RenderWindow& ventana) {
    if (spriteFondo.has_value()) {
        ventana.draw(*spriteFondo); 
    }

    for (auto& t : contenedorTitulo) {
        ventana.draw(t);
    }
    
    for (auto& boton : botones) {
        boton.dibujar(ventana);
    }
}