## PLANTILLA PARA GOOGLE-TESTING CON DOCKER PARA PROYECTOS EN C++

## 🔹 Descripcion basica del proyecto

Este proyecto es un uego sencillo de consola, donde un personaje tienne que salir de un laberinto

## Funcionamiento:


Luego lo voy a llenar ,pero en resumen Laberitnor se encarga de rellenar la estrucutra que posee laclase laberintoEstructura , conolsa se encargad e dreciir informacion ... estoy cansado luego lo terminare 


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

# NOTAS
Es Posible que se pierda acceso a modificar diversos archivos dentro del contanier, si es asi se debe de ejecutar
estando en la carpeta raíz del proyecto
```bash
sudo chown -R $(whoami):$(whoami) .
sudo chmod -R u+rw .
```
