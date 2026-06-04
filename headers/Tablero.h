#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "Casilla.h"

class Tablero {
private:
    std::vector<Casilla*> casillas;
    std::vector<int> beneficios;
    std::vector<int> castigos;

    int base;

    
public:
    Tablero();

    void crearTablero();
    Casilla obtenerCasilla(int posicion);
    void posicionesCasEspecial(std::vector<int>& posiciones, int dimencionTablero);

    int getCantidadCasillas() const;
};

#endif // TABLERO_H