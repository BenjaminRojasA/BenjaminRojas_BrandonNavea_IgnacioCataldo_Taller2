#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stdexcept>

template <typename T>
class NodoLista {
public:
    T dato;
    NodoLista* siguiente;

    NodoLista(T valor) : dato(valor), siguiente(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    NodoLista<T>* cabeza;
    int cantidadElementos;

public:
    LinkedList() : cabeza(nullptr), cantidadElementos(0) {}

    ~LinkedList() {
        vaciar();
    }

    void agregarAlFinal(T valor) {
        NodoLista<T>* nuevoNodo = new NodoLista<T>(valor);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            NodoLista<T>* temporal = cabeza;
            while (temporal->siguiente != nullptr) {
                temporal = temporal->siguiente;
            }
            temporal->siguiente = nuevoNodo;
        }
        cantidadElementos++;
    }

    void vaciar() {
        while (cabeza != nullptr) {
            NodoLista<T>* temporal = cabeza;
            cabeza = cabeza->siguiente;
            delete temporal;
        }
        cantidadElementos = 0;
    }

    NodoLista<T>* getCabeza() const { return cabeza; }
    int getCantidad() const { return cantidadElementos; }

    T obtenerElemento(int indice) const {
        NodoLista<T>* temporal = cabeza;
        int contador = 0;
        while (temporal != nullptr) {
            if (contador == indice) return temporal->dato;
            contador++;
            temporal = temporal->siguiente;
        }
        throw std::out_of_range("Índice fuera de rango en la lista enlazada");
    }
};

#endif