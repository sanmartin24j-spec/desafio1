#include <iostream>
#include "tablero.h"

using namespace std;

int main()
{
    int semilla;

    cout <<"Ingrese una semilla: " << endl;
    cin >> semilla;

    int filas, columnas, cantidadfichas, totalbits, totalbytes;

    cout <<"Ingrese filas" << endl;
    cin >> filas;

    cout <<"Ingrese columnas" << endl;
    cin >> columnas;

    cantidadfichas = filas * columnas;
    totalbits = cantidadfichas * 3;
    totalbytes = (totalbits + 7) / 8;

    unsigned char *tablero = new unsigned char[totalbytes];

    for (int i = 0; i < totalbytes; i++)
    {
        tablero[i] = 0;
    }

    cout << "Total de bytes: " << totalbytes << endl;

    llenarTablero(tablero, filas, columnas, &semilla);

    mostrarTablero(tablero, filas, columnas);

    delete[] tablero;
    tablero = nullptr;

    return 0;
}
