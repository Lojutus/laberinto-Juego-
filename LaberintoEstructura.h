#ifndef LaberintoEstructura_H
#define LaberintoEstructura_H

#include <iostream>
#include <string>
#include <vector>

/*
===============================================================================
                                CRC - LaberintoEstructura
===============================================================================

Clase:
    LaberintoEstructura

Responsabilidades:
    Proveer la estructura base para el laberinto.
    Facilitar la creación y manipulación de la malla del laberinto.
    Gestionar la representación del laberinto.

    
Colaboradores:
   
===============================================================================
*/

class LaberintoEstructura {
    protected:
        struct Bloque {
            int fila;
            int columna;
            bool operator==(const Bloque& other) const {
                return fila == other.fila && columna == other.columna;
            }//Defino el operado == para mi struct Bloque 
        };
        
        int tamañoHorizontal;
        int tamañoVertical;
        std::vector<std::vector<int>> malla; // Malla del laberinto
        bool comprobarBloque(const Bloque& bloque) const;
        void añadirFila(const std::vector<int>& fila);
        void setEstadoBloque(Bloque bloque , int estado);
        int getEstadoBloque(Bloque bloque) const;
        std::vector<Bloque> getBloquesIndefinidos() const;


    public:
        LaberintoEstructura();   // Constructor
        ~LaberintoEstructura();  // Destructor
        
    private:

        // Atributos

};

#endif // LaberintoEstructura_H
