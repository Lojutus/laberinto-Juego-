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
    malla.resize(tamañoHorizontal, std::vector<int>(tamañoVertical, 0));  // 0 representa una pared
}// crea la malla 




bool Laberinto::verificarNuevoCamino( LaberintoEstructura::Bloque *bloqueAnalizar, int tolerancia) {
    /*
        Verifica si un bloque puede ser camino con las siguientes reglas:
            - es una pared
            - tiene solo un camino vecino
            
    */
   Bloque* bloqueActual = bloqueAnalizar;  // puntero al bloque actual que nos ayudara a movernos
    if (getEstadoBloque(*bloqueActual) == 0) { // si el bloque esta como pared
        
                std::vector<Bloque> vecinos; // punteros que apuntan a los bloques vecinos
                // verificar que no se salga de los limites
                Bloque vecino = *bloqueActual;
                vecino.fila = bloqueActual->fila + 1;
                vecino.columna = bloqueActual->columna;
                if(comprobarBloque(vecino)) vecinos.push_back(vecino);; // abajo
                
                vecino.fila = bloqueActual->fila - 1;
                if(comprobarBloque(vecino)) vecinos.push_back(vecino); // arriba
                vecino.fila = bloqueActual->fila;
                vecino.columna = bloqueActual->columna + 1;
                if(comprobarBloque(vecino)) vecinos.push_back(vecino); // derecha
                vecino.columna = bloqueActual->columna - 1;
                if(comprobarBloque(vecino)) vecinos.push_back(vecino); // izquierda
                int caminosUnidos = 0;
                
                for (const auto& vecino : vecinos) {// itera los vecinos para decidir si convertir en camino
                    //Console::showInfoMessage("Verificando bloque vecino en: (" + std::to_string(vecino.fila) + ", " + std::to_string(vecino.columna) + ")\n");
                    if (comprobarBloque(vecino) && getEstadoBloque(vecino) == 1) {// verifica que tiene un vecino camino
                        // tiene un vecino que es camino
                        //Console::showInfoMessage("Bloque vecino camino encontrado en: (" + std::to_string(vecino.fila) + ", " + std::to_string(vecino.columna) + ")\n");
                        caminosUnidos++;
                    }
                }

            if (caminosUnidos == tolerancia) //verfica que no tenga mas caminos
            {
                return true;
            } else {
                //Console::showInfoMessage("Bloque rechazado para camino: (" + std::to_string(bloqueActual->fila) + ", " + std::to_string(bloqueActual->columna) + ") tiene " + std::to_string(caminosUnidos) + " caminos unidos.\n");
                return false;
            }
            }
    return false; 
            
    }

void Laberinto::rellenarEspacio() {
    // Implementación del método rellenarEspacio
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


    Console::showInfoMessage("Total de bloques a llenar: " + std::to_string(getBloquesIndefinidos().size()) + "\n");

    std::vector<LaberintoEstructura::Bloque> bloquesLlenar = getBloquesIndefinidos();// VECTOR DE BLOQUES A LLENAR
    std::random_device rd;
    
    std::uniform_int_distribution<size_t> dist(0, bloquesLlenar.size() - 1);
    size_t indice = dist(gen);
    bloqueSpawn = bloquesLlenar[indice];
    setEstadoBloque(bloquesLlenar[indice], 1);

    Bloque* bloqueActual = &bloqueSpawn; 

    std::vector<LaberintoEstructura::Bloque> posiblesCaminos = {}; //vector de punteros a bloques posibles para convertir en camino
    posiblesCaminos.push_back(*bloqueActual);
    //posiblesCaminos.push_back((bloqueActual->fila-1) * (tamañoHorizontal-1) + abs((bloqueActual->columna-1))); // puntero al bloque actual que nos ayudara a movernos
    while(dificultad> tamañoHorizontal * tamañoVertical /10){
        dificultad = dificultad -1;
    }

    size_t longitudSolucion = tamañoHorizontal * tamañoVertical;
    
    bloqueSalida = crearCamino(longitudSolucion, *bloqueActual);
    setEstadoBloque(bloqueSalida, 1);
    Console::showInfoMessage("Bloque de entrada creado en: (" + std::to_string(bloqueSpawn.fila) + ", " + std::to_string(bloqueSpawn.columna) + ")\n");
    Console::showInfoMessage("Bloque de salida creado en: (" + std::to_string(bloqueSalida.fila) + ", " + std::to_string(bloqueSalida.columna) + ")\n");
    size_t i = 0;
    while(!posiblesCaminos.empty()){
        std::uniform_int_distribution<size_t> dist(0, longitudSolucion);
        size_t longitudSolucionRand = dist(gen);
        Bloque posicionFinalCamino = crearCamino(longitudSolucionRand, posiblesCaminos.back()); // el bloque final del camino no lo convierte en camino
        setEstadoBloque(posicionFinalCamino, 1); // convierte en camino el donde termina el camino
        if(posicionFinalCamino ==  posiblesCaminos.back()){
            posiblesCaminos.pop_back();
        } else {
            //Console::showInfoMessage("nuevo camino"+ std::to_string(i));
            posiblesCaminos.push_back(posicionFinalCamino); // no crea mas caminos porque el otro camino no se puede mover , hay que encontrar la solucion a ese problema

        }
    }
   
    
    
    
    //int backUpDireccion = -5; // variable para evitar retroceder en el mismo movimiento
    
}

