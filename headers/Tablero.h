#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "Casilla.h"

class Tablero {
private:
    int base;
    std::vector<Casilla*> casillas;
    std::vector<int> beneficios;
    std::vector<int> castigos;
    sf::Texture texturaNormal;
    sf::Texture texturaBeneficio;
    sf::Texture texturaCastigo;
    public:
Tablero(int baseNum);

    void crearTablero();
    void posicionesCasEspecial(std::vector<int>& posVector1, std::vector<int>& posVector2, int dimencionTablero);
    void asignarCasillas(std::vector<Casilla*>& casillas, int dimencionTablero);
    void dibujar(sf::RenderTarget& target) const;
    void actualizar();
    int getCantidadCasillas() const;
Casilla* obtenerCasilla(int posicion);
};

#endif // TABLERO_H