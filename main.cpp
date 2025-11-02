

#include "Console.h"
#include "Laberinto.h"
#include "LaberintoEstructura.h"
#include "Juego.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int main() {
  
  Console::clearConsole();
  Console::showInfoMessage("Bienvenido al mejor juego de laberinto nunca antes visto ");
  while(true){
    try
    {
      Laberinto laberinto;
     
      Console::showInfoMessage("Ingrese el ancho de su laberinto. \n");
      int ancho = stoi(Console::inputManager());
      Console::showInfoMessage("Ingrese el largo de su laberinto. \n");
      int largo = stoi(Console::inputManager());
      Console::showInfoMessage("Ingrese el estilo para imprimir su laberinto. \n 1: Con bloques \n 2: con numeros \n Por defecto Con numeros" );
      int modoImprecion = stoi(Console::inputManager());

      laberinto.inicializarEspacios(ancho, largo);
      laberinto.rellenarEspacio();
      LaberintoEstructura::Bloque Bloqueinicial  = laberinto.getBloqueSpawn();
      LaberintoEstructura::Bloque BloqueFinal = laberinto.getBloqueSalida();
      Juego juego(Bloqueinicial.fila, Bloqueinicial.columna, laberinto);
      LaberintoEstructura::Bloque* BloqueJugador = &juego.getBloqueActual(); // se usa un puntero para que siempre quede enlazado
      std::string exit = "";
      while( *BloqueJugador!=BloqueFinal){
        if(exit=="y"){
          break;
        }
        Console::showInfoMessage("Ingrese la direccion a moverse: \n w:arriba \n s:abajo \n a:izquierda \n d:derecha \n k: para reinicar");
        
        laberinto.imprimirMalla(modoImprecion , *BloqueJugador);

        std::string input = Console::inputManager();
        if(input=="k"){
          Console::clearConsole();
          Console::showInfoMessage("Te gustaria salir del programa? y/n");
          exit =  Console::inputManager();
          break;
        }
        if(input.size()==1){
            char c = input[0];
            juego.movimientoPersonaje(c);
            


        }
         
        else{

          Console::showInfoMessage("DATO INVALIDO ");
        }
        
      }
      
      
    }
    
    catch(const std::exception& e)
    {
      std::cerr << e.what() << "ERROR \n";
    }
    Console::waitForKeyPress();
    Console::showInfoMessage("¿JUGAR DE NUEVO? y/n");
    std::string input = Console::inputManager();
    if(input=="n"){
      Console::showInfoMessage("Gracias por jugar , me costo bastante el algortimo de generacion del algoritmo ");
      break;
    }

  }
  
  
  return 0;
}