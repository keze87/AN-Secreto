// César Ezequiel Herrera 97429
// Numero de grupo: 29
//
// Repo con pruebas unitarias:
// https://github.com/keze87/CT29
//
// Make:
// gcc -lm -std=c11 -Wall -pedantic -pedantic-errors -o CT29 CT29.c -I.

#include "tests.h" // Pruebas Unitarias

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUMERODEPADRON 97429

#define TRUE 0
#define FALSE 1

#define MAXITERACIONES 32000
#define FRACASO -300000

#define N 20
#define h 0.000001
#define MINDIVISOR 0.0000000001
#define TAMMATRIZ 6
#define MESES 12
#define HORASPORANIO 8760
#define FACTORREDUCCIONPOTENCIA 0.3
#define DOLARAPESO 17.5

struct vectorDatos {

	// Inversion inicial
	int potencia;
	double costoUnitarioPotencia;

	// FCFn
	int costos;
	float ganancias[N+1];

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

	return (ahorroElectricidad + ahorroPotencia - costos) * (1 - ganancias);

}

struct vectorDatos cargarDatos () {

	struct vectorDatos aux;

	aux.potencia				= 30;
	aux.costoUnitarioPotencia	= 1800;
	aux.costos					= 5000;
	aux.factorUso				= 0.18 * NUMERODEPADRON / 100000;
	aux.costoElec				= 1.9;
	aux.costoPot				= 250;

	for (int i = 0; i <= N; i++) {

		aux.ganancias[i] = 0.35;

	}

	return aux;

}

// Llena la matriz con los datos
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

		matriz[4][i] = fcf(matriz[1][i], matriz[2][i], matriz[3][i], datos.ganancias[i]);

	}

}

// Devuelve un string de el numero redondeado
char * redondear (double numero) {

	char * aux = malloc(sizeof(char) * 31);
	char * auxInteger = malloc(sizeof(char) * 31);
	char auxModulo[30];

	long entero = round(numero);

	snprintf(auxInteger, 30, "%li", entero);
	snprintf(auxModulo, 30, "%li", labs(entero));

	// Si es mayor o igual (en modulo) a 100 devuelvo solo la parte entera
	// Sino devuelvo un decimal o 2
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

// Llena una matriz (para imprimir) con los titulos y los números redondeados
void cargarMatrizRedondada (char * matriz[TAMMATRIZ][TAMMATRIZ], double matrizDatos[5][N+1]) {

	// Pido memoria para los titulos
	matriz[0][0] = malloc(sizeof(char) * 2);

	for (int i = 1; i < TAMMATRIZ; i++) {

		matriz[i][0] = malloc(sizeof(char) * 22);
		matriz[i][4] = malloc(sizeof(char) * 4);
		matriz[0][i] = malloc(sizeof(char) * 22);

	}

	// Escribo los titulos
	strcpy(matriz[0][0], " "); strcpy(matriz[0][1], "Anio 0"); strcpy(matriz[0][2], "Anio 1");
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
		matriz[5][i] = redondear(matrizDatos[4][i - 1]); strcat(matriz[5][i], " $");

	}

	// Año N
	// Inversiones
	matriz[1][5] = redondear(matrizDatos[0][N]); strcat(matriz[1][5], " $");

	// Ahorros E
	matriz[2][5] = redondear(matrizDatos[1][N]); strcat(matriz[2][5], " $");

	// Ahorros P
	matriz[3][5] = redondear(matrizDatos[2][N]); strcat(matriz[3][5], " $");

	// Costos
	matriz[4][5] = redondear(matrizDatos[3][N]); strcat(matriz[4][5], " $");

	// FCFs
	matriz[5][5] = redondear(matrizDatos[4][N]); strcat(matriz[5][5], " $");

}

void liberarMemoriaMatriz (char * matriz[TAMMATRIZ][TAMMATRIZ]) {

	for (int i = 0; i < TAMMATRIZ; i++)
		for (int j = 0; j < TAMMATRIZ; j++)
			free(matriz[i][j]);

}

