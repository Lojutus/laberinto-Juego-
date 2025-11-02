#ifndef Laberinto_H
#define Laberinto_H

#include "LaberintoEstructura.h"
#include "Console.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>

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

class Laberinto: public LaberintoEstructura {
public:
    
    Laberinto();   // Constructor
    ~Laberinto();  // Destructor
    bool rellenarEspacio();
    void imprimirMalla(int modo, Bloque Jugador);
    void inicializarEspacios(int tamañoH , int tamañoV);
    Bloque getBloqueSpawn();
    Bloque getBloqueSalida();
    

protected:
    LaberintoEstructura::Bloque bloqueSpawn;
    LaberintoEstructura::Bloque bloqueSalida;
    
    std::mt19937 gen{std::random_device{}()}; // Generador de números aleatorios

    
    void mostrarLaberinto();
    void gestionarEntradaUsuario();
    void actualizarLaberinto();
    
    bool verificarNuevoCamino(LaberintoEstructura::Bloque *bloqueAnalizar , int tolerancia);
    int elegirDireccionAleatoria(Bloque  bloqueActual);

    Bloque crearCamino(size_t longitud, Bloque bloquePos);
       // Atributos
}; 
#endif // Laberinto_H
