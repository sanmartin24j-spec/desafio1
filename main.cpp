#include <iostream>
using namespace std;
void escribirFicha(unsigned char *tablero, int byteActual, int desplazamiento, unsigned char ficha);
unsigned char leerFicha(unsigned char *tablero, int byteActual, int desplazamiento);
void encontraficha (int fila, int columna, int columnas, int *byteactual, int *desplazamiento );
void llenarTablero(unsigned char *tablero,int filas, int columnas, int *semilla);
void mostrarTablero(unsigned char *tablero, int filas,int columnas);

int main ()
{
    int byteactual;
    int desplazamiento;
    int fila;
    int columna;
    int semilla;
    cout<<"Ingrese una semilla "<<endl;
    cin>>semilla;

    int filas, columnas, cantidadfichas, totalbits, totalbytes;

    cout<<"Ingrese filas"<<endl;
    cin>>filas;
    cout<<"Ingrese columnas"<<endl;
    cin>>columnas;

    cantidadfichas= filas* columnas;
    totalbits=cantidadfichas*3;
    totalbytes=(totalbits+7)/8;
    unsigned char *tablero= new unsigned char [totalbytes];

    for (int i=0;i<totalbytes;i++)
    {
        tablero[i]=0;
    }
    cout<<"Total de bytes: "<<totalbytes<<endl;

    cout<<"Ingrese fila de la ficha"<<endl;
    cin>>fila;
    cout<<"Ingrese columna de la ficha"<<endl;
    cin>>columna;


    encontraficha(fila, columna, columnas, &byteactual, &desplazamiento);
    int valorFicha;
    cout << "Ingrese ficha entre 0 y 7" << endl;
    cin >> valorFicha;

    unsigned char ficha = valorFicha;

    escribirFicha(tablero, byteactual, desplazamiento, ficha);

    unsigned char lectura =leerFicha(tablero, byteactual, desplazamiento);

    cout << "Ficha leida: " << (int)lectura << endl;


    cout <<"Byte actual es el:  "<< byteactual << endl;
    cout << "Desplazamiento es:  "<< desplazamiento << endl;
    llenarTablero(tablero,filas,columnas,&semilla);
    mostrarTablero(tablero, filas,columnas);

    delete []tablero;
    tablero= nullptr;


    return 0;
}




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

