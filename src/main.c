// main

#include "tests.h" // Pruebas Unitarias

#include <stdio.h>
#include <string.h>
#include <math.h>

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

double ahorroElectricidad (int potencia, double factorUso, float costoElec) {

	return (potencia * HORASPORANIO * factorUso * costoElec);

}

double ahorroPotencia (int potencia, int costoPot) {

	return (potencia * FACTORREDUCCIONPOTENCIA * costoPot * MESES);

}

double fcf (double ahorroElectricidad, double ahorroPotencia, int costos, float ganancias) {

	return (ahorroElectricidad + ahorroPotencia - costos) * (1 - ganancias) ;

}

struct vectorDatos cargarDatos () {

	struct vectorDatos aux;

	aux.potencia				= 30;
	aux.costoUnitarioPotencia	= 1800;
	aux.costos					= 5000;
	aux.ganancias				= 0.35;
	aux.factorUso				= 0.18 * NUMERODEPADRON / 100000;
	aux.costoElec				= 1.9;
	aux.costoPot				= 250;

	return aux;

}

void cargarMatriz (double matriz[5][N+1], struct vectorDatos datos) {

	// Inversion inicial
	matriz[0][0] = - datos.potencia * datos.costoUnitarioPotencia * DOLARAPESO;

	// En los demas años no hay inversion
	for (int i = 1; i <= N; i++)
		matriz[0][i] = 0;

	for (int i = 0; i <= N; i++) {

		matriz[1][i] = ahorroElectricidad(datos.potencia, datos.factorUso, datos.costoElec);

		matriz[2][i] = ahorroPotencia(datos.potencia, datos.costoPot);

		matriz[3][i] = datos.costos;

		matriz[4][i] = fcf (matriz[1][i], matriz[2][i], matriz[3][i], datos.ganancias);

	}

}

int largoDeNumeroRedondeado (double numero) {

	char aux[30];
	char auxInteger[30];
	char auxModulo[30];

	int entero = round(numero);
	int moduloEntero = fabs(round(numero));

	snprintf(auxInteger, 30, "%d", entero);
	snprintf(auxModulo, 30, "%d", moduloEntero);

	if (strlen(auxModulo) >= 3) {

		//TODO
		printf("%s\n",auxInteger);
		return strlen(auxInteger);

	} else if (strlen(auxModulo) >= 2) {

		snprintf(aux, 30, "%.1f", numero);

	} else if (strlen(auxModulo) >= 1) {

		snprintf(aux, 30, "%.2f", numero);

	}

	//TODO
	printf("%s\n",aux);

	return strlen(aux);

}

int imprimirTabla (struct vectorDatos datos) {

	double matriz [5][N+1];

	cargarMatriz(matriz,datos);

	//TODO
	/*for (int i = 0; i <= 4; i++) {
		for (int j = 0; j <= N; j++) {

			printf("%.1f",matriz[i][j]);

			if (j != N) { printf (" "); }
			else { printf("\n\n"); }
		}
	}*/

	return TRUE;

}

int proceso () {

	struct vectorDatos datos = cargarDatos();

	imprimirTabla(datos);

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
