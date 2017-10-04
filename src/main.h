// Solo para pruebas unitarias

#define NUMERODEPADRON 97429

#define TRUE 0
#define FALSE 1

#define N 20
#define MESES 12
#define HORASPORANIO 8760
#define FACTORREDUCCIONPOTENCIA 0.3
#define DOLARAPESO 17.5

#define MAXITERACIONES 32000
//TODO
#define MAXERROR 0.00000000005
#define FRACASO -32000

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

double ahorroElectricidad (int potencia, double factorUso, float costoElec);
double ahorroPotencia (int potencia, int costoPot);
double fcf (double ahorroElectricidad, double ahorroPotencia, int costos, float ganancias);
struct vectorDatos cargarDatos ();
char * redondear (double numero);
double biseccion (int inversion, double arrayFCF[N+1], double intervaloMin, double intervaloMax);
