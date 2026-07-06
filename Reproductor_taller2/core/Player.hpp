#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Song.hpp"
#include "LinkedList.hpp"
#include <string>

class Player {
private:
    LinkedList<Song*> bibliotecaCanciones;
    LinkedList<Song*> listaDeReproduccion;
    NodoLista<Song*>* pistaActual;

    bool pausado;
    bool modoAleatorio;
    int modoRepeticion;

    void persistirDatosEnDisco();

public:
    Player();
    ~Player();

    void cargarDatosDesdeDisco();
    void reproducirPistaInmediata(Song* cancion);
    void encolarPistaAlFinal(Song* cancion);
    void avanzarPista();
    void retrocederPista();

    LinkedList<Song*>& getBiblioteca();
    LinkedList<Song*>& getListaReproduccion();
    Song* getPistaActual() const;

    void alternarPausa();
    bool estaPausado() const;
    void alternarAleatorio();
    bool getModoAleatorio() const;
    void cambiarRepeticion();
    int getModoRepeticion() const;
    void mostrarColaDeReproduccion() const;
    void mostrarListadoCanciones() const;
};

#endif