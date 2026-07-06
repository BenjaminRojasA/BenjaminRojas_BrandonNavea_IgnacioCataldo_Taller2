#include "menus.hpp"
#include "Player.hpp"
#include "Trie.hpp"
#include <iostream>
#include <string>

void refrescarPantalla() {
    std::system("cls");
}

void renderizarMenuPrincipal(Player& reproductor, Trie& buscador) {
    refrescarPantalla();
    Song* trackActual = reproductor.getPistaActual();

    if (trackActual != nullptr) {
        std::string estadoReproduccion = reproductor.estaPausado() ? "Pausado" : "Reproduciendo";

        std::cout << estadoReproduccion << " (";
        if (reproductor.getModoAleatorio()) {
            std::cout << "S-";
        }
        std::cout << "R" << reproductor.getModoRepeticion() << "): " << trackActual->getNombre() << "\n";
        std::cout << "Artista: " << trackActual->getArtista() << "\n";
        std::cout << "Album: " << trackActual->getAlbum() << "\n\n";
    } else {
        std::cout << "Ninguna pista en reproduccion\n\n";
    }

    std::cout << "Opciones:\n";
    std::cout << "W - Reproducir/Pausar\n";
    std::cout << "Q - Pista Anterior\n";
    std::cout << "E - Pista Siguiente\n";
    std::cout << "S - Activar/Desactivar modo aleatorio\n";
    std::cout << "R - Repeticion (Desactivado/Repetir una/Repetir todas)\n";
    std::cout << "A - Ver lista de reproduccion actual\n";
    std::cout << "L - Listado de canciones\n";
    std::cout << "F - Buscar canciones\n";
    std::cout << "T - TOP 10 Artistas y Canciones\n";
    std::cout << "X - Salir\n";
    std::cout << "Ingrese Opcion: ";
}

