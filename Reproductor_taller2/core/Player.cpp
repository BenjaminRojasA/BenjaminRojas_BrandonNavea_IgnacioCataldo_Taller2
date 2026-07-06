#include "Player.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

Player::Player() : pistaActual(nullptr) {
    std::srand(std::time(0));
    pausado = false;
    modoAleatorio = false;
    modoRepeticion = 0;
}

Player::~Player() {
    bibliotecaCanciones.vaciar();
    listaDeReproduccion.vaciar();
}

void Player::cargarDatosDesdeDisco() {

    bibliotecaCanciones.vaciar();

    std::ifstream archivo("music_source.txt");
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string id, nom, art, alb;

            if (std::getline(ss, id, ',') &&
                std::getline(ss, nom, ',') &&
                std::getline(ss, art, ',') &&
                std::getline(ss, alb)) {

                bibliotecaCanciones.agregarAlFinal(new Song(id, nom, art, alb, 2026));
                }
        }
        archivo.close();
    } else {
        std::cout << "Error: No se pudo abrir music_source.txt" << std::endl;
    }

    std::ifstream lectorArchivo("song_ranking.txt");
    if (lectorArchivo.is_open()) {
        std::string bufferLinea;
        while (std::getline(lectorArchivo, bufferLinea)) {
            std::stringstream streamMecanismo(bufferLinea);
            std::string idLeido, reprosLeidas;
            if (std::getline(streamMecanismo, idLeido, ',') && std::getline(streamMecanismo, reprosLeidas)) {
                int nRepros = std::stoi(reprosLeidas);
                NodoLista<Song*>* actual = bibliotecaCanciones.getCabeza();
                while (actual != nullptr) {
                    if (actual->dato->getId() == idLeido) {
                        actual->dato->setReproducciones(nRepros);
                        break;
                    }
                    actual = actual->siguiente;
                }
            }
        }
        lectorArchivo.close();
    }
}

void Player::persistirDatosEnDisco() {
    std::ofstream escritorArchivo("song_ranking.txt");
    if (escritorArchivo.is_open()) {
        NodoLista<Song*>* actual = bibliotecaCanciones.getCabeza();
        while (actual != nullptr) {
            escritorArchivo << actual->dato->getId() << "," << actual->dato->getReproducciones() << "\n";
            actual = actual->siguiente;
        }
        escritorArchivo.close();
    }
}

LinkedList<Song*>& Player::getBiblioteca() { return bibliotecaCanciones; }
LinkedList<Song*>& Player::getListaReproduccion() { return listaDeReproduccion; }
Song* Player::getPistaActual() const { return pistaActual ? pistaActual->dato : nullptr; }

void Player::reproducirPistaInmediata(Song* cancion) {
    cancion->incrementarReproducciones();
    persistirDatosEnDisco();

    listaDeReproduccion.vaciar();
    listaDeReproduccion.agregarAlFinal(cancion);

    NodoLista<Song*>* auxiliar = bibliotecaCanciones.getCabeza();
    while (auxiliar != nullptr) {
        if (auxiliar->dato != cancion) {
            listaDeReproduccion.agregarAlFinal(auxiliar->dato);
        }
        auxiliar = auxiliar->siguiente;
    }
    pistaActual = listaDeReproduccion.getCabeza();
    pausado = false;
}

void Player::encolarPistaAlFinal(Song* cancion) {
    listaDeReproduccion.agregarAlFinal(cancion);
    if (pistaActual == nullptr) {
        pistaActual = listaDeReproduccion.getCabeza();
    }
}

