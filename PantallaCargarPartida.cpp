#include "headers/PantallaCargarPartida.h"
#include "headers/PartidaArchivo.h"
#include "headers/Accesibilidad.h"

std::vector<std::string> PantallaCargarPartida::generarOpcionesMenu(std::vector<int>& idsCargados) {
    PartidaArchivo archivo;
    idsCargados = archivo.obtenerIdsPartidasActivas();
    
    std::vector<std::string> opciones;
    
    if (idsCargados.empty()) {
        opciones.push_back("No hay partidas guardadas");
    } else {
        for (int id : idsCargados) {
            opciones.push_back("Cargar Partida ID: " + std::to_string(id));
        }
    }
    opciones.push_back("Volver al Menú Principal");
    
    return opciones;
}

PantallaCargarPartida::PantallaCargarPartida(float anchoVentana, float altoVentana, Partida& p)
    : partida(p), 
      menu(anchoVentana, altoVentana, "Cargar Partida", generarOpcionesMenu(idsActivos)) 
{
}

EstadoID PantallaCargarPartida::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) menu.moverArriba();
        if (keyPressed->code == sf::Keyboard::Key::Down) menu.moverAbajo();
        
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            int seleccion = menu.obtenerSeleccion();
                        if (seleccion == idsActivos.size()) {
                return EstadoID::MenuPrincipal;
            }
            if (idsActivos.empty()) {
                return EstadoID::MenuPrincipal; 
            }
            
            
            int idElegido = idsActivos[seleccion];
            PartidaArchivo archivo;
            
            partida = archivo.leer(idElegido - 1); 
            
            Accesibilidad::hablar("Partida cargada. Retomando juego.");
            return EstadoID::juegoCargado;
        }
    }
    
    return EstadoID::Ninguno;
}

void PantallaCargarPartida::actualizar() {
}

void PantallaCargarPartida::dibujar(sf::RenderWindow& ventana) {
    menu.dibujar(ventana);
}