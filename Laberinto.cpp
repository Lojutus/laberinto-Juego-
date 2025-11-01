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
    /*
        # Implementacion metodo inicializarEspacios
        
        Pide los valores con el que se inicalizara la malla , y cambia su tamaño de aceurdo a esos datos
    
    */
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
        Implementacion metodo verificarNuevoCamino

        Verifica si un bloque puede ser camino con las siguientes reglas:
                    - es una pared
                    - tiene  una cantidad de  caminos vecino menor o igual al de tolerancia
        Funcionamiento:

        1. revisa si el bloque suministrado es una pared y no un camino 

        2. si es un camino guarda sus vecinos ( arriba, abajo , izquierda , derecha ) todas esos nuevos bloques se guardan en un vector (si la direccion es valida)
        3. cuenta cuantos de sus vecinos son caminos 

        4. si cumple que tiene menos cantidad o igua cantidad de caminos a la tolerancia suministrada devuelve true

        Notas:

            Si no cumple con la tolerancia devuelve que no es valido
            Si ya es un camino devuelve que no es valido 
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

            if (caminosUnidos <= tolerancia && caminosUnidos!=0) //verfica que no tenga mas caminos
            {
                return true;
            } else {
                //Console::showInfoMessage("Bloque rechazado para camino: (" + std::to_string(bloqueActual->fila) + ", " + std::to_string(bloqueActual->columna) + ") tiene " + std::to_string(caminosUnidos) + " caminos unidos.\n");
                return false;
            }
            }
    return false; 
            
    }

