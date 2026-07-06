#ifndef MENUS_HPP
#define MENUS_HPP

#include "Player.hpp"
#include "../data_structures/Trie.hpp"

void refrescarPantalla();
void renderizarMenuPrincipal(Player& reproductor, Trie& buscador);
void ventanaBusqueda(Player& reproductor, Trie& buscador);
void ventanaRankings(Player& reproductor);

#endif