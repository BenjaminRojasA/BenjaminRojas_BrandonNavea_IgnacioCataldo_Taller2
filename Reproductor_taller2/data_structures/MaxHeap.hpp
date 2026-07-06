#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

template <typename T>
class MaxHeap {
private:
    T* arregloDatos;
    int capacidadMaxima;
    int cantidadElementos; // <-- Sinónimo natural en lugar de tamaño

    bool evaluarPrioridadSuperior(T elementoA, T elementoB);
    void desplazarAbajo(int indice);
    void desplazarArriba(int indice);

public:
    MaxHeap(int capacidad);
    ~MaxHeap();

    void insertar(T elemento);
    T extraerMaximo();
    int getCantidad() const; // <-- Nombre limpio y lógico
};

#include "MaxHeap.cpp"

#endif