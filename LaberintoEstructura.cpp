#include "LaberintoEstructura.h"

LaberintoEstructura::LaberintoEstructura() {
    // Constructor vacío
}

LaberintoEstructura::~LaberintoEstructura() {
    // Destructor vacío
}
bool LaberintoEstructura::comprobarBloque(const Bloque& bloque) const {
    /*
    # Implemetacion comprobarBLoque
    Revisa si un bloque esta dentro de la malla

    
    */
    if (malla.empty() || malla[0].empty()) return false;
    int tamañoFilas = static_cast<int>(malla.size());
    int tamañoColumnas = static_cast<int>(malla[0].size());
    return bloque.fila >= 0 && bloque.fila < tamañoFilas && bloque.columna >= 0 && bloque.columna < tamañoColumnas;
}// funcion util para comprobar la existencia de un bloque 


void LaberintoEstructura::setEstadoBloque(Bloque bloque, int estado) {
    /*
    #Implementacion setEstadoBlqoue

    cambia el estado de un bloque en la malla
    
    
    
    */
    if (comprobarBloque(bloque)) {
        if(estado==0 || estado==1){
            malla[bloque.fila][bloque.columna] = estado;
        }
        else {
            std::cerr << "Error: Estado inválido. Debe ser 0 o 1." << std::endl;
        }
        
    } else {
        std::cerr << "Error: Bloque fuera de los límites." << std::endl;
    }
}
int LaberintoEstructura::getEstadoBloque(Bloque bloque) const {
    /*
        # Implementacion getEstadoBloque
        verifica si el bloque exite en la malla y devuelve el valor

    
    
    */
    if (comprobarBloque(bloque)) {
        return malla[bloque.fila][bloque.columna];
    } else {
        //std::cerr << "Error: Bloque fuera de los límites." << std::endl;
        return -1;  // Valor por defecto en caso de error
    }
}

std::vector<LaberintoEstructura::Bloque> LaberintoEstructura::getBloquesIndefinidos() const {
    /*
    # Implementacion getBloquesIndefinidos

    Itera toda la malla y devuelve los bloques que tenga de valor 0
    
    */
    std::vector<Bloque> bloquesIndefinidos;
    for (int i = 0; i < static_cast<int>(malla.size()); ++i) {
        for (int j = 0; j < static_cast<int>(malla[i].size()); ++j) {
            if (malla[i][j] == 0) {  // 0 representa un bloque pared
                bloquesIndefinidos.push_back({i, j});
            }
        }
    }
    return bloquesIndefinidos;
}// funcion util para encontrar bloques indefinidos

