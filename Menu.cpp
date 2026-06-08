#include "headers/Menu.h"
#include "headers/Accesibilidad.h"
#include <iostream>

Menu::Menu(float anchoVentana, float altoVentana, const sf::String& titulo, const std::vector<sf::String>& items) {
    if (!fuente.openFromFile("fuentes/sansation.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }
    if (!texturaBoton.loadFromFile("imagenes/menu_boton.png")) {
        std::cerr << "Error al cargar la textura del botón." << std::endl;
    }

    /*
    if (texturaFondo.loadFromFile("imagenes/fondo.png")) {
        spriteFondo.emplace(texturaFondo); 
        float escalaX = anchoVentana / spriteFondo->getLocalBounds().size.x;
        float escalaY = altoVentana / spriteFondo->getLocalBounds().size.y;
        spriteFondo->setScale({escalaX, escalaY}); 
    }
    */

    
    sf::Text textoTit(fuente);
    textoTit.setString(titulo);
    textoTit.setCharacterSize(50);
    textoTit.setFillColor(sf::Color::Green);
    textoTit.setStyle(sf::Text::Bold);
    textoTit.setPosition({(anchoVentana - textoTit.getLocalBounds().size.x) / 2.0f, 30.f});
    textoTit.setOutlineThickness(3.f);
    textoTit.setOutlineColor(sf::Color::Black);
    
    contenedorTitulo.push_back(textoTit);

    opciones = items;
    indiceSeleccionado = 0;

    for (size_t i = 0; i < opciones.size(); ++i) {
        float xPos = (anchoVentana - texturaBoton.getSize().x) / 2.0f;
        float yPos = altoVentana / (opciones.size() + 2) * (i + 2);
        sf::Vector2f posicionElemento = {xPos, yPos};

        Boton nuevoBoton(opciones[i], posicionElemento, fuente, texturaBoton);
        
        if (i == 0) {
            nuevoBoton.setSeleccionado(true);
        }
        
        botones.push_back(nuevoBoton);
    }

    std::string mensajeInicial = titulo.toAnsiString() + ". " + opciones[indiceSeleccionado].toAnsiString();
    Accesibilidad::hablar(mensajeInicial);
}

void Menu::moverArriba() {
    if (indiceSeleccionado - 1 >= 0) {
        botones[indiceSeleccionado].setSeleccionado(false);
        indiceSeleccionado--;
        botones[indiceSeleccionado].setSeleccionado(true);
        
        Accesibilidad::hablar(opciones[indiceSeleccionado].toAnsiString());
    }
}

void Menu::moverAbajo() {
    if (indiceSeleccionado + 1 < opciones.size()) {
        botones[indiceSeleccionado].setSeleccionado(false);
        indiceSeleccionado++;
        botones[indiceSeleccionado].setSeleccionado(true);
        
        Accesibilidad::hablar(opciones[indiceSeleccionado].toAnsiString());
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