#include "Laberinto.h"
#include "Console.h"
#include <random>
Laberinto::Laberinto() {
    // Constructor vacío
}

Laberinto::~Laberinto() {
    // Destructor vacío
}
void Laberinto::inicializarEspacios() {
    Console::showInfoMessage("Inicializando espacios del laberinto... Ingrese la cantidad de filas:");
    tamañoHorizontal = std::stoi(Console::inputManager());
    
    Console::showInfoMessage("Ingrese la cantidad de columnas:");
    tamañoVertical = std::stoi(Console::inputManager());
    if (tamañoHorizontal > 10 && tamañoVertical > 10) {
        Console::showInfoMessage("Espacios inicializados.");
    } else {
        Console::showInfoMessage("Tamaño inválido. Los valores deben ser mayores que diez.");
    }

    Console::waitForKeyPress();

    Console::clearConsole();
    // Inicializar la malla del laberinto con el tamaño especificado
    malla.resize(tamañoHorizontal, std::vector<int>(tamañoVertical, -1));  // -1 representa un bloque indefinido
}// crea la malla 

void Laberinto::rellenarEspacio() {
/*
    Este algoritmo es un tanto complejo y requiere una comprensión profunda de la estructura del laberinto.
    Se basa en la generación de números aleatorios para determinar la posición de los bloques y su estado.
    Además, se deben tener en cuenta las restricciones del laberinto, como la existencia de caminos y paredes.

    Primero se establece un bloque de salida y uno de entrada, y luego se crea un camino aleatorio desde la entrada hasta la salida del laberinto.
    Este camino se genera utilizando un algoritmo de búsqueda aleatoria que garantiza que haya un camino válido.
    A continuación, se rellenan los espacios restantes del laberinto de manera aleatoria, asegurando que se mantenga la conectividad del camino.
    Generando caminos aleatorios para los bloques restantes.
    
*/
inicializarEspacios();

std::vector<LaberintoEstructura::Bloque> bloquesLlenar = getBloquesIndefinidos();// VECTOR DE BLOQUES A LLENAR
/*for (size_t i = 0; i < bloquesLlenar.size(); i++)
{
    Console::showInfoMessage("Bloque a llenar: (" + std::to_string(bloquesLlenar[i].fila) + ", " + std::to_string(bloquesLlenar[i].columna) + ")"+ "\n");
}*/

    std::random_device rd;
    std::mt19937 gen(rd());
    size_t indice;
    size_t indice2;

    if (tamañoHorizontal > dificultad && tamañoVertical > dificultad) {
        // Establecer bloques importantes los suficientemente difíciles
        dificultad = std::min(tamañoHorizontal, tamañoVertical) / 2;
    } // GESTOR DE DIFICULTAD MODIFICAR SI QUIERE 


    //Estableceer bloques importantes los suficientemente dificiles
    do {

        std::uniform_int_distribution<size_t> dist(0, bloquesLlenar.size() - 1);
        indice = dist(gen);
        //Establecer spawn

        bloqueSpawn = bloquesLlenar[indice];
         // 1 representa un bloque lleno
    // bloquesLlenar.erase(bloquesLlenar.begin() + indice); // EL BLOQUE NO ESTA PARA LLENAR ENTONCES SE QUITA

        // Establecer bloque de salida

        std::uniform_int_distribution<size_t> dist2(0, bloquesLlenar.size() - 1);
        indice2 = dist2(gen);
        bloqueSalida = bloquesLlenar[indice2];
        
    } while (((bloqueSalida.columna - bloqueSpawn.columna)>dificultad && (bloqueSalida.fila - bloqueSpawn.fila) > dificultad) || (bloqueSalida.columna - bloqueSpawn.columna < -dificultad && bloqueSalida.fila - bloqueSpawn.fila < -dificultad));
    
    setEstadoBloque(bloquesLlenar[indice], 1); 
    setEstadoBloque(bloqueSalida, 1); // CAMBIA EL ESTADO DEL BLOQUE DE ENTRADA Y DE SALIDA

    //bloquesLlenar.erase(bloquesLlenar.begin() + indice2);// EL BLOQUE NO ESTA PARA LLENAR ENTONCES SE QUITA

    //mostrar el bloque de entrada y salida elegido
    Console::showInfoMessage("Bloque de entrada elegido: (" + std::to_string(bloqueSpawn.fila) + ", " + std::to_string(bloqueSpawn.columna) + ")");
    Console::showInfoMessage("Bloque de salida elegido: (" + std::to_string(bloqueSalida.fila) + ", " + std::to_string(bloqueSalida.columna) + ")");
    // CREAR CAMINO ALEATORIO ENTRE ENTRADA Y SALIDA

    /*
        Apartir de aqui van a ir las reglas de generación del camino aleatorio.
        Regla de solución:
            Eligira 50/50 si acercarse horizontalmente. o verticalmente.
                Si el bloque de salida es menor que el bloque de entrada horizontalmente entonces intentara mover hacia la izquierda, de lo contrario, intentara mover hacia la derecha.
                Si el bloque de salida es menor que el bloque de entrada verticalmente entonces intentara mover hacia arriba, de lo contrario, intentara mover hacia abajo.
            hay una pequeña posibilidad de que no se acerque en ninguna dirección eso dependera de la dificultad. 
            si no se acerca hay una posibilidad de que se mueva aleatoriamente.
        Reglas de paredes:
            ...
        Reglas de caminos:
            ...
    
    
    */
    Bloque* bloqueActual = &bloqueSpawn;  // puntero al bloque actual que nos ayudara a movernos
    int i = 0;
   while (true) {
    
       // elegir en que posicion moverse
        std::random_device rd;
       std::mt19937 gen(rd());

       std::uniform_int_distribution<size_t> dist(0, 1);
       size_t direccion = dist(gen);
       std::uniform_int_distribution<size_t> mov(0, dificultad);
        size_t movimiento = mov(gen);
        if ((bloqueActual->columna == bloqueSalida.columna && bloqueActual->fila == bloqueSalida.fila)) {
            Console::showInfoMessage("Bloque alcanzado: (" + std::to_string(bloqueActual->fila) + ", " + std::to_string(bloqueActual->columna) + ")");
            break;
        }// Si llega a su destino se va del bucle

       if (direccion == 0 ) {
           // mover Horizontalmente 
           if(movimiento <= 2) {// si logra moverse bien
            if(bloqueSalida.columna>bloqueActual->columna){
                // mover hacia la derecha
                auto it = std::find(bloquesLlenar.begin(), bloquesLlenar.end(), *bloqueActual);
                bloqueActual= &bloquesLlenar[it-bloquesLlenar.begin()+1];

            } else if(bloqueSalida.columna<bloqueActual->columna) {
                // mover hacia la izquierda
                auto it = std::find(bloquesLlenar.begin(), bloquesLlenar.end(), *bloqueActual);
                bloqueActual= &bloquesLlenar[it-bloquesLlenar.begin()-1];
            }

               
           } else {
               // mover aleatoriamente
               std::uniform_int_distribution<size_t> dist(-1, 1);
               size_t dir = dist(gen);
               auto it = std::find(bloquesLlenar.begin(), bloquesLlenar.end(), *bloqueActual);
               bloqueActual= &bloquesLlenar[it-bloquesLlenar.begin()+dir];

           }
           //el bloque it-bloquesLlenar.begin() resta dos iteradores ( son como punteros pero mas estables ) para devolver el indice ( que es la diferencia entre estos)
       } else {
        if(movimiento <= 2) {// si logra moverse bien
            if(bloqueSalida.fila>bloqueActual->fila){
                // mover hacia abajo
                auto it = std::find(bloquesLlenar.begin(), bloquesLlenar.end(), *bloqueActual);
                bloqueActual= &bloquesLlenar[it-bloquesLlenar.begin()+tamañoHorizontal];

            } else if(bloqueSalida.fila<bloqueActual->fila) {
                // mover hacia arriba
                auto it = std::find(bloquesLlenar.begin(), bloquesLlenar.end(), *bloqueActual);
                bloqueActual= &bloquesLlenar[it-bloquesLlenar.begin()-tamañoHorizontal];
            }

               
           } else {
               // mover aleatoriamente
               std::uniform_int_distribution<size_t> dist(-1, 1);
               size_t dir = dist(gen);
               auto it = std::find(bloquesLlenar.begin(), bloquesLlenar.end(), *bloqueActual);
               bloqueActual= &bloquesLlenar[it-bloquesLlenar.begin()+(dir*tamañoHorizontal)];

           }
           
       }
   }

}