// Busca el largo del elemento mas largo de cada columna
void calcularAnchoColumnas (int anchos[TAMMATRIZ], char * matriz[TAMMATRIZ][TAMMATRIZ]) {

	for (int i = 0; i < TAMMATRIZ; i++)
		anchos[i] = 0;

	for (int i = 0; i < TAMMATRIZ; i++) {

		for (int j = 0; j < TAMMATRIZ; j++) {

			if (strlen(matriz[j][i]) > anchos[i])
				anchos[i] = strlen(matriz[j][i]);

		}

	}

}

// Imprime linea entre filas
void imprimirLineaSeparadora (int anchos[TAMMATRIZ]) {

	int i = 0;

	int anchoTotal = 0;

	for (int j = 0; j < TAMMATRIZ; j++)
		anchoTotal = anchoTotal + anchos[j];

	anchoTotal = anchoTotal + 5 * 3; // Tamaño separador

	printf("\n");

	while (i <= anchoTotal) {

		printf("-");

		i++;

	}

	printf("\n");

}

// Imprime espacios y un separador
void imprimirSeparador (int anchoElemento, int anchoColumna) {

	int aux = anchoElemento;

	while (aux < anchoColumna) {

		printf(" ");

		aux++;

	}

	printf(" | ");

}

// Imprime matriz de Strings agregando separadores
void imprimirMatriz (char * matriz[TAMMATRIZ][TAMMATRIZ]) {

	int anchos[TAMMATRIZ];

	calcularAnchoColumnas(anchos, matriz);

	for (int i = 0; i < TAMMATRIZ; i++) {

		for (int j = 0; j < TAMMATRIZ; j++) {

			printf("%s", matriz[i][j]);

			if (j != TAMMATRIZ - 1)
				imprimirSeparador(strlen(matriz[i][j]), anchos[j]);

		}

		if (i != TAMMATRIZ - 1)
			imprimirLineaSeparadora(anchos);

	}

	printf("\n");

}

// Calcula datos y manda a imprimir
int imprimirTabla (double matriz[5][N+1]) {

	char * matrizRedondeada[TAMMATRIZ][TAMMATRIZ];

	cargarMatrizRedondada(matrizRedondeada, matriz);

	imprimirMatriz(matrizRedondeada);

	liberarMemoriaMatriz(matrizRedondeada);

	return TRUE;

}

double potencia (double x, int n) {

	double aux = 1;

	for (int i = 1; i < n; i++) {

		aux = aux * x;

	}

	return aux;

}

double sumatoriaVan (double x, double arrayFCF[N+1]) {

	double aux = 0;

	for (int i = 1; i <= N; i++) {

		aux = aux + arrayFCF[i] / potencia(1 + x, i);

	}

	return aux;

}

// Io+Sum[FCFn/(i+1)^n, {n, 20}]
double van (double i, int inversion, double arrayFCF[N+1]) {

	if (i != -1)
		return inversion + sumatoriaVan(i, arrayFCF);

	return FRACASO;

}

double error (double Xk1, double Xk) {

	return fabs(Xk1 - Xk) / fabs(Xk1) * 100;

}

double biseccion (int inversion, double arrayFCF[N+1], double intervaloMin, double intervaloMax) {

	int i = 1;

	double puntoMedio = intervaloMin;
	double puntoMedioAnterior;

	if ( ! ((intervaloMin < intervaloMax) && \
			(van(intervaloMin, inversion, arrayFCF) * van(intervaloMax, inversion, arrayFCF) < 0)) ) {

			printf("No se puede resolver por bisección.\n");

			return FRACASO;

	}

	while (i < MAXITERACIONES) {

		puntoMedioAnterior = puntoMedio;
		puntoMedio = (intervaloMin + intervaloMax) / 2;

		if ((van(puntoMedio, inversion, arrayFCF) == 0) || (error(puntoMedio, puntoMedioAnterior) < 1 /* % */)) {

			break; // Encontre solución

		}

		if (van(intervaloMin, inversion, arrayFCF) * van(puntoMedio, inversion, arrayFCF) < 0) {

			intervaloMax = puntoMedio;

		} else {

			intervaloMin = puntoMedio;

		}

		i++;

	}

	return puntoMedio;

}

