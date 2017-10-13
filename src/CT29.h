// Solo para pruebas unitarias

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

double ahorroElectricidad (int potencia, double factorUso, float costoElec);
double ahorroPotencia (int potencia, int costoPot);
double fcf (double ahorroElectricidad, double ahorroPotencia, int costos, float ganancias);
struct vectorDatos cargarDatos ();
char * redondear (double numero);
double biseccion (int inversion, double arrayFCF[N+1], double intervaloMin, double intervaloMax);
double vanDerivada (double i, int inversion, double arrayFCF[N+1]);
char * incerteza (char * raiz);
double potencia (double x, int n);
double error (double Xk1, double Xk);

