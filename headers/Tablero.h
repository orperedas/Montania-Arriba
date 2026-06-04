#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "Casilla.h"

class Tablero {
private:
    std::vector<Casilla*> casillas;
    std::vector<int> beneficios;
    std::vector<int> castigos;

protected:

    
public:
    Tablero();

    void crearTablero();
    Casilla obtenerCasilla(int posicion);
    void posicionesCasEspecial(std::vector<int>& posVector1, std::vector<int>& posVector2, int dimencionTablero);
    void asignarCasillas(std::vector<Casilla*>& casillas, int dimencionTablero);
    void dibujar(sf::RenderWindow& ventana);

    int getCantidadCasillas() const;
};

#endif // TABLERO_H