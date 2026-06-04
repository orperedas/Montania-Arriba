#include "headers/Accesibilidad.h"
#include "headers/Boton.h"
#include "headers/Menu.h"


Menu::Menu(float anchoVentana, float altoVentana, const sf::String& titulo, const std::vector<sf::String>& items) {
    if (!fuente.openFromFile("fuentes/sansation.ttf")) {
    }

    sf::Text textoTit(fuente);
    textoTit.setString(titulo);
    textoTit.setCharacterSize(50);
    textoTit.setFillColor(sf::Color::Cyan);
    textoTit.setPosition({(anchoVentana - 250.f)/ 2.0f, 30.f});
    
    contenedorTitulo.push_back(textoTit);

    opciones = items;
    indiceSeleccionado = 0;

    for (size_t i = 0; i < opciones.size(); ++i) {

        float xPos = (anchoVentana - 200.f) / 2.0f;
        float yPos = altoVentana / (opciones.size() + 2) * (i + 2);

        sf::Vector2f posicionElemento = {(anchoVentana - 50.f) / 2.0f, altoVentana / (opciones.size() + 2) * (i + 2)};

        Boton nuevoBoton(opciones[i], posicionElemento);
        nuevoBoton.menuBoton(opciones[i], posicionElemento);
        botones.push_back(nuevoBoton);

        sf::Text texto(fuente);
        texto.setString(opciones[i]);
        texto.setCharacterSize(30);
        texto.setPosition(posicionElemento);

        if (i == 0) {
            texto.setFillColor(sf::Color::Yellow);
        } else {
            texto.setFillColor(sf::Color::White);
        }
        
        textosSFML.push_back(texto);
    }

    std::string mensajeInicial = titulo.toAnsiString() + ". " + opciones[indiceSeleccionado].toAnsiString();
    Accesibilidad::hablar(mensajeInicial);
}

void Menu::moverArriba() {
    if (indiceSeleccionado - 1 >= 0) {
        textosSFML[indiceSeleccionado].setFillColor(sf::Color::White);
        indiceSeleccionado--;
        textosSFML[indiceSeleccionado].setFillColor(sf::Color::Yellow);
        
        Accesibilidad::hablar(opciones[indiceSeleccionado].toAnsiString());
    }
}

void Menu::moverAbajo() {
    if (indiceSeleccionado + 1 < opciones.size()) {
        textosSFML[indiceSeleccionado].setFillColor(sf::Color::White);
        indiceSeleccionado++;
        textosSFML[indiceSeleccionado].setFillColor(sf::Color::Yellow);
        
        Accesibilidad::hablar(opciones[indiceSeleccionado].toAnsiString());
    }
}

int Menu::obtenerSeleccion() const {
    return indiceSeleccionado;
}

void Menu::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(contenedorTitulo[0]); 
    
    // for (auto& boton : botones) {
    //    boton.dibujar(ventana);
    // }

    for (const auto& texto : textosSFML) {
        ventana.draw(texto);
    }
}