#pragma once
#include <iostream>
#include "keyboard.h"
#include <chrono>
#include <list>
#include <deque>
#define FILA 10
#define COLUMNA 20

void HacerTablero(char tablero[FILA][COLUMNA]) {
    for (int i = 0; i < COLUMNA; i++) {
        for (int j = 0; j < 20; j++) {
            tablero[i][j] = ' ';
        }
    }
}

void GenerarComida(char tablero[COLUMNA][20]) {
    int fila, columna;
    bool posvalida = false;
    while (!posvalida)
    {
        std::srand(std::time(0));
        fila = std::rand() % COLUMNA;
        columna = std::rand() % 20;
        if (tablero[fila][columna] == ' ') {
            posvalida = true;
            tablero[fila][columna] = 'O';
        }
    }
}

void ImprimirTablero(char tablero[COLUMNA][20]) {
    system("cls");
    for (int j = 0; j < 22; j++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i = 0; i < FILA; i++) {
            std::cout << "|";
        for (int j = 0; j < COLUMNA; j++) {
            std::cout << tablero[i][j];
        }
            std::cout << "|";
        std::cout << std::endl;
    }
    for (int j = 0; j < 22; j++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

void Movimiento(char tablero[FILA][COLUMNA]) {
    int puntuacion = 0;
    int fila = 5;
    int columna = 10;
    struct Posicion {
        int fila;
        int columna;
    };
    std::deque<Posicion> serpiente;
    Posicion cabeza = { 5, 10 };
    serpiente.push_front(cabeza);
    tablero[cabeza.fila][cabeza.columna] = 'X';

    int movimiento = 0;
    int comida = 0;
    bool partida = false;
    while (!partida)
    {
        if (IsDPressed() && movimiento != 2) {
            movimiento = 1;
        }
        else if (IsAPressed() && movimiento != 1 && movimiento != 0) {
            movimiento = 2;
        }
        else if (IsWPressed() && movimiento != 4 && movimiento != 0) {
            movimiento = 3;
        }
        else if (IsSPressed() && movimiento != 3 && movimiento != 0) {
            movimiento = 4;
        }
        Posicion originalCabeza = serpiente.front();
        tablero[originalCabeza.fila][originalCabeza.columna] = ' ';

        Posicion nuevaCabeza = originalCabeza;

        switch (movimiento) {
        case 1:
            (nuevaCabeza.columna) += 1;
            break;
        case 2:
            (nuevaCabeza.columna) -= 1;
            break;
        case 3:
            (nuevaCabeza.fila) -= 1;
            break;
        case 4:
            (nuevaCabeza.fila) += 1;
            break;

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        if (nuevaCabeza.columna >= 20 || nuevaCabeza.columna < 0 || nuevaCabeza.fila >= 10 || nuevaCabeza.fila < 0) {
            partida = true;
        }
        if (tablero[nuevaCabeza.fila][nuevaCabeza.columna] == 'x') {
            partida = true;
        }else if (tablero[nuevaCabeza.fila][nuevaCabeza.columna] == 'O') {
            comida += 1;
            serpiente.push_front(nuevaCabeza);
            tablero[nuevaCabeza.fila][nuevaCabeza.columna] = 'X';    
            puntuacion += 15;
        }else {
            Posicion cola = serpiente.back();
            serpiente.pop_back();
            tablero[cola.fila][cola.columna] = ' ';
            serpiente.push_front(nuevaCabeza);
            tablero[nuevaCabeza.fila][nuevaCabeza.columna] = 'X';
        }
        for (int i = 1; i < serpiente.size(); ++i) {
            Posicion cuerpo = serpiente[i];
            tablero[cuerpo.fila][cuerpo.columna] = 'x';
        }
        bool haycomida = false;
        if (movimiento != 0) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 20; j++) {
                    if (tablero[i][j] == 'O') {
                        haycomida = true;
                    }
                }
            }
            if (!haycomida) {
                GenerarComida(tablero);
            }
            puntuacion += 1;
            ImprimirTablero(tablero);
            std::cout << "Puntuacion total: " << puntuacion << std::endl;
        }
    }
}