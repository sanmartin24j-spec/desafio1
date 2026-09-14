#include <iostream>

using namespace std;


unsigned char leerficha(unsigned char byte, int desplazamiento);

unsigned char escribirficha(unsigned char byte, unsigned char ficha, int desplazamiento);

int main()
{
    unsigned char byte = 0b10010100;
    unsigned char lectura= leerficha(byte, 3);
    unsigned char ficha = 0b111;
    byte = escribirficha(byte, ficha, 3);
    unsigned char lecturaNueva = leerficha(byte, 3);

    cout <<"anterior "<< (int) lectura<<endl;
    cout <<"nueva "<< (int) lecturaNueva;

    return 0;
}


unsigned char leerficha(unsigned char byte, int desplazamiento)
{
    byte = byte >> desplazamiento;
    byte = byte & 0b00000111;

    return byte;
}

unsigned char escribirficha(unsigned char byte, unsigned char ficha,int desplazamiento)
{
    ficha = ficha & 0b00000111;
    unsigned char zona = 0b00000111 << desplazamiento;
    unsigned char limpieza = ~zona;
    byte = byte & limpieza;
    unsigned char fichamovida = ficha << desplazamiento;
    byte = byte | fichamovida;
    return byte;
}