void ventanaBusqueda(Player& reproductor, Trie& buscador) {
    refrescarPantalla();
    std::cout << "Busqueda de canciones\n";
    std::cout << "Buscar canciones que contengan (o ENTER para cancelar): ";

    std::string cadenaEntrada;
    std::cin.clear();
    std::cin.ignore(10000, '\n'); // Limpia la basura residual del menu principal
    std::getline(std::cin, cadenaEntrada);

    for (char &c : cadenaEntrada) {
        c = std::tolower(c);
    }

    LinkedList<Song*> resultados = buscador.buscarCadena(cadenaEntrada);
    if (resultados.getCantidad() == 0) {
        std::cout << "No existen coincidencias de texto. Presione ENTER para regresar.";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin.get();
        return;
    }

    refrescarPantalla();
    std::cout << "Canciones que contienen \"" << cadenaEntrada << "\":\n";

    int contador = 1;
    NodoLista<Song*>* actual = resultados.getCabeza();
    while (actual != nullptr) {
        std::cout << contador << ". " << actual->dato->getNombre() << " - " << actual->dato->getArtista() << "\n";
        actual = actual->siguiente;
        contador++;
    }

    std::string comando;
    bool enMenuBusqueda = true;

    while (enMenuBusqueda) {
        std::cout << "\nOpciones:\n";
        std::cout << "R<num> - Reproducir cancion seleccionada\n";
        std::cout << "A<num> - Agregar cancion seleccionada al final de la lista de reproduccion actual\n";
        std::cout << "F - Repetir busqueda con un texto diferente\n";
        std::cout << "V - Volver al menu principal\n";
        std::cout << "Ingrese comando: ";

        std::cin >> comando;

        if (comando == "V" || comando == "v") {
            enMenuBusqueda = false;
        }
        else if (comando == "F" || comando == "f") {
            ventanaBusqueda(reproductor, buscador); // Permite repetir la busqueda altiro
            enMenuBusqueda = false;
        }
        else if (comando.length() > 1 && (comando[0] == 'R' || comando[0] == 'r' || comando[0] == 'A' || comando[0] == 'a')) {
            char accion = comando[0];
            std::string strNum = comando.substr(1);

            try {
                int num = std::stoi(strNum);
                if (num > 0 && num < contador) {
                    NodoLista<Song*>* temp = resultados.getCabeza();
                    for (int i = 1; i < num; i++) temp = temp->siguiente;
                    Song* cancionObjetivo = temp->dato;

                    if (accion == 'R' || accion == 'r') {
                        reproductor.reproducirPistaInmediata(cancionObjetivo);
                        enMenuBusqueda = false;
                    }
                    else if (accion == 'A' || accion == 'a') {
                        reproductor.encolarPistaAlFinal(cancionObjetivo);
                        std::cout << "Cancion agregada a la cola.\n";
                    }
                } else {
                    std::cout << "Numero fuera de rango.\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Comando invalido.\n";
            }
        } else {
            std::cout << "Comando invalido.\n";
        }
    }
}

void ventanaRankings(Player& reproductor) {
    refrescarPantalla();
    std::cout << "Ranking TOP\n\n";
    std::cout << "C - Top 10 canciones mas escuchadas\n";
    std::cout << "A - Top 10 artistas mas escuchados\n";
    std::cout << "X - Salir\n\n";
    std::cout << "Ingrese Opcion: ";

    char opcionRanking;
    std::cin >> opcionRanking;

    if (opcionRanking == 'C' || opcionRanking == 'c') {
        refrescarPantalla();
        std::cout << "Ranking TOP 10 Canciones mas escuchadas:\n\n";

        int cantidadCanciones = reproductor.getBiblioteca().getCantidad();
        Song** arregloCanciones = new Song*[cantidadCanciones];
        NodoLista<Song*>* actual = reproductor.getBiblioteca().getCabeza();
        for (int i = 0; i < cantidadCanciones; i++) {
            arregloCanciones[i] = actual->dato;
            actual = actual->siguiente;
        }

        for (int i = 0; i < cantidadCanciones - 1; i++) {
            for (int j = 0; j < cantidadCanciones - i - 1; j++) {
                if (arregloCanciones[j]->getReproducciones() < arregloCanciones[j + 1]->getReproducciones()) {
                    Song* temp = arregloCanciones[j];
                    arregloCanciones[j] = arregloCanciones[j + 1];
                    arregloCanciones[j + 1] = temp;
                }
            }
        }

        int tope = (cantidadCanciones < 10) ? cantidadCanciones : 10;
        for (int i = 0; i < tope; i++) {
            std::cout << (i + 1) << ". [" << arregloCanciones[i]->getReproducciones() << "] "
                      << arregloCanciones[i]->getNombre() << " - " << arregloCanciones[i]->getArtista() << "\n";
        }

        std::string comando;
        bool enMenuRanking = true;

        while (enMenuRanking) {
            std::cout << "\nOpciones:\n";
            std::cout << "R<num> - Reproducir cancion seleccionada\n";
            std::cout << "A<num> - Agregar cancion seleccionada al final de la lista de reproduccion actual\n";
            std::cout << "A - Top 10 artistas mas escuchados\n";
            std::cout << "V - Volver al menu principal\n";
            std::cout << "Ingrese Opcion: ";

            std::cin >> comando;

            if (comando == "V" || comando == "v") {
                enMenuRanking = false;
            }
            else if (comando == "A" || comando == "a") {
                refrescarPantalla();
                std::cout << "Ranking TOP 10 Artistas mas escuchados:\n\n";
                std::cout << "(Muestra de artistas en desarrollo)\n\n";
                std::cout << "Presione ENTER para continuar...";
                std::cin.clear(); std::cin.ignore(10000, '\n'); std::cin.get();
                enMenuRanking = false;
            }
            else if (comando.length() > 1 && (comando[0] == 'R' || comando[0] == 'r' || comando[0] == 'A' || comando[0] == 'a')) {
                char accion = comando[0];
                std::string strNum = comando.substr(1);

                try {
                    int num = std::stoi(strNum);
                    if (num > 0 && num <= tope) {
                        Song* cancionObjetivo = arregloCanciones[num - 1];

                        if (accion == 'R' || accion == 'r') {
                            reproductor.reproducirPistaInmediata(cancionObjetivo);
                            enMenuRanking = false;
                        }
                        else if (accion == 'A' || accion == 'a') {
                            reproductor.encolarPistaAlFinal(cancionObjetivo);
                            std::cout << "Cancion agregada a la cola.\n";
                        }
                    } else {
                        std::cout << "Numero fuera de rango.\n";
                    }
                } catch (const std::exception& e) {
                    std::cout << "Comando invalido.\n";
                }
            } else {
                std::cout << "Comando invalido.\n";
            }
        }
        delete[] arregloCanciones;
    }
    else if (opcionRanking == 'A' || opcionRanking == 'a') {
        refrescarPantalla();
        std::cout << "Ranking TOP 10 Artistas mas escuchados:\n\n";
        std::cout << "1. Vivid BAD Squad\n";
        std::cout << "2. David Guetta\n";
        std::cout << "3. K/DA\n";
        std::cout << "4. Ado\n";
        std::cout << "5. Sia\n\n";
        std::cout << "Presione ENTER para volver...";
        std::cin.clear(); std::cin.ignore(10000, '\n'); std::cin.get();
    }
}