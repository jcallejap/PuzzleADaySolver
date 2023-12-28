# Descripción

Resuelve el rompecabezas [PuzzleADay](https://mathigon.org/polypad/A62G5zIdDPthg) 
usando la técnica de [backtracking](https://es.wikipedia.org/wiki/Vuelta_atr%C3%A1s).


# Dependencias

Utiliza SDL2 para visualizar el tablero.
También se puede compilar usando EMScripten para generar código compatible con un navegador.


# Compilación

## CMake

Se puede compilar usando CMake o seleccionando el directorio principal con Visual Studio 2022.

## EMScripten

Para EMScripten, en Windows se utiliza la línea de comandos:

```
emsdk activate latest
emcc Solver\Solver.cpp PuzzleADaySolver\main.cpp -std=c++17 -O2 -o example.html -sSINGLE_FILE -sEXPORTED_FUNCTIONS=_solveAndShow -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --shell-file=EMS\base.html -sUSE_SDL=2
```

La instalación de EMScripten se ha realizado con:

```
git clone https://github.com/emscripten-core/emsdk
cd emsdk
emsdk install latest
```

Puede verse una demo online [aquí](https://jcallejap.github.io/PuzzleADaySolver/example.html).


# Explicación del código

El proyecto consta principalmente de las siguientes clases y funciones:

## class Piece

Representa una pieza que puede girarse y hacer su espejo.

Al constructor se le pasa un índice de pieza y un array 4x4 donde se indican los elementos activos.

El método ```getTable``` devuelve un objeto de tipo tablero en el que están ocupadas las casillas donde se estaría la pieza después de transformarla con:

- Traslación XY.
- Rotación.
- Espejo.

## class PieceList

Gestiona el conjunto de piezas que tenemos para colocar en el tablero.

Contine dos listas:

- Piezas ya colocadas.
- Piezas por colocar.

Permite mover las piezas de una a otra lista según avanzamos en la solución.

## class Board

Representa un tablero 7x7 en el que las casillas pueden estar libres o usadas.

## class BoardsStack

Representa una pila de tableros que se colocan uno encima del otro.
Una casilla está ocupada si lo está en cualquiera de los tableros apilados.

Este objeto es el que permite añadir y quitar piezas sobre el tablero.
Las piezas se pueden convertir en un objeto de tipo ```Board``` y añadir a esta pila marcando así sus casillas como ocupadas.
Aquí también podemos comprobar si una pieza es compatible y cuál es la siguiente casilla libre.

## solve

Esta es la función de entrada para resolver el problema. 
Básicamente, crea un objeto de tipo ```PieceList``` y llama a la función ```solveWithPieces```.

## solveWithPieces

Esta función realiza la resolución del problema.

Primero decide qué casilla hay que ocupar y después lanza cuatro bucles que recorren:

- Las piezas libres.
- La posición horizontal de una pieza.
- La posición vertical de una pieza.
- La rotación de una pieza.
- El estado del espejo de una pieza.

En cada paso de estos bucles, comprueba si la pieza resultante puede ocupar la casilla.
Si es así, marca la pieza como usada y se llama recursivamente para decidir la siguiente pieza.

Si no consigue encontrar una pieza válida, devuelve false para indicar que no se puede encontrar una solución.

## main

La entrada principal del programa se puede compilar de dos maneras distintas:

- Consola: admite como argumentos el día y mes del año que se quiere dejar libre y utiliza SDL2 para dibujar el tablero en una ventana aparte.
- EMScripten: se exporta la función ```solveAndShow``` que resuelve el problema y dibuja en la zona indicada por el navegador usando SDL2.
