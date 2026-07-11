#include "headers/PantallaEstadisticas.h"
#include "headers/Estadisticas.h"
#include "headers/Accesibilidad.h"

std::vector<std::string> PantallaEstadisticas::generarOpcionesRanking() {
    Estadisticas stats;
    
    std::vector<DatosGanador> ranking = stats.obtenerRankingGanadores();
    
    std::vector<std::string> opciones;
    
    if (ranking.empty()) {
        opciones.push_back("Aún no hay ganadores registrados.");
    } else {
        for (size_t i = 0; i < ranking.size(); ++i) {
            if (i == 5) break;
            
std::string texto = std::to_string(i + 1) + ". En la partida con id " + 
                                std::to_string(ranking[i].idPartida) + 
                                " el jugador " + ranking[i].nombre + 
                                " ganó con " + std::to_string(ranking[i].tiradas) + " tiradas y con " + std::to_string(ranking[i].vida) + "vidas";
            opciones.push_back(texto);
        }
    }
    opciones.push_back("Volver al Menú Principal");
    
    return opciones;
}

PantallaEstadisticas::PantallaEstadisticas(float anchoVentana, float altoVentana)
    : menu(anchoVentana, altoVentana, "Ranking Mejores Jugadores", generarOpcionesRanking()) 
{
}

EstadoID PantallaEstadisticas::manejarEventos(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) menu.moverArriba();
        if (keyPressed->code == sf::Keyboard::Key::Down) menu.moverAbajo();
        
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            Accesibilidad::hablar("Volviendo al menú principal.");
            return EstadoID::MenuPrincipal; 
        }
    }
    
    return EstadoID::Ninguno;
}

void PantallaEstadisticas::actualizar() {
}

void PantallaEstadisticas::dibujar(sf::RenderWindow& ventana) {
    menu.dibujar(ventana);
}