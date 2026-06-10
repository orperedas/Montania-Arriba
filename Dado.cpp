#include "headers/Dado.h"
#include "headers/Accesibilidad.h"
#include <iostream>
#include <cstdlib>
#include <string>

Dado::Dado(sf::Vector2f posicion) : animando(false), contadorCambios(0), resultadoFinal(1) {
    if (!texturaDado.loadFromFile("imagenes/dado.png")) {
        std::cerr << "Error al cargar la imagen del dado." << std::endl;
    }
    
    spriteDado.setTexture(texturaDado);
    
    sf::FloatRect limites = spriteDado.getLocalBounds();
    spriteDado.setOrigin({limites.size.x / 2.0f, limites.size.y / 2.0f});
    
    spriteDado.setPosition(posicion);
}

int Dado::tirar() {
    if (!animando) {
        animando = true;
        contadorCambios = 0;
        
        resultadoFinal = (rand() % 6) + 1; 
        
        Accesibilidad::hablar("Tirando dado...");
        relojAnimacion.restart(); 
    }
    return resultadoFinal; // Devolvemos el int tal cual lo pediste
}

void Dado::actualizar() {
    if (animando) {
        if (relojAnimacion.getElapsedTime().asMilliseconds() > 30) {
            
            spriteDado.rotate(45.f);
            
            contadorCambios++;
            relojAnimacion.restart();

            if (contadorCambios >= 20) {
                animando = false;
                
                spriteDado.setRotation(0.f); 
                
                Accesibilidad::hablar("Salió un " + std::to_string(resultadoFinal));
            }
        }
    }
}

void Dado::draw(sf::RenderWindow& ventana) {
    ventana.draw(spriteDado);
}

bool Dado::estaAnimando() const {
    return animando;
}