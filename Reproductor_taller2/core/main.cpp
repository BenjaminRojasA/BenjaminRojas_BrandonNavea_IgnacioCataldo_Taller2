#include <iostream>
#include <string>
#include "Player.hpp"
#include "Trie.hpp"
#include "menus.hpp"

int main() {
    Player reproductorSistema;
    Trie motorDeBusqueda;
    
    reproductorSistema.cargarDatosDesdeDisco();

    NodoLista<Song*>* lectorNodos = reproductorSistema.getBiblioteca().getCabeza();
    while (lectorNodos != nullptr) {
        std::string nombreMin = lectorNodos->dato->getNombre();
        for (char &c : nombreMin) c = std::tolower(c); // Convierte a minúsculas
         motorDeBusqueda.indexarCancion(lectorNodos->dato);
        lectorNodos = lectorNodos->siguiente;
    }

    std::string entradaUsuario = "";
    char selectorMenu = ' ';

    while (selectorMenu != 'X' && selectorMenu != 'x') {

        renderizarMenuPrincipal(reproductorSistema, motorDeBusqueda);

        std::cin.clear();

        std::cin >> entradaUsuario;

        if (!entradaUsuario.empty()) {
            selectorMenu = entradaUsuario[0];
        } else {
            selectorMenu = ' ';
        }

        if (selectorMenu == 'F' || selectorMenu == 'f') {
            ventanaBusqueda(reproductorSistema, motorDeBusqueda);
        } else if (selectorMenu == 'T' || selectorMenu == 't') {
            ventanaRankings(reproductorSistema);
        } else if (selectorMenu == 'Q' || selectorMenu == 'q') {
            reproductorSistema.retrocederPista();
        } else if (selectorMenu == 'E' || selectorMenu == 'e') {
            reproductorSistema.avanzarPista();
        } else if (selectorMenu == 'W' || selectorMenu == 'w') {
            reproductorSistema.alternarPausa();
        } else if (selectorMenu == 'S' || selectorMenu == 's') {
            reproductorSistema.alternarAleatorio();
        } else if (selectorMenu == 'R' || selectorMenu == 'r') {
            reproductorSistema.cambiarRepeticion();
        } else if (selectorMenu == 'A' || selectorMenu == 'a') {
            refrescarPantalla();
            reproductorSistema.mostrarColaDeReproduccion();
            std::cout << "\nPresione ENTER para volver...";
            std::cin.clear(); std::cin.ignore(10000, '\n'); std::cin.get();
        } else if (selectorMenu == 'L' || selectorMenu == 'l') {
            refrescarPantalla();
            reproductorSistema.mostrarListadoCanciones();
            std::cout << "\nPresione ENTER para volver...";
            std::cin.clear(); std::cin.ignore(10000, '\n'); std::cin.get();
        }
    }

    NodoLista<Song*>* nodoLimpieza = reproductorSistema.getBiblioteca().getCabeza();
    while (nodoLimpieza != nullptr) {
        nodoLimpieza = nodoLimpieza->siguiente;
    }

    return 0;
}