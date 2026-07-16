#include "headers/PantallaCreditos.h"
#include "headers/Accesibilidad.h"
#include "headers/Fuente.h"
#include "headers/Visual.h"

PantallaCreditos::PantallaCreditos(float anchoVentana, float altoVentana) 
    : textoTitulo(Fuente::getFuente(IDFuente::TituloPantalla)),
      textoSalir(Fuente::getFuente(IDFuente::TextoBotonMenu))
{
    textosCreditos = {
        "Lucas Matías Burgos. Legajo 31687",
        "Otto Rene Pereda. Legajo 31679",
        "Librería Utilizada para entorno gráfico y sonoro: SFML",
        "Efectos de sonidos y música creados con herramientas IA."
    };

    visual.fondoVentanaTablero(
        {anchoVentana * 0.6f, altoVentana * 0.6f},
        {anchoVentana / 2.f, altoVentana / 2.f} 
    );

    textoTitulo.setString("Creditos");
    textoTitulo.setCharacterSize(34);
    textoTitulo.setFillColor(visual.getColor(IDVisual::Blanco_Solido));
    sf::FloatRect boundsTitulo = textoTitulo.getLocalBounds();
    textoTitulo.setPosition({(anchoVentana - boundsTitulo.size.x) / 2.f, 200.f});

    textoSalir.setString("Presiona Escape para volver al Menu Principal");
    textoSalir.setCharacterSize(20);
    textoSalir.setFillColor(visual.getColor(IDVisual::NaranjaClaro_Solido));
    sf::FloatRect boundsSalir = textoSalir.getLocalBounds();
    textoSalir.setPosition({(anchoVentana - boundsSalir.size.x) / 2.f, altoVentana - 80.f});

    float startY = 280.f;
    float spacingY = 80.f;
    float anchoCaja = 600.f;
    float altoCaja = 50.f;

    for (size_t i = 0; i < textosCreditos.size(); ++i) {
        sf::RectangleShape caja({anchoCaja, altoCaja});
        caja.setFillColor(visual.getColor(IDVisual::Negro_Transparente)); 
        caja.setOutlineThickness(2.f);
        caja.setOutlineColor(visual.getColor(IDVisual::Azul_Solido));
        caja.setPosition({(anchoVentana - anchoCaja) / 2.f, startY + (i * spacingY)});
        cajas.push_back(caja);

        sf::Text texto(Fuente::getFuente(IDFuente::TextoBotonMenu));
        texto.setString(textosCreditos[i]);
        texto.setCharacterSize(24);
        texto.setFillColor(visual.getColor(IDVisual::Blanco_Solido));
        
        sf::FloatRect boundsTexto = texto.getLocalBounds();
        texto.setPosition({
            caja.getPosition().x + 20.f, 
            caja.getPosition().y + (altoCaja - boundsTexto.size.y) / 2.f - 5.f
        });
        textosSfml.push_back(texto);
    }

    Accesibilidad::hablar("Pantalla de créditos. Presiona los números del 1 al " + std::to_string(textosCreditos.size()) + " para leer cada crédito. Presiona Escape para volver.");
}

EstadoID PantallaCreditos::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            Accesibilidad::hablar("Volviendo al menú principal.");
            return EstadoID::MenuPrincipal;
        }

        int numPresionado = -1;
        if (keyPressed->code == sf::Keyboard::Key::Num1) numPresionado = 0;
        else if (keyPressed->code == sf::Keyboard::Key::Num2) numPresionado = 1;
        else if (keyPressed->code == sf::Keyboard::Key::Num3) numPresionado = 2;
        else if (keyPressed->code == sf::Keyboard::Key::Num4) numPresionado = 3;
        else if (keyPressed->code == sf::Keyboard::Key::Num5) numPresionado = 4;
        else if (keyPressed->code == sf::Keyboard::Key::Num6) numPresionado = 5;
        else if (keyPressed->code == sf::Keyboard::Key::Num7) numPresionado = 6;
        else if (keyPressed->code == sf::Keyboard::Key::Num8) numPresionado = 7;
        else if (keyPressed->code == sf::Keyboard::Key::Num9) numPresionado = 8;

        if (numPresionado != -1 && numPresionado < static_cast<int>(textosCreditos.size())) {
            Accesibilidad::hablar(textosCreditos[numPresionado]);
        }
    }
    
    return EstadoID::Ninguno;
}

void PantallaCreditos::actualizar() {
}

void PantallaCreditos::dibujar(sf::RenderWindow& ventana) {
    visual.dibujar(ventana);

    ventana.draw(textoTitulo);
    
    for (size_t i = 0; i < cajas.size(); ++i) {
        ventana.draw(cajas[i]);
        ventana.draw(textosSfml[i]);
    }

    ventana.draw(textoSalir);
}