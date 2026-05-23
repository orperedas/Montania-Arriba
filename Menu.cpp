#include "headers/Menu.h"
#include "headers/Accesibilidad.h"

Menu::Menu(float anchoVentana, float altoVentana, const sf::String& titulo, const std::vector<sf::String>& items) {
    if (!fuente.openFromFile("fuentes/sansation.ttf")) {
    }

    sf::Text textoTit(fuente);
    textoTit.setString(titulo);
    textoTit.setCharacterSize(50);
    textoTit.setFillColor(sf::Color::Cyan);
    textoTit.setPosition({anchoVentana / 2.0f - 250.f, 30.f});
    
    contenedorTitulo.push_back(textoTit);

    opciones = items;
    indiceSeleccionado = 0;

    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text texto(fuente);
        texto.setString(opciones[i]);
        texto.setCharacterSize(30);
        
        texto.setPosition({anchoVentana / 2.0f - 50.f, altoVentana / (opciones.size() + 2) * (i + 2)});
        
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
    // Dibujamos el elemento 0 (el único que hay) de nuestro vector de título
    ventana.draw(contenedorTitulo[0]); 
    
    for (const auto& texto : textosSFML) {
        ventana.draw(texto);
    }
}