#ifndef BOTON_H
#define BOTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Boton {
    protected:
        sf::String textoBoton;
        sf::Vector2f posicionBoton;

        sf::Texture texturaBoton;
        sf::Sprite spriteBoton;
        sf::Text etiquetaBoton;
        sf::Font fuenteBoton;
    public:
        Boton(const sf::String& texto, const sf::Vector2f& posicion)
        :   textoBoton(texto),
            posicionBoton(posicion),
            spriteBoton(texturaBoton),
            etiquetaBoton(fuenteBoton, texto, 20)
            {
                // texturaBoton.loadFromFile("imagenes/menu_boton.png");
                // spriteBoton.setTexture(texturaBoton);
                // fuenteBoton.openFromFile("fuentes/sansation.ttf");
                // spriteBoton.setPosition(posicion);
                // etiquetaBoton.setPosition({posicion.x + 10.f, posicion.y + 10.f});
            }
        
        ~Boton() = default;

        void menuBoton(const sf::String& texto, sf::Vector2f posicion);
        void dibujar(sf::RenderWindow& ventana);
};

#endif // BOTON_H