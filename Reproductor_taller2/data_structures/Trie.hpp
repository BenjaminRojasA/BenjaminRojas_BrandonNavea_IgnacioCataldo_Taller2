#ifndef TRIE_HPP
#define TRIE_HPP

#include "LinkedList.hpp"
#include "../classes/Song.hpp"
#include <string>

class NodoTrie {
public:
    NodoTrie* hijos[256];
    LinkedList<Song*> cancionesCoincidentes;

    NodoTrie() {
        for (int i = 0; i < 256; i++) {
            hijos[i] = nullptr;
        }
    }

    ~NodoTrie() {
        for (int i = 0; i < 256; i++) {
            if (hijos[i] != nullptr) delete hijos[i];
        }
    }
};

class Trie {
private:
    NodoTrie* raiz;

    char convertirAMinuscula(char c) {
        if (c >= 'A' && c <= 'Z') return c + 32;
        return c;
    }

    void insertarSufijo(const std::string& textoSufijo, Song* cancion) {
        NodoTrie* actual = raiz;
        for (size_t i = 0; i < textoSufijo.length(); i++) {
            unsigned char indice = (unsigned char)convertirAMinuscula(textoSufijo[i]);
            if (actual->hijos[indice] == nullptr) {
                actual->hijos[indice] = new NodoTrie();
            }
            actual = actual->hijos[indice];

            // Evitar duplicar la misma canción en el mismo nodo
            bool yaExiste = false;
            NodoLista<Song*>* tempNodo = actual->cancionesCoincidentes.getCabeza();
            while (tempNodo != nullptr) {
                if (tempNodo->dato == cancion) {
                    yaExiste = true;
                    break;
                }
                tempNodo = tempNodo->siguiente;
            }
            if (!yaExiste) {
                actual->cancionesCoincidentes.agregarAlFinal(cancion);
            }
        }
    }

public:
    Trie() { raiz = new NodoTrie(); }
    ~Trie() { delete raiz; }

    void indexarCancion(Song* cancion) {
        std::string nombre = cancion->getNombre();
        std::string artista = cancion->getArtista();

        // Indexa todas las subcadenas del nombre
        for (size_t i = 0; i < nombre.length(); i++) {
            insertarSufijo(nombre.substr(i), cancion);
        }
        // Indexa todas las subcadenas del artista
        for (size_t i = 0; i < artista.length(); i++) {
            insertarSufijo(artista.substr(i), cancion);
        }
    }

    LinkedList<Song*> buscarCadena(const std::string& busqueda) {
        NodoTrie* actual = raiz;
        LinkedList<Song*> listaVacia;

        for (size_t i = 0; i < busqueda.length(); i++) {
            unsigned char indice = (unsigned char)convertirAMinuscula(busqueda[i]);
            if (actual->hijos[indice] == nullptr) {
                return listaVacia; // No hay resultados
            }
            actual = actual->hijos[indice];
        }
        return actual->cancionesCoincidentes;
    }
};

#endif