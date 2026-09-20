#include <iostream>
#include "tablero.h"

using namespace std;

void escribirFicha(unsigned char *tablero, int byteActual, int desplazamiento, unsigned char ficha)
{

    ficha= ficha&0b00000111;

    if (desplazamiento <= 5){
        unsigned char zona = 0b0000111<<desplazamiento;

        unsigned char limpieza = ~zona;

        tablero[byteActual] =  tablero[byteActual]&limpieza;

        tablero[byteActual] =  tablero[byteActual] | (ficha << desplazamiento); }

    else{
        int bitsprimerbyte= 8 - desplazamiento;
        int bitssegundobyte= 3 - bitsprimerbyte;
        unsigned char mascaraprimerbyte = (1 << bitsprimerbyte) - 1;
        unsigned char zonaprimerbyte = mascaraprimerbyte << desplazamiento;
        unsigned char limpiezaprimerbyte =~zonaprimerbyte;
        tablero[byteActual] =tablero[byteActual] & limpiezaprimerbyte;

        tablero[byteActual] =tablero[byteActual] |((ficha & mascaraprimerbyte) << desplazamiento);


        unsigned char mascarasegundobyte =(1 << bitssegundobyte) - 1;
        unsigned char limpiezasegundobyte =~mascarasegundobyte;
        tablero[byteActual + 1] = tablero[byteActual + 1] & limpiezasegundobyte;

        tablero[byteActual + 1] = tablero[byteActual + 1] |((ficha >> bitsprimerbyte) & mascarasegundobyte);}

}

unsigned char leerFicha(unsigned char *tablero, int byteActual, int desplazamiento)
{
    if (desplazamiento <= 5){
        return (tablero[byteActual] >> desplazamiento)& 0b00000111;}
    else {
        int bitsprimerbyte = 8 - desplazamiento;
        int bitssegundobyte = 3 - bitsprimerbyte;
        unsigned char mascaraprimerbyte =(1 << bitsprimerbyte) - 1;
        unsigned char mascarasegundobyte =(1 << bitssegundobyte) - 1;
        unsigned char parteprimerbyte =(tablero[byteActual] >> desplazamiento) & mascaraprimerbyte;
        unsigned char partesegundobyte =tablero[byteActual + 1] & mascarasegundobyte;

        return parteprimerbyte |(partesegundobyte << bitsprimerbyte); }
}

void encontraficha (int fila, int columna, int columnas, int *byteactual, int *desplazamiento )
{
    int indice=fila*columnas+columna;
    int bitini= indice*3;
    *byteactual=bitini/8;
    *desplazamiento=bitini%8;
}
void llenarTablero(unsigned char *tablero,int filas, int columnas, int *semilla)
{
    int byteactual;
    int desplazamiento;


    for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0; columna < columnas; columna++)
        {
            encontraficha(fila, columna, columnas, &byteactual, &desplazamiento);
            *semilla=(*semilla*4+3)%97;
            int ficha = (*semilla) % 6;
            escribirFicha(tablero, byteactual, desplazamiento, ficha);
        }
    }
}

void mostrarTablero(unsigned char *tablero, int filas,int columnas)
{
    int byteactual;
    int desplazamiento;
    int resultado;
    for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0; columna < columnas; columna++)
        {
            encontraficha(fila, columna, columnas, &byteactual, &desplazamiento);

            resultado =leerFicha(tablero, byteactual, desplazamiento);
            cout<<resultado<< " ";
        }
        cout << endl;
    }

}