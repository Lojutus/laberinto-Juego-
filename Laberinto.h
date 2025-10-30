#ifndef Laberinto_H
#define Laberinto_H

#include "LaberintoEstructura.h"
#include "Console.h"
#include <iostream>
#include <string>
#include <vector>

/*
===============================================================================
                                CRC - Laberinto
===============================================================================

Clase:
    Laberinto

Responsabilidades: 
    rellena los espacios del laberinto
    
Colaboradores:
    LaberintoEstructura
    Console
   
===============================================================================
*/

class Laberinto:LaberintoEstructura {
public:
    int dificultad;
    
    Laberinto();   // Constructor
    ~Laberinto();  // Destructor
    void rellenarEspacio();
     
    

private:
    LaberintoEstructura::Bloque bloqueSpawn;
    LaberintoEstructura::Bloque bloqueSalida;

    void inicializarEspacios();
    
    void mostrarLaberinto();
    void gestionarEntradaUsuario();
    void actualizarLaberinto();
    void iniciarLaberinto();
       // Atributos
};

#endif // Laberinto_H
