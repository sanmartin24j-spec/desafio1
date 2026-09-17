#include <iostream>
using namespace std;
void escribirFicha(unsigned char *tablero, int byteActual, int desplazamiento, unsigned char ficha);
unsigned char leerFicha(unsigned char *tablero, int byteActual, int desplazamiento);


int main()
{
    unsigned char tablero[2];

    tablero[0] = 0b11101010;
    tablero[1] = 0b10110010;
    unsigned char ficha = 0b110;
    int desplazamiento = 7;
    escribirFicha(tablero, 0, desplazamiento, ficha);


    unsigned char lectura =leerFicha(tablero, 0, desplazamiento);
    cout << "Ficha leida: "<< (int)lectura<< endl;

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
