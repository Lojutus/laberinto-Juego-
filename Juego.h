#ifndef Personaje_H
#define Personaje_H

#include <iostream>
#include <string>
#include <vector>
#include "Laberinto.h"
#include "LaberintoEstructura.h"

/*
===============================================================================
                                CRC - Juego
===============================================================================

Clase:
    Personaje

Responsabilidades:
    Representar a un personaje en el laberinto.
    
Colaboradores:
   
===============================================================================
*/

class Juego {
public:
    Juego(int posicionHorizontal , int posicionVertical, Laberinto& Laberinto);   // Constructor
    void movimientoPersonaje(char direccion);
    LaberintoEstructura::Bloque& getBloqueActual();
    ~Juego();  // Destructor
    
        

private:
    
    
    Laberinto laberinto;
    LaberintoEstructura::Bloque bloqueActual;
    
    
    // Atributos

    
};

#endif // CLASEA_H