LaberintoEstructura::Bloque Laberinto::crearCamino(size_t longitud, Bloque bloquePos) {
    // Implementación del método crearCamino
    
    for (size_t i = 0; i < longitud; i++) {
        if(getEstadoBloque(bloquePos) == 0) {// obtiene el estado del bloque actual
            Console::showInfoMessage("Suministrado no es camino");
            return bloquePos; // si el bloque es pared , retorna la posicion actual sin crear camino
        }
        int direccion = elegirDireccionAleatoria(bloquePos); // 1 derecha , 2 izquierda , -1 abajo , -2 arriba , 0 no se puede mover
        switch (direccion)
        {
        case 1:
            // mover hacia la derecha
            
            bloquePos.fila = bloquePos.fila + 1;
            setEstadoBloque(bloquePos, 1);
            break;
        case 2:
            // mover hacia la izquierda
            
            bloquePos.fila = bloquePos.fila - 1;
            setEstadoBloque(bloquePos, 1);
            break;
        case -1:
            // mover hacia abajo
            
            bloquePos.columna = bloquePos.columna + 1;
            setEstadoBloque(bloquePos, 1);
            break;
        case -2:
            // mover hacia arriba
            
            bloquePos.columna = bloquePos.columna - 1;
            setEstadoBloque(bloquePos, 1);
            break;
        
        default:
            break;
        }
         
    }
    return bloquePos; // retorna la nueva posicion del bloque despues de crear el camino

}
int Laberinto::elegirDireccionAleatoria(Bloque bloqueActual) {

            
            std::uniform_int_distribution<size_t> dist2(0, 3);
            size_t direccion2 = dist2(gen);
            
            
            for(size_t j=0; j<4; j++){
                Bloque bloqueBackup = bloqueActual; // guardo la posicion actual del bloque
                // mover en horizontal
                if(direccion2==0){
                    // mover hacia la derecha
                    bloqueActual.fila = bloqueActual.fila+1; // obtiene la posicion actual
                    if(verificarNuevoCamino(&bloqueActual, 1))return 1;
                    bloqueActual = bloqueBackup; // restaurar la posicion original

                } else if(direccion2==1){
                    // mover hacia la izquierda
                    bloqueActual.fila = bloqueActual.fila-1;
                    if(verificarNuevoCamino(&bloqueActual, 1))return 2;
                    bloqueActual = bloqueBackup; // restaurar la posicion original
                }

             else if(direccion2==2){ 
                // mover hacia abajo
                bloqueActual.columna = bloqueActual.columna+1;
                if(verificarNuevoCamino(&bloqueActual, 1))return -1;
                bloqueActual = bloqueBackup; // restaurar la posicion original

            } else if(direccion2==3){
            // mover hacia arriba
                bloqueActual.columna = bloqueActual.columna-1;
                    if(verificarNuevoCamino(&bloqueActual, 1))return -2;
                    bloqueActual = bloqueBackup; // restaurar la posicion original
                }
                if(direccion2==3){
                    direccion2=0;
                } else {
                    direccion2++;
                }

    // Implementación del método elegirDireccionAleatoria
}
return 0;// no se puede mover
            } 

void Laberinto::imprimirMalla() {
    for (const auto& fila : malla) {
        for (int celda : fila) {
            if (celda == 0) std::cout << "█";     // pared
            else if (celda == 1) std::cout << " "; // camino
            else if (celda == 2) std::cout << "S"; // Start
            else if (celda == 3) std::cout << "E"; // End
            else std::cout << "?";                  // valor desconocido
        }
        std::cout << "\n";
    }
    for (size_t f = 0; f < malla.size(); ++f) {
    for (size_t c = 0; c < malla[f].size(); ++c) {

        LaberintoEstructura::Bloque actual{(int)f, (int)c};

        // Si es el spawn → 8
        if (actual == bloqueSpawn) {
            std::cout << "8 ";
        }
        // Si es la salida → 9
        else if (actual == bloqueSalida) {
            std::cout << "9 ";
        }
        // Si no, imprime la celda original
        else {
            std::cout << malla[f][c] << " ";
        }
    }
    std::cout << "\n";
}

}
