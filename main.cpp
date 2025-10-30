

#include "Console.h"
#include "Laberinto.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int main() {
  Laberinto laberinto;
  Console::clearConsole();
  Console::showInfoMessage("Bienvenido al programa");
  Console::showInfoMessage("Por favor, ingrese los datos solicitados.");
  
  laberinto.rellenarEspacio();

  return 0;
}