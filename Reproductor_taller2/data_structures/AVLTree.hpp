#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "../classes/Song.hpp"
#include "LinkedList.hpp"

class NodoAVL {
public:
    Song* cancion;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(Song* s) : cancion(s), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

class AVLTree {
private:
    NodoAVL* raiz;

    int getAltura(NodoAVL* n) { return n ? n->altura : 0; }
    int getMayor(int a, int b) { return (a > b) ? a : b; }

    int obtenerBalance(NodoAVL* n) {
        return n ? getAltura(n->izquierdo) - getAltura(n->derecho) : 0;
    }

    NodoAVL* rotarDerecha(NodoAVL* y) {
        NodoAVL* x = y->izquierdo;
        NodoAVL* T2 = x->derecho;
        x->derecho = y;
        y->izquierdo = T2;
        y->altura = getMayor(getAltura(y->izquierdo), getAltura(y->derecho)) + 1;
        x->altura = getMayor(getAltura(x->izquierdo), getAltura(x->derecho)) + 1;
        return x;
    }

    NodoAVL* rotarIzquierda(NodoAVL* x) {
        NodoAVL* y = x->derecho;
        NodoAVL* T2 = y->izquierdo; // Enlazamos subárbol izquierdo de y a la derecha de x
        y->izquierdo = x;
        x->derecho = T2;
        x->altura = getMayor(getAltura(x->izquierdo), getAltura(x->derecho)) + 1;
        y->altura = getMayor(getAltura(y->izquierdo), getAltura(y->derecho)) + 1;
        return y;
    }

    NodoAVL* insertarNodo(NodoAVL* nodo, Song* cancionNueva) {
        if (!nodo) return new NodoAVL(cancionNueva);

        if (cancionNueva->getNombre() < nodo->cancion->getNombre()) {
            nodo->izquierdo = insertarNodo(nodo->izquierdo, cancionNueva);
        } else {
            nodo->derecho = insertarNodo(nodo->derecho, cancionNueva);
        }

        nodo->altura = 1 + getMayor(getAltura(nodo->izquierdo), getAltura(nodo->derecho));
        int balance = obtenerBalance(nodo);

        // Caso Izquierda Izquierda
        if (balance > 1 && cancionNueva->getNombre() < nodo->izquierdo->cancion->getNombre())
            return rotarDerecha(nodo);

        // Caso Derecha Derecha
        if (balance < -1 && cancionNueva->getNombre() > nodo->derecho->cancion->getNombre())
            return rotarIzquierda(nodo);

        // Caso Izquierda Derecha
        if (balance > 1 && cancionNueva->getNombre() > nodo->izquierdo->cancion->getNombre()) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }

        // Caso Derecha Izquierda
        if (balance < -1 && cancionNueva->getNombre() < nodo->derecho->cancion->getNombre()) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    void recorridoInOrder(NodoAVL* nodo, LinkedList<Song*>& listaDestino) {
        if (!nodo) return;
        recorridoInOrder(nodo->izquierdo, listaDestino);
        listaDestino.agregarAlFinal(nodo->cancion);
        recorridoInOrder(nodo->derecho, listaDestino);
    }

    void liberarMemoria(NodoAVL* nodo) {
        if (!nodo) return;
        liberarMemoria(nodo->izquierdo);
        liberarMemoria(nodo->derecho);
        delete nodo;
    }

public:
    AVLTree() : raiz(nullptr) {}
    ~AVLTree() { liberarMemoria(raiz); }

    void insertar(Song* cancionNueva) { raiz = insertarNodo(raiz, cancionNueva); }

    LinkedList<Song*> obtenerListaOrdenada() {
        LinkedList<Song*> lista;
        recorridoInOrder(raiz, lista);
        return lista;
    }
};

#endif