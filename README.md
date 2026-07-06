# :musical_note: C-Player | Reproductor de Consola (Taller 02 EDD)

## :pencil: De qué trata esto
Este es nuestro proyecto para el Taller 2 de Estructuras de Datos (UCN). El objetivo principal de esta entrega es la evolución de nuestro reproductor de música desarrollado en el primer taller, expandiendo sus capacidades al implementar estructuras de datos basadas en árboles. Seguimos manteniendo la regla de oro: **cero librerías nativas STL**. Toda la lógica de búsqueda, ordenamiento y jerarquía la armamos desde cero peleando con los punteros y manejando la memoria a mano.

---

## :busts_in_silhouette: El Equipo

| Integrante | Carrera | GitHub |
| :--- | :--- | :--- |
| **Benjamín Rojas** | ICCI | [@BenjaminRojasA](https://github.com/BenjaminRojasA) |
| **Brandon Navea** | ICCI | [@brandonnavea](https://github.com/brandonnavea) |
| **Ignacio Cataldo** | ICCI | [@ignaciocataldo](https://github.com/ignaciocataldo) |

* **Profesor:** Bastian Ruiz Garay
* **Ayudante:** Pablo Guzmán Vargas

---

## :construction: Qué logramos armar (Nuevas Funcionalidades)
Para esta versión, el reproductor no solo mantiene todas las funciones mecánicas de la entrega anterior (reproducción, pausa, colas, avance y retroceso), sino que le metimos harto empeño a las sugerencias de la comunidad para mejorar la experiencia:

* **Búsqueda Inteligente (F):** Implementamos un buscador alfanumérico que permite encontrar canciones por cualquier fragmento de texto en el nombre de la pista o del artista. Para que la búsqueda de texto sea ultra eficiente, nos basamos en árboles **Trie**.
* **Sistema de Rankings TOP 10 (T):** Ahora el reproductor lleva la cuenta de lo que más escuchas. Creamos un sistema que muestra las 10 canciones más reproducidas y los 10 artistas más escuchados en la plataforma. Esto está soportado bajo el capó utilizando árboles **Heap**.
* **Catálogo por Artistas:** Desde el menú de artistas top, puedes desplegar un submenú con todas las canciones registradas a nombre de ese artista en particular. Para mantener todo impecable y ordenado alfabéticamente, usamos árboles **AVL**.
* **Persistencia de Contadores:** Para no impactar la memoria, las estructuras de los árboles se arman al vuelo cuando arranca el programa. Lo único que guardamos de forma persistente en disco son los contadores de reproducción de cada ID de canción. 
* **Interfaz Limpia:** Se implementó limpieza de consola en cada operación para que la navegación entre menús sea fluida y no deje un rastro gigante en la terminal.

---

## :brain: La Arquitectura y Modularidad
Todo el código sigue estructurado con Templates (`<T>`) para evitar redundancias, pero ahora separamos rigurosamente la interfaz de la implementación (.h y .cpp). El proyecto está modularizado en carpetas específicas según su función:
* `data_structures/`: Aquí viven nuestros Nodos, Listas Enlazadas, y los nuevos árboles (Trie, Heap, AVL).
* `classes/`: Las entidades del sistema (como las Canciones).
* `core/`: La lógica dura del negocio y los flujos de los menús.

---

## :gear: Compilación y Ejecución
Para compilar y ejecutar este proyecto de forma limpia por consola (CMD), necesitas tener instalado un compilador de C++ (como MinGW/GCC). Como el proyecto está dividido en varios módulos y carpetas, tienes dos opciones para hacerlo funcionar desde tu terminal ubicándote en la raíz del proyecto:

### Opción 1: Compilación manual (Comando g++)
Abre tu consola (CMD o terminal) y lanza este comando para enlazar todos los archivos `.cpp` de las distintas carpetas y generar el ejecutable:

```bash
g++ main.cpp core/*.cpp classes/*.cpp data_structures/*.cpp -o CPlayer