LaberintoEstructura::Bloque Laberinto::crearCamino(size_t longitud, Bloque bloquePos) {
    /*
        # Implementación del método crearCamino

        Este se encarga de crear un nuevo camino que funciona como una rama ( necesita esta conectado a un camino)

        *Funcionamiento:*
        1. entra a un bucle que se ejecutara la cantidad de veces establecida en la longitud ( esto no garantiza que el camino tendra esa cantidad de bloques mas adelante se explica el porque )
        
        2. Verifica que el bloque de donde se inicia sea un cammino ( si no lo es devuelve el mismo bloque)

        3. elije una direccion a donde moverse de acuerdo al metodo elegirDireccionAleatoria

        4. se mueve hacia la direccion que eligio , y establece ese bloque como camino  ( las verificaciones respecto a si es valido o no lo hace el metodo elegirDireccionAleatoria)
        
        ...Repite ese ciclo...

        5. cuando se termina la longitud el algoritmo devuelve el blque donde termino el camino}

        Notas:
            El metodo elegirDireccionAleatoria puede devolver 0  lo cual significa que no se puede mover a ningun lado , si eso apsa el bucle del camino se detiene , para ahorrar tiempo
            Al ser aleatorio  el bloque de salida puede estar muy cerca del bloque de spawn sin embargoe so no significa que la cantidad de pasos sea poca 
    */ 
    
    for (size_t i = 0; i < longitud; i++) {
        if(getEstadoBloque(bloquePos) == 0) {// obtiene el estado del bloque actual
            //Console::showInfoMessage("Suministrado no es camino");
            return bloquePos; // si el bloque es pared , retorna la posicion actual sin crear camino
        }
        int direccion = elegirDireccionAleatoria(bloquePos); // 1 derecha , 2 izquierda , -1 abajo , -2 arriba , 0 no se puede mover
        if(direccion==0){
            break;
        }
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
    /*
        #Implementacion Metodo elegiDireccionAleatoria

        Comprueba las 4 direcciones var aver si alguna es valida , si lo es devuelve 1 derecha , 2 izquierda , -1 abajo , -2 arriba y devuelve 0 no se puede mover

        *Funcionamiento:*
        1. Elije un numero random para decidir en que direccion va a comenzar a revisar
        2. Entra en un bucle y revisa si la pocion es valida con la funcion verificarNuevoCamino
        
        Notas:
         el bloqueBackup sirve para devolverse si la verificion fallo 

    
    */

            
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
void Laberinto::rellenarEspacio() {
    // Implementación del método rellenarEspacio
    /*
    Este algoritmo es un tanto complejo y requiere una comprensión profunda de la estructura del laberinto.
    Se basa en la generación de números aleatorios para determinar la posición de los bloques y su estado.
    Además, se deben tener en cuenta las restricciones del laberinto, como la existencia de caminos y paredes.

    funcionamineto
        Este metodo colabora con varios otros metodos los cuales su funcionamiento estara explicado en su respectivo espacio ( asi como este)
        1: Para tener un laberinto al cual llenar  se instancias los espacios 
        2: Se obtiene todos los bloques los cuales estan sin llenar , que en ese momento de ejecucion son todos 
        3: utilizando la libreria random se elije un punto de spawn y se establece ese punto como nuestro primer camino ( crucial para mas adelante)
        4: se establece lo largo de los caminos de acuerdo a la realcion de bloques que hay para llenar, entre mas bloques mas largos los caminos , si se deja un camino muy bajo hay altas posibilidades que no se rellene todo el laberinto
        5: de aceurdo al primer camino aleatorio generado y el bloque final del camino , se genera el bloque de salida, es decir es totalmente aleatorio
        6: se muestra la informacion en consola
        7: Por ultimo se revisa cada uno de los bloques que hay para rellenar , y se llama a la funcion crearcaminoo para que esta verifique si es valido para un camino o no ( si lo es crea un nuevo camino desde ahi )
        Notas:
            El fracmento con el bucle que crea ramificaciones , tiene una carga computacional demasiado alta, cuando el laberinto es pequeño se podria dejar con un solo bucle
            Pero para garantizar que todo el laberinto este lleno independientemente el tamaño, coloque el bucle dos veces . a mi parecer esta en el punto de equilibiro entre calidad y tiempo ( aunque se puede optimizar el algoritmo que escoje las ramificaciones)
        */
    inicializarEspacios();

    
    std::vector<LaberintoEstructura::Bloque> bloquesLlenar = getBloquesIndefinidos();// VECTOR DE BLOQUES A LLENAR
    std::random_device rd;
    
    std::uniform_int_distribution<size_t> dist(0, bloquesLlenar.size() - 1);
    size_t indice = dist(gen);
    bloqueSpawn = bloquesLlenar[indice];
    setEstadoBloque(bloquesLlenar[indice], 1);

    size_t longitudSolucion = tamañoHorizontal * tamañoVertical;
    
    bloqueSalida = crearCamino(longitudSolucion, bloqueSpawn);
    setEstadoBloque(bloqueSalida, 1);
    Console::showInfoMessage("Bloque de entrada creado en: (" + std::to_string(bloqueSpawn.fila) + ", " + std::to_string(bloqueSpawn.columna) + ")\n");
    Console::showInfoMessage("Bloque de salida creado en: (" + std::to_string(bloqueSalida.fila) + ", " + std::to_string(bloqueSalida.columna) + ")\n");
    

    Console::showInfoMessage("Total de bloques a llenar: " + std::to_string(getBloquesIndefinidos().size()) + "\n");
    Console::showInfoMessage("CARGANDO");
    
    for(size_t j = 0 ; j <bloquesLlenar.size(); j++){
        crearCamino(longitudSolucion, bloquesLlenar[j]);
        //
    } 
    bloquesLlenar = getBloquesIndefinidos();

    for(size_t j = 0 ; j <bloquesLlenar.size(); j++){
        crearCamino(longitudSolucion, bloquesLlenar[j]);
        //
    }  
    bloquesLlenar = getBloquesIndefinidos();

    for(size_t j = 0 ; j <bloquesLlenar.size(); j++){
        crearCamino(longitudSolucion, bloquesLlenar[j]);
        //
    }    
    //int backUpDireccion = -5; // variable para evitar retroceder en el mismo movimiento
    Console::clearConsole();
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
