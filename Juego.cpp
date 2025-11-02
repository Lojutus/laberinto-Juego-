#include "Juego.h"
#include "Laberinto.h"
#include "Console.h"
Juego::Juego(int posicionHorizontal, int posicionVertical, Laberinto& lab): 
    laberinto(lab),
    bloqueActual{posicionHorizontal, posicionVertical}
{
}

Juego::~Juego() {
    // Destructor vacío
}
void Juego::movimientoPersonaje(char direccion){
    Laberinto::Bloque bloque; 
    bloque = bloqueActual;
    
    if (direccion =='w'){
        bloque.fila = bloque.fila- 1;
    }
    else if(direccion=='s'){
        bloque.fila =bloque.fila+1 ;
    }
    else if(direccion== 'd'){
        bloque.columna=bloque.columna+1;
    }
    else if(direccion== 'a'){
        bloque.columna=bloque.columna-1;
    }
    else{
        Console::showInfoMessage("Comando invalido");
    }
    if(!laberinto.comprobarBloque(bloque) || laberinto.getEstadoBloque(bloque)==0){
       
        Console::showInfoMessage("Direccion invalida");
    }
    else{
        bloqueActual = bloque;
    }

}

Laberinto::Bloque& Juego::getBloqueActual(){
    return bloqueActual;
}