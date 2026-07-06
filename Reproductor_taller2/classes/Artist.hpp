#ifndef ARTIST_HPP
#define ARTIST_HPP

#include <string>

class Artist {
private:
    std::string nombreArtista;
    int totalReproducciones;

public:
    Artist();
    Artist(std::string nombre, int repros);
    
    std::string getNombre() const;
    int getTotalReproducciones() const;
    void acumularReproducciones(int cantidad);
};

#endif