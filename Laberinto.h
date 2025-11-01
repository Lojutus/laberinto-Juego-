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

class Laberinto:LaberintoEstructura {
public:
    
    Laberinto();   // Constructor
    ~Laberinto();  // Destructor
    void rellenarEspacio();
    void imprimirMalla();
     
    

private:
    LaberintoEstructura::Bloque bloqueSpawn;
    LaberintoEstructura::Bloque bloqueSalida;
    std::mt19937 gen{std::random_device{}()}; // Generador de números aleatorios

    void inicializarEspacios();
    
    void mostrarLaberinto();
    void gestionarEntradaUsuario();
    void actualizarLaberinto();
    void iniciarLaberinto();
    bool verificarNuevoCamino(LaberintoEstructura::Bloque *bloqueAnalizar , int tolerancia);
    int elegirDireccionAleatoria(Bloque  bloqueActual);
    Bloque crearCamino(size_t longitud, Bloque bloquePos);
       // Atributos
}; 
#endif // Laberinto_H
