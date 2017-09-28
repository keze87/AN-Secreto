// main

#include "tests.h" //DEBUG

#define NUMERODEPADRON 97429

#define TRUE 0
#define FALSE 1

#define MESES 12
#define HORASPORANIO 8760
#define FACTORREDUCCIONPOTENCIA 0.3

float fcf (int potencia, double factorUso, float costoElec, int costoPot, int costos, float ganancias) {

	return (potencia * HORASPORANIO * factorUso * costoElec + potencia * FACTORREDUCCIONPOTENCIA * costoPot * MESES - costos) * (1 - ganancias) ;

}

int main () {

	correrTests(); //DEBUG

	return 0;

}
