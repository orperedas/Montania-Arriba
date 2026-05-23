#ifndef ACCESIBILIDAD_H
#define ACCESIBILIDAD_H

#include <string>

class Accesibilidad {
private:
    static std::string mensaje;
    static bool condicion;

public:
    static void cargarAccesibilidad();
    static void descargarAccesibilidad();
    static void setCondicion(bool c);
        static void hablar(const std::string& m);
};

#endif