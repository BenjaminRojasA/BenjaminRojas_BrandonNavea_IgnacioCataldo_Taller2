template <typename T>
MaxHeap<T>::MaxHeap(int capacidad) : capacidadMaxima(capacidad), cantidadElementos(0) {
    arregloDatos = new T[capacidadMaxima];
}

template <typename T>
MaxHeap<T>::~MaxHeap() {
    delete[] arregloDatos;
}

template <typename T>
bool MaxHeap<T>::evaluarPrioridadSuperior(T elementoA, T elementoB) {
    if (elementoA->getReproducciones() != elementoB->getReproducciones()) {
        return elementoA->getReproducciones() > elementoB->getReproducciones();
    }
    if (elementoA->getNombre() != elementoB->getNombre()) {
        return elementoA->getNombre() < elementoB->getNombre();
    }
    return elementoA->getArtista() < elementoB->getArtista();
}

template <typename T>
void MaxHeap<T>::desplazarAbajo(int indice) {
    int mayorPrioridad = indice;
    int hijoIzquierdo = 2 * indice + 1;
    int hijoDerecho = 2 * indice + 2;

    if (hijoIzquierdo < cantidadElementos && evaluarPrioridadSuperior(arregloDatos[hijoIzquierdo], arregloDatos[mayorPrioridad])) {
        mayorPrioridad = hijoIzquierdo;
    }
    if (hijoDerecho < cantidadElementos && evaluarPrioridadSuperior(arregloDatos[hijoDerecho], arregloDatos[mayorPrioridad])) {
        mayorPrioridad = hijoDerecho;
    }

    if (mayorPrioridad != indice) {
        T aux = arregloDatos[indice];
        arregloDatos[indice] = arregloDatos[mayorPrioridad];
        arregloDatos[mayorPrioridad] = aux;
        desplazarAbajo(mayorPrioridad);
    }
}

template <typename T>
void MaxHeap<T>::desplazarArriba(int indice) {
    while (indice > 0 && evaluarPrioridadSuperior(arregloDatos[indice], arregloDatos[(indice - 1) / 2])) {
        T aux = arregloDatos[indice];
        arregloDatos[indice] = arregloDatos[(indice - 1) / 2];
        arregloDatos[(indice - 1) / 2] = aux;
        indice = (indice - 1) / 2;
    }
}

template <typename T>
void MaxHeap<T>::insertar(T elemento) {
    if (cantidadElementos >= capacidadMaxima) return;
    arregloDatos[cantidadElementos] = elemento;
    desplazarArriba(cantidadElementos);
    cantidadElementos++;
}

template <typename T>
T MaxHeap<T>::extraerMaximo() {
    if (cantidadElementos <= 0) return nullptr;
    T raizMaximo = arregloDatos[0];
    arregloDatos[0] = arregloDatos[cantidadElementos - 1];
    cantidadElementos--;
    desplazarAbajo(0);
    return raizMaximo;
}

template <typename T>
int MaxHeap<T>::getCantidad() const {
    return cantidadElementos;
}