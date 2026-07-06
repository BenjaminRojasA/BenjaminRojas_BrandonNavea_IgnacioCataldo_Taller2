SONG CPP

#include "Song.hpp"

Song::Song(std::string id, std::string nom, std::string art, std::string alb, int repros)
    : idCancion(id), nombre(nom), artista(art), album(alb), reproducciones(repros) {}

std::string Song::getId() const { return idCancion; }
std::string Song::getNombre() const { return nombre; }
std::string Song::getArtista() const { return artista; }
std::string Song::getAlbum() const { return album; }
int Song::getReproducciones() const { return reproducciones; }

void Song::incrementarReproducciones() { reproducciones++; }
void Song::setReproducciones(int cantidad) { reproducciones = cantidad; }