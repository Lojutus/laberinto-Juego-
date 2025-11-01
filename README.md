## PLANTILLA PARA GOOGLE-TESTING CON DOCKER PARA PROYECTOS EN C++

## 🔹 Descripcion basica del proyecto

Este proyecto es un juego sencillo de consola, donde un personaje tiene que salir de un laberinto, el laberinto puede ser de cualqueir tamaño (min 11*11) siempre y cuando el poder computacional lo permita. El laberinto es generado proceduralmente

## Funcionamiento

# **CLASE LaberintoEstructura**
Esta clase es la encargada de contener toda la logica para modificar el laberinto , el cual es representado con una malla 
# Propiedades
```cpp
struct Bloque {
            int fila;
            int columna;
            bool operator==(const Bloque& other) const {
                return fila == other.fila && columna == other.columna;
            }//Defino el operado == para el struct Bloque 
        };
        
int tamañoHorizontal;
int tamañoVertical;
std::vector<std::vector<int>> malla; // Malla del laberinto
```
La estrucutra Bloque se usa en todo el proyecto dado que asi podemos contener una fila y una columna de una forma muchisimo mas comoda 

La mala es sobre la cual se desarrolla el juego y las variables de tipo entero sirven para hacer comparaciones mas adelante


# Implemetacion comprobarBLoque
Revisa si un bloque esta dentro de la malla

# Implementacion setEstadoBlqoue

cambia el estado de un bloque en la malla

# Implementacion getEstadoBloque

verifica si el bloque exite en la malla y devuelve el valor

# Implementacion getBloquesIndefinidos

Itera toda la malla y devuelve los bloques que tenga de valor 0
    
# **CLASE Laberinto**

Hereda todo lo de LaberintoEstrucutra

# Propiedades
```cpp

    LaberintoEstructura::Bloque bloqueSpawn;

    LaberintoEstructura::Bloque bloqueSalida;

    std::mt19937 gen{std::random_device{}()}; 

```
Los bloques son el de spwan del jugador y el de salida del laberinto 

el mt19937 es el motor de generador de numeros aleatorios 

# Implementacion metodo inicializarEspacios
        
crea la malla
    

# Implementacion metodo verificarNuevoCamino

Verifica si un bloque puede ser camino con las siguientes reglas:
            - es una pared
            - tiene  una cantidad de  caminos vecino menor o igual al de tolerancia

*Funcionamiento:*

1. revisa si el bloque suministrado es una pared y no un camino 

2. si es un camino guarda sus vecinos ( arriba, abajo , izquierda , derecha ) todas esos nuevos bloques se guardan en un vector (si la direccion es valida)
3. cuenta cuantos de sus vecinos son caminos 

4. si cumple que tiene menos cantidad o igua cantidad de caminos a la tolerancia suministrada devuelve true

Notas:

    Si no cumple con la tolerancia devuelve que no es valido

    Si ya es un camino devuelve que no es valido 

 # Implementación del método crearCamino

Este se encarga de crear un nuevo camino que funciona como una rama ( necesita esta conectado a un camino)

*Funcionamiento:*

1. entra a un bucle que se ejecutara la cantidad de veces establecida en la longitud ( esto no garantiza que el camino tendra esa cantidad de bloques mas adelante se explica el porque )
        
2. Verifica que el bloque de donde se inicia sea un cammino ( si no lo es devuelve el mismo bloque)

3. elije una direccion a donde moverse de acuerdo al metodo elegirDireccionAleatoria

4. se mueve hacia la direccion que eligio , y establece ese bloque como camino  ( las verificaciones respecto a si es valido o no lo hace el metodo elegirDireccionAleatoria)
        
...Repite ese ciclo...

5. cuando se termina la longitud el algoritmo devuelve el bloque donde termino el camino

Notas:

    El metodo elegirDireccionAleatoria puede devolver 0  lo cual significa que no se puede mover a ningun lado , si eso apsa el bucle del camino se detiene , para ahorrar recursos 

    Al ser aleatorio  el bloque de salida puede estar muy cerca del bloque de spawn sin embargoe so no significa que la cantidad de pasos sea poca 
    
# Implementacion Metodo elegiDireccionAleatoria

Comprueba las 4 direcciones var aver si alguna es valida , si lo es devuelve 1 derecha , 2 izquierda , -1 abajo , -2 arriba y devuelve 0 no se puede mover

*Funcionamiento:*

1. Elije un numero random para decidir en que direccion va a comenzar a revisar
2. Entra en un bucle y revisa si la pocion es valida con la funcion verificarNuevoCamino
        
Notas:

el bloqueBackup sirve para devolverse si la verificion fallo 

# Implementación del método rellenarEspacio

Este algoritmo es un tanto complejo y requiere una comprensión profunda de la estructura del laberinto.
Se basa en la generación de números aleatorios para determinar la posición de los bloques y su estado.
Además, se deben tener en cuenta las restricciones del laberinto, como la existencia de caminos y paredes.

*Funcionamiento:*

Este metodo colabora con varios otros metodos los cuales su funcionamiento estara explicado en su respectivo espacio ( asi como este)

1. Para tener un laberinto al cual llenar  se instancias los espacios 

2. Se obtiene todos los bloques los cuales estan sin llenar , que en ese momento de ejecucion son todos 

3. utilizando la libreria random se elije un punto de spawn y se establece ese punto como nuestro primer camino ( crucial para mas adelante)

4. se establece lo largo de los caminos de acuerdo a la realcion de bloques que hay para llenar, entre mas bloques mas largos los caminos , si se deja un camino muy bajo hay altas posibilidades que no se rellene todo el laberinto

5. de aceurdo al primer camino aleatorio generado y el bloque final del camino , se genera el bloque de salida, es decir es totalmente aleatorio

6. se muestra la informacion en consola

7. Por ultimo se revisa cada uno de los bloques que hay para rellenar , y se llama a la funcion crearcaminoo para que esta verifique si es valido para un camino o no ( si lo es crea un nuevo camino desde ahi )
        
Notas:

El fracmento con el bucle que crea ramificaciones , tiene una carga computacional demasiado alta, cuando el laberinto es pequeño se podria dejar con un solo bucle
Pero para garantizar que todo el laberinto este lleno independientemente el tamaño, coloque el bucle dos veces . a mi parecer esta en el punto de equilibiro entre calidad y tiempo ( aunque se puede optimizar el algoritmo que escoje las ramificaciones)
        
## NOTAS SOBRE LAS CLASES

En este momento no estan implementadas todas las clases para que el jeugo funcioopne correctamente, por ahora estan esas dos 

## 🔹 COMO HACER Debugging en VS Code
El archivo `.vscode/launch.json` ya incluye la configuración de depuración:
- Debug (gdbserver :2345) → Permite depuración remota con `gdbserver`.
1. En una terminal del contenedor, compila y lanza `gdbserver`:
```bash
make gdbserver
```
Esto mostrará algo como:
```bash
Listening on port 2345
Waiting for gdb connection...
```
2. En VS Code pulsa **F5**. Se conectará al puerto *2345* y podrás depurar de forma remota.

## 🔹 Google Testing
Se debe modificar el archivo `tests/test_main.cpp` con los test que requeridos.

Dentro del Dev Container:

```bash
make google-test       # Ejecuta los test con la librería gtest de google
```

El binario generado es `test_runner`.

