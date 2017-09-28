// main

#include "tests.h" // Pruebas Unitarias

#define NUMERODEPADRON 97429

#define TRUE 0
#define FALSE 1

#define N 20
#define MESES 12
#define HORASPORANIO 8760
#define FACTORREDUCCIONPOTENCIA 0.3
#define DOLARAPESO 17.5

struct vectorDatos {

	// Inversion inicial
	int potencia;
	int costoUnitarioPotencia;

	// FCFn
	int costos;
	float ganancias;

	// Ahorros
	double factorUso;
	float costoElec;
	int costoPot;

};

float fcf (int potencia, double factorUso, float costoElec, int costoPot, int costos, float ganancias) {

	return (potencia * HORASPORANIO * factorUso * costoElec + potencia * FACTORREDUCCIONPOTENCIA * costoPot * MESES \
			- costos) * (1 - ganancias) ;

}

struct vectorDatos cargarDatos () {

	struct vectorDatos aux;

	aux.potencia				= 30000;
	aux.costoUnitarioPotencia	= 1800;
	aux.costos					= 5000;
	aux.ganancias				= 0.35;
	aux.factorUso				= 0.18 * NUMERODEPADRON / 100000;
	aux.costoElec				= 1.9;
	aux.costoPot				= 250;

	return aux;

}

int proceso () {

	struct vectorDatos datos = cargarDatos();

	//imprimirTabla(datos);

	/*buscarTIRBiseccion();

	buscarTIRPuntoFijo();

	buscarTIRSecante();

	buscarTIREscenarios();*/

	return TRUE;

}

int main () {

	correrTests(); // Pruebas Unitarias

	return proceso();

}
