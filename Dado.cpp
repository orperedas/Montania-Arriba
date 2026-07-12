#include <iostream>
#include <cstdlib>
#include <string>

#include "headers/Accesibilidad.h"
#include "headers/Dado.h"
#include "headers/Imagen.h"
#include "headers/Sonido.h"

Dado::Dado(sf::Vector2f posicion) 
: spriteDado(texturaDado),
    animando(false),
    contadorCambios(0),
    resultadoFinal(1),
    texturaDado(Imagen::getImagen(IDImagen::Dado))
{
    spriteDado.setTexture(texturaDado, true);
    spriteDado.setOrigin({40.0f, 40.0f});
    spriteDado.setPosition(posicion);
    spriteDado.setTextureRect(sf::IntRect({0, 80}, {80, 160}));
    spriteDado.setScale({1.3f, 1.3f});
}

int Dado::tirar() {
    if (!animando) {
        animando = true;
        contadorCambios = 0;
        
        resultadoFinal = (rand() % 6) + 1; 
        Sonido::reproducir(IDSonido::TirarDado);
        relojAnimacion.restart(); 
    }
    return resultadoFinal; 
}

void Dado::actualizar() {
    if (animando) {
        if (relojAnimacion.getElapsedTime()>= sf::seconds(0.1f)) {
            spriteDado.rotate(sf::degrees(45.f));
            
            contadorCambios++;
            
            int cuadroActual = contadorCambios % 6;
            int posX = cuadroActual * 80 ;

            spriteDado.setTextureRect(sf::IntRect{{posX, 0}, {80, 80}});

            relojAnimacion.restart();

            if (contadorCambios >= 12) {
                animando = false;
                
                spriteDado.setRotation(sf::degrees(359.f)); 
                
                int finalX = (resultadoFinal - 1) * 80;
                spriteDado.setTextureRect({{finalX, 80}, {80, 160}});
                
                Accesibilidad::hablar("Salió un " + std::to_string(resultadoFinal));
            }
        }
    }
}

void Dado::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(spriteDado, states);
}

bool Dado::estaAnimando() const {
    return animando;
}