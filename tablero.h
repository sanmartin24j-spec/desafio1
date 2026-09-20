#ifndef TABLERO_H
#define TABLERO_H

void escribirFicha(unsigned char *tablero, int byteActual, int desplazamiento, unsigned char ficha);
unsigned char leerFicha(unsigned char *tablero, int byteActual, int desplazamiento);
void encontraficha (int fila, int columna, int columnas, int *byteactual, int *desplazamiento );
void llenarTablero(unsigned char *tablero,int filas, int columnas, int *semilla);
void mostrarTablero(unsigned char *tablero, int filas,int columnas);


#endif // TABLERO_H
