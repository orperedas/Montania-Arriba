#include "headers/Musica.h"
#include <iostream>

sf::Music Musica::reproductor;
std::map<IDMusica, std::string> Musica::rutas;

void Musica::inicializar() {
    std::cout << "LOG [Musica]: Inicializando el sistema de musica..." << std::endl;
    
    rutas[IDMusica::FondoMenu] = "musica/menu.wav";
    rutas[IDMusica::FondoTablero] = "musica/fondo.wav";
    
    std::cout << "LOG [Musica]: Rutas registradas correctamente (" << rutas.size() << " audios)." << std::endl;
    
    reproductor.setVolume(25.f); 
    std::cout << "LOG [Musica]: Volumen configurado al 20%." << std::endl;
}

void Musica::reproducir(IDMusica id, bool loop) {
    std::cout << "LOG [Musica]: Solicitud para reproducir ID de musica: " << static_cast<int>(id) << std::endl;
    
    auto it = rutas.find(id);
    
    if (it != rutas.end()) {
        std::cout << "LOG [Musica]: Archivo encontrado en la lista -> " << it->second << std::endl;
        
        // Intentamos abrir el archivo físico
        if (!reproductor.openFromFile(it->second)) {
            std::cerr << "LOG ERROR [Musica]: SFML NO pudo abrir el archivo físico: " << it->second << std::endl;
            std::cerr << " -> Verifica que la carpeta 'musica' este al lado de tu ejecutable y el nombre sea exacto." << std::endl;
            return;
        }
        
        std::cout << "LOG [Musica]: Archivo abierto con EXITO. Iniciando reproduccion..." << std::endl;
        reproductor.setLooping(loop);
        reproductor.play();
        
    } else {
        std::cerr << "LOG ERROR [Musica]: El ID solicitado NO existe en el mapa." << std::endl;
    }
}

void Musica::pausar() {
    std::cout << "LOG [Musica]: Musica pausada." << std::endl;
    reproductor.pause();
}

void Musica::detener() {
    std::cout << "LOG [Musica]: Musica detenida." << std::endl;
    reproductor.stop();
}

void Musica::setVolumen(float volumen) {
    std::cout << "LOG [Musica]: Modificando volumen a: " << volumen << std::endl;
    reproductor.setVolume(volumen);
}