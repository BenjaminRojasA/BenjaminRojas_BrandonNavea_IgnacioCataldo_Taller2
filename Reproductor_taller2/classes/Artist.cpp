#include "Artist.hpp"

Artist::Artist() : nombreArtista(""), totalReproducciones(0) {}
Artist::Artist(std::string nombre, int repros) : nombreArtista(nombre), totalReproducciones(repros) {}

std::string Artist::getNombre() const { return nombreArtista; }
int Artist::getTotalReproducciones() const { return totalReproducciones; }
void Artist::acumularReproducciones(int cantidad) { totalReproducciones += cantidad; }