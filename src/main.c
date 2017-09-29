// main

#include "tests.h" // Pruebas Unitarias

#include <stdio.h>
#include <stdlib.h>
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

char * redondear (double numero) {

	char * aux = malloc(sizeof(char) * 31);
	char * auxInteger = malloc(sizeof(char) * 31);
	char auxModulo[30];

	int entero = round(numero);

	snprintf(auxInteger, 30, "%d", entero);
	snprintf(auxModulo, 30, "%d", abs(entero));

	if (strlen(auxModulo) >= 3) {

		free(aux);

		return auxInteger;

	} else if (strlen(auxModulo) >= 2) {

		snprintf(aux, 30, "%.1f", numero);

	} else {

		snprintf(aux, 30, "%.2f", numero);

	}

	free(auxInteger);

	return aux;

}

void cargarMatrizRedondada (char * matriz[6][6], double matrizDatos[5][N+1]) {

	// Pido memoria para los titulos
	matriz[0][0] = malloc(sizeof(char) * 2);

	for (int i = 1; i < 6; i++) {

		matriz[i][0] = malloc(sizeof(char) * 22);
		matriz[i][4] = malloc(sizeof(char) * 4);
		matriz[0][i] = malloc(sizeof(char) * 22);

	}

	// Escribo los titulos
	strcpy(matriz[0][0], " "); strcpy(matriz[0][1], "Anio 0"); strcpy(matriz[0][2], "Anio 1"); \
					strcpy(matriz[0][3], "Anio 2"); strcpy(matriz[0][4], "..."); strcpy(matriz[0][5], "Anio N");
	strcpy(matriz[1][0], "Inversion");				strcpy(matriz[1][4], "...");
	strcpy(matriz[2][0], "Ahorro electricidad");	strcpy(matriz[2][4], "...");
	strcpy(matriz[3][0], "Ahorro potencia");		strcpy(matriz[3][4], "...");
	strcpy(matriz[4][0], "Costos");					strcpy(matriz[4][4], "...");
	strcpy(matriz[5][0], "FCF");					strcpy(matriz[5][4], "...");

	// Agrego los datos
	for (int i = 1; i <= 3; i++) {

		// Inversiones
		matriz[1][i] = redondear(matrizDatos[0][i - 1]); strcat(matriz[1][i], " $");

		// Ahorros E
		matriz[2][i] = redondear(matrizDatos[1][i - 1]); strcat(matriz[2][i], " $");

		// Ahorros P
		matriz[3][i] = redondear(matrizDatos[2][i - 1]); strcat(matriz[3][i], " $");

		// Costos
		matriz[4][i] = redondear(matrizDatos[3][i - 1]); strcat(matriz[4][i], " $");

		// FCFs
		matriz[5][i] = redondear(matrizDatos[4][i - 1]);

	}

	// Año n
	// Inversiones
	matriz[1][5] = redondear(matrizDatos[0][N]); strcat(matriz[1][5], " $");

	// Ahorros E
	matriz[2][5] = redondear(matrizDatos[1][N]); strcat(matriz[2][5], " $");

	// Ahorros P
	matriz[3][5] = redondear(matrizDatos[2][N]); strcat(matriz[3][5], " $");

	// Costos
	matriz[4][5] = redondear(matrizDatos[3][N]); strcat(matriz[4][5], " $");

	// FCFs
	matriz[5][5] = redondear(matrizDatos[4][N]);

}

void liberarMemoriaMatriz (char * matriz[6][6]) {

	for (int i = 0; i <= 5; i++)
		for (int j = 0; j <= 5; j++)
			free(matriz[i][j]);

}

void calcularAnchoFilas (int anchos[6], char * matriz[6][6]) {

	for (int i = 0; i < 6; i++)
		anchos[i] = 0;

	for (int j = 0; j < 6; j++) {

		for (int i = 0; i < 6; i++) {

			if (strlen(matriz[i][j]) > anchos[j])
				anchos[j] = strlen(matriz[i][j]);

		}

	}

}

void imprimirLineaSeparadora (int anchos[6]) {

	int i = 0;

	int anchoTotal = 0;

	for (int j = 0; j < 6; j++)
		anchoTotal = anchoTotal + anchos[j];

	anchoTotal = anchoTotal + 5 * 3; // Tamaño separador

	printf("\n");

	while (i < anchoTotal) {

		printf("-");

		i++;

	}

	printf("\n");

}

void imprimirSeparador (int anchoElemento, int anchoFila) {

	int aux = anchoElemento;

	while (aux < anchoFila) {

		printf(" ");

		aux++;

	}

	printf(" | ");

}

void imprimirMatriz (char * matriz[6][6]) {

	int anchos [6];

	calcularAnchoFilas(anchos, matriz);

	for (int i = 0; i < 6; i++) {

		for (int j = 0; j < 6; j++) {

			printf("%s", matriz[i][j]);

			if (j != 5)
				imprimirSeparador(strlen(matriz[i][j]), anchos[j]);

		}

		if (i != 5)
			imprimirLineaSeparadora(anchos);

	}

	printf("\n");

}

int imprimirTabla (struct vectorDatos datos) {

	double matriz [5][N+1];
	char * matrizRedondeada [6][6];

	cargarMatriz(matriz,datos);
	cargarMatrizRedondada(matrizRedondeada,matriz);

	imprimirMatriz(matrizRedondeada);

	liberarMemoriaMatriz(matrizRedondeada);

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
