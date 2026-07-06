
#ifndef SONG_HPP
#define SONG_HPP

#include <string>

class Song {
private:
    std::string idCancion;
    std::string nombre;
    std::string artista;
    std::string album;
    int reproducciones;

public:
    Song(std::string id, std::string nom, std::string art, std::string alb, int repros = 0);
    
    std::string getId() const;
    std::string getNombre() const;
    std::string getArtista() const;
    std::string getAlbum() const;
    int getReproducciones() const;
    
    void incrementarReproducciones();
    void setReproducciones(int cantidad);
};

#endif