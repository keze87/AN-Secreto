// Solo para pruebas unitarias

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

float fcf (int potencia, double factorUso, float costoElec, int costoPot, int costos, float ganancias);
struct vectorDatos cargarDatos ();
