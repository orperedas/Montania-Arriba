#include "headers/Accesibilidad.h"
#include "Tolk.h"
#include <SFML/System/String.hpp>

std::string Accesibilidad::mensaje = "";
bool Accesibilidad::condicion = true; 

void Accesibilidad::cargarAccesibilidad() {
    Tolk_TrySAPI(true);
    Tolk_Load();
}

void Accesibilidad::descargarAccesibilidad() {
    Tolk_Unload();
}

void Accesibilidad::setCondicion(bool c) {
    condicion = c;
}

void Accesibilidad::hablar(const std::string& m) {
    mensaje = m;
    
    if (condicion == true && Tolk_IsLoaded()) {
        sf::String traductor(mensaje);
        Tolk_Speak(traductor.toWideString().c_str());
    }
}