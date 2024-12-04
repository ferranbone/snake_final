#include <iostream>
#include <thread>
#include <chrono>
#include "keyboard.h"
#include "MainLibrary.h"

int main() {
    const int fila = 10;
    const int columna = 20;
    char tablero[fila][columna];
    bool bGameOver = false;
    int otravez = 0;
    while (!bGameOver) {
        HacerTablero(tablero);
        ImprimirTablero(tablero);
        Movimiento(tablero);
        std::cout << std::endl << "Has perdido, quieres volver a jugar? 1: Si 2: No" << std::endl;
        otravez = 0;
        std::cin >> otravez;
        if (otravez == 2) {
            bGameOver = true;
        }
        else if (otravez != 1) {
            std::cout << "Caracter invalido";
            bGameOver = true;
        }
    }
}