// PRE: decimales despues del punto
char * incerteza (char * raiz) {

	char * punteroADecimalDespuesDePunto = NULL;
	char * retorno = malloc(sizeof(char) * 30);
	int cantidadDeDecimales;

	// el puntero es igual a la posicion de memoria del caracter despues del punto
	// "123.456" -> "456"
	for (int i = 0; i < strlen(raiz); i++) {

		if (raiz[i] == '.') {

			punteroADecimalDespuesDePunto = raiz + i + 1;

			break;

		}

	}

	if (punteroADecimalDespuesDePunto == NULL) {

		strcpy(retorno, "1");

		return retorno;

	}

	cantidadDeDecimales = strlen(punteroADecimalDespuesDePunto);

	strcpy(retorno, "0.");

	for (int j = 1; j < cantidadDeDecimales; j++)
		strcat(retorno,"0");

	strcat(retorno,"1");

	return retorno;

}

void imprimirRaiz (double raiz, char * metodo) {

	//printf("%.16F\n", raiz);

	if (raiz != FRACASO) {

		printf("Raiz por %s: ", metodo);

		char * auxRaiz = redondear(raiz);
		char * auxIncerteza = incerteza(auxRaiz);

		printf("%s +/- %s\n", auxRaiz, auxIncerteza);

		free(auxRaiz); free(auxIncerteza);

	}

}

double buscarTIRBiseccion (int inversion, double arrayFCF[N+1]) {

	// Busco en un intervalo [0.02, 0.06]
	double raiz = biseccion(inversion, arrayFCF, 0.02, 0.06);

	imprimirRaiz(raiz, "biseccion");

	return raiz;

}

// (f(x + h) - f(x)) / h, h -> 0
double vanDerivada (double i, int inversion, double arrayFCF[N+1]) {

	if (i != -1)
		return (van(i + h, inversion, arrayFCF) - van(i, inversion, arrayFCF)) / h;

	return FRACASO;

}

// g(x) = f(x) / f'(x)
double puntoFijo (int inversion, double arrayFCF[N+1], double semilla) {

	int i = 1;
	double Xi1;
	double Xi = semilla;
	double fXi;

	while (i < MAXITERACIONES) {

		double resultadoDerivada = vanDerivada(Xi, inversion, arrayFCF);

		if (fabs(resultadoDerivada) < MINDIVISOR) {

			printf("No se puede resolver por punto fijo.\n");

			return FRACASO;

		}

		fXi = van(Xi, inversion, arrayFCF);

		Xi1 = Xi - fXi / resultadoDerivada;

		if (fabs(Xi1 - Xi) > 1) {

			printf("No se puede resolver por punto fijo.\n");

			return FRACASO;

		} else if (error(Xi1, Xi) < 1 /* % */) {

			break;

		}

		Xi = Xi1;

		i++;

	}

	return Xi1;

}

void buscarTIRPuntoFijo (double raizBiseccion, int inversion, double arrayFCF[N+1]) {

	double raiz = puntoFijo(inversion, arrayFCF, raizBiseccion - 0.1);

	imprimirRaiz(raiz, "punto fijo");

}

double secante (int inversion, double arrayFCF[N+1], double intervaloMin, double intervaloMax) {

	int i = 1;
	double XiMas1;
	double Xi = intervaloMax;
	double XiMenos1 = intervaloMin;

	double fXi;
	double fXiMenos1;

	while (i < MAXITERACIONES) {

		fXi = van(Xi, inversion, arrayFCF);
		fXiMenos1 = van(XiMenos1, inversion, arrayFCF);

		XiMas1 = Xi - (Xi - XiMenos1) * fXi / (fXi - fXiMenos1);

		if (fabs(XiMas1 - XiMenos1) > 1) {

			printf("No se puede resolver por puntoFijo.\n");

			return FRACASO;

		} else if (error(XiMas1, Xi) < 1 /* % */) {

			break;

		}

		if (fabs(XiMas1 - XiMenos1) < fabs(Xi - XiMas1)) {

			XiMenos1 = XiMas1;

		} else {

			Xi = XiMas1;

		}

		i++;

	}

	return XiMas1;

}

void buscarTIRSecante (double raizBiseccion, int inversion, double arrayFCF[N+1]) {

	double raiz = secante(inversion, arrayFCF, raizBiseccion - 0.1, raizBiseccion + 0.1);

	imprimirRaiz(raiz, "secante");

}