void Player::avanzarPista() {
    if (pistaActual == nullptr) return;

    if (modoRepeticion == 1) {
        pausado = false;
        return;
    }

    int cantidad = 0;
    NodoLista<Song*>* temp = listaDeReproduccion.getCabeza();
    while (temp != nullptr) { cantidad++; temp = temp->siguiente; }

    if (modoAleatorio && cantidad > 1) {
        int randIndex;
        NodoLista<Song*>* nodoRandom;
        do {
            randIndex = std::rand() % cantidad;
            nodoRandom = listaDeReproduccion.getCabeza();
            for(int i = 0; i < randIndex; i++) nodoRandom = nodoRandom->siguiente;
        } while (nodoRandom == pistaActual);
        pistaActual = nodoRandom;
    } else {
        if (pistaActual->siguiente != nullptr) {
            pistaActual = pistaActual->siguiente;
        } else {
            if (modoRepeticion == 2) pistaActual = listaDeReproduccion.getCabeza();
        }
    }

    if (pistaActual != nullptr) {
        pistaActual->dato->incrementarReproducciones();
        persistirDatosEnDisco();
    }
    pausado = false;
}

void Player::retrocederPista() {
    if (pistaActual == nullptr) return;

    if (modoRepeticion == 1) {
        pausado = false;
        return;
    }

    int cantidad = 0;
    NodoLista<Song*>* temp = listaDeReproduccion.getCabeza();
    while (temp != nullptr) { cantidad++; temp = temp->siguiente; }

    if (modoAleatorio && cantidad > 1) {
        int randIndex;
        NodoLista<Song*>* nodoRandom;
        do {
            randIndex = std::rand() % cantidad;
            nodoRandom = listaDeReproduccion.getCabeza();
            for(int i = 0; i < randIndex; i++) nodoRandom = nodoRandom->siguiente;
        } while (nodoRandom == pistaActual);
        pistaActual = nodoRandom;
    } else {
        if (pistaActual != listaDeReproduccion.getCabeza()) {
            NodoLista<Song*>* previo = listaDeReproduccion.getCabeza();
            while (previo != nullptr && previo->siguiente != pistaActual) {
                previo = previo->siguiente;
            }
            if (previo != nullptr) pistaActual = previo;
        } else {
            if (modoRepeticion == 2) {
                NodoLista<Song*>* ultimo = listaDeReproduccion.getCabeza();
                while (ultimo && ultimo->siguiente != nullptr) ultimo = ultimo->siguiente;
                pistaActual = ultimo;
            }
        }
    }

    if (pistaActual != nullptr) {
        pistaActual->dato->incrementarReproducciones();
        persistirDatosEnDisco();
    }
    pausado = false;
}

void Player::alternarPausa() {
    if (pistaActual != nullptr) pausado = !pausado;
}

bool Player::estaPausado() const { return pausado; }
void Player::alternarAleatorio() { modoAleatorio = !modoAleatorio; }
bool Player::getModoAleatorio() const { return modoAleatorio; }

void Player::cambiarRepeticion() {
    modoRepeticion++;
    if (modoRepeticion > 2) modoRepeticion = 0;
}
int Player::getModoRepeticion() const { return modoRepeticion; }

void Player::mostrarColaDeReproduccion() const {
    NodoLista<Song*>* actual = listaDeReproduccion.getCabeza();
    if (actual == nullptr) {
        std::cout << "\nLa cola de reproduccion esta vacia.\n";
        return;
    }
    std::cout << "\n--- Cola de Reproduccion Actual ---\n";
    int i = 1;
    while (actual != nullptr) {
        if (actual == pistaActual) {
            std::cout << " -> " << i << ". " << actual->dato->getNombre() << " - " << actual->dato->getArtista();
            if (pausado) std::cout << " [PAUSADO]";
            std::cout << "\n";
        } else {
            std::cout << "    " << i << ". " << actual->dato->getNombre() << " - " << actual->dato->getArtista() << "\n";
        }
        actual = actual->siguiente;
        i++;
    }
}

void Player::mostrarListadoCanciones() const {
    NodoLista<Song*>* actual = bibliotecaCanciones.getCabeza();
    if (actual == nullptr) {
        std::cout << "\nNo hay canciones cargadas en el sistema.\n";
        return;
    }
    std::cout << "\n--- Listado Completo de Canciones ---\n";
    int i = 1;
    while (actual != nullptr) {
        std::cout << i << ". " << actual->dato->getNombre() << " - " << actual->dato->getArtista() << " (" << actual->dato->getAlbum() << ")\n";
        actual = actual->siguiente;
        i++;
    }
}