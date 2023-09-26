# Descripción

Resuelve el rompecabezas [PuzzleADay](https://mathigon.org/polypad/A62G5zIdDPthg) 
usando la técnica de [backtracking](https://es.wikipedia.org/wiki/Vuelta_atr%C3%A1s).

# Dependencias

Utiliza SDL2 para visualizar el tablero.

# Compilación

Se puede compilar usando CMake o EMScripten.

Para EMScripten, en Windows se utiliza la línea de comandos:

```
emcc Solver\Solver.cpp PuzzleADaySolver\main.cpp -std=c++17 -O2 -o index.html -sSINGLE_FILE -sEXPORTED_FUNCTIONS=_solveAndShow,_main -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --shell-file=EMS\base.html -sUSE_SDL=2
```

Puede verse una demo online [aquí](https://jcallejap.github.io/PuzzleADaySolver/index.html).