void buscarTIREscenarios () {

	double matriz [5][N+1];
	struct vectorDatos datos = cargarDatos();

	// a)
	datos.costoUnitarioPotencia = datos.costoUnitarioPotencia * 0.7;
	cargarMatriz(matriz,datos);

	printf("a)\n");
	imprimirRaiz(biseccion(matriz[0][0], matriz[4], 0.08, 0.11), "biseccion"); // 0.08757777

	// b)
	datos = cargarDatos();
	for (int i = 0; i <= N; i++)
		datos.ganancias[i] = 0;

	cargarMatriz(matriz,datos);

	printf("b)\n");
	imprimirRaiz(biseccion(matriz[0][0], matriz[4], 0, 0.13), "biseccion");

	// c)
	datos = cargarDatos();
	datos.costoElec = datos.costoElec * 2;
	cargarMatriz(matriz,datos);

	printf("c)\n");
	imprimirRaiz(biseccion(matriz[0][0], matriz[4], 0, 0.2), "biseccion");

	// d)
	datos = cargarDatos();
	datos.factorUso = 0.2;
	cargarMatriz(matriz,datos);

	printf("d)\n");
	imprimirRaiz(biseccion(matriz[0][0], matriz[4], 0, 0.11), "biseccion");

	// e)
	datos = cargarDatos();

	if (N > 5)
		for (int i = 0; i <= 5; i++)
			datos.ganancias[i] = 0;

	cargarMatriz(matriz,datos);

	printf("e)\n");
	imprimirRaiz(biseccion(matriz[0][0], matriz[4], 0, 1), "biseccion");

}

void imprimirEnunciado (short enunciado) {

	switch (enunciado) {

		case 1:
			printf("\n1) Calcular la inversión requerida, los ahorros y el resultado del flujo de fondos para cada año.\n");
			printf("   Mostrar los valores en una tabla:\n\n");
			break;

		case 2:
			printf("\n2) Aplicar el método de bisección para calcular la TIR del proyecto.\n");
			printf("   Para ello, encuentre un intervalo que contenga a la raíz buscada e itere hasta lograr una precisión de 1%%.\n");
			printf("   Exprese el resultado correctamente.\n\n");
			break;

		case 3:
			printf("\n3) Aplicar el método de punto fijo para calcular la TIR del proyecto utilizando la función de iteración g(x) = x - f(x).\n");
			printf("   Para ello, utilice como semilla, un valor similar al encontrado mediante bisección.\n");
			printf("   Exprese el resultado correctamente.\n\n");
			break;

		case 4:
			printf("\n5) Repita el punto 3) aplicando el método de la secante.\n\n");
			break;

		case 5:
			printf("\n7) Calcule la TIR del proyecto utilizando el método de la secante para los siguientes escenarios:\n");
			printf("   a) El costo unitario de la instalación fotovoltaica se reduce un 30%%.\n");
			printf("   b) Los proyectos solares quedan exentos del pago del impuesto a las ganancias (α=0).\n");
			printf("   c) El costo de la electricidad se duplica.\n");
			printf("   d) La constante del Factor de Uso aumenta a 0,2 (mejora la eficiencia de los paneles)\n");
			printf("   e) Los proyectos solares quedan exentos del pago del impuesto a las ganancias por los primeros 5 años.\n\n");
			break;

		default :
			printf("Error\n");

	}

}

int proceso () {

	double raizBiseccion;
	struct vectorDatos datos = cargarDatos();

	double matriz [5][N+1];
	cargarMatriz(matriz,datos);

	imprimirEnunciado(1);
	imprimirTabla(matriz);

	imprimirEnunciado(2);
	raizBiseccion = buscarTIRBiseccion(/* Inversión */matriz[0][0], /* FCF */matriz[4]);

	imprimirEnunciado(3);
	buscarTIRPuntoFijo(raizBiseccion, /* Inversión */matriz[0][0], /* FCF */matriz[4]);

	imprimirEnunciado(4);
	buscarTIRSecante(raizBiseccion, /* Inversión */matriz[0][0], /* FCF */matriz[4]);

	imprimirEnunciado(5);
	buscarTIREscenarios();

	printf("\n");

	return TRUE;

}

int main () {

	printf("\nCesar Ezequiel Herrera 97429\n");

	correrTests(); // Pruebas Unitarias

	return proceso();

}
