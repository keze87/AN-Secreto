#include "greatest.h"
#include "CT29.h"

TEST testAuxiliares (void) {

	GREATEST_ASSERT_EQ(8, potencia(2, 3));

	GREATEST_ASSERT(error(0.04271, 0.042480) < 1 /* % */);

	PASS();

}

TEST testCalcularFCF (void) {

	double factorUso = 0.18 * NUMERODEPADRON / 100000;

	double ahorroElec = ahorroElectricidad(30, factorUso, 1.9);
	double ahorroPot = ahorroPotencia(30, 250);

	GREATEST_ASSERT_IN_RANGE(87566.846904, ahorroElec, 0.01);
	GREATEST_ASSERT_EQ(27000, ahorroPot);

	GREATEST_ASSERT_IN_RANGE(71218.4504876, fcf(ahorroElec, ahorroPot, 5000, 0.35), 0.01);

	PASS();

}

TEST testCargarDatos (void) {

	struct vectorDatos datos = cargarDatos();

	GREATEST_ASSERT_EQ(30,		datos.potencia);
	GREATEST_ASSERT_EQ(1800,	datos.costoUnitarioPotencia);
	GREATEST_ASSERT_EQ(5000,	datos.costos);

	double factorUso = 0.18 * NUMERODEPADRON / 100000;
	GREATEST_ASSERT_EQ(factorUso,	datos.factorUso);
	GREATEST_ASSERT_EQ(250,			datos.costoPot);
	GREATEST_ASSERT_IN_RANGE(0.35,	datos.ganancias[0], 0.000001); //TODO es un array
	GREATEST_ASSERT_IN_RANGE(1.9,	datos.costoElec, 0.000001);

	PASS();

}

TEST testRedondeoNumero (void) {

	char * aux;

	aux = redondear(1);
	GREATEST_ASSERT_STR_EQ("1.00",	aux); free(aux);

	aux = redondear(1.00015456);
	GREATEST_ASSERT_STR_EQ("1.00",	aux); free(aux);

	aux = redondear(1000.1);
	GREATEST_ASSERT_STR_EQ("1000",	aux); free(aux);

	aux = redondear(-0.0006);
	GREATEST_ASSERT_STR_EQ("-0.00",	aux); free(aux);

	aux = redondear(71218.4504876);
	GREATEST_ASSERT_STR_EQ("71218",	aux); free(aux);

	aux = redondear(87566.846904);
	GREATEST_ASSERT_STR_EQ("87567",	aux); free(aux);

	aux = redondear(1.846904);
	GREATEST_ASSERT_STR_EQ("1.85",	aux); free(aux);

	aux = redondear(10.846904);
	GREATEST_ASSERT_STR_EQ("10.8",	aux); free(aux);

	aux = redondear(100.846904);
	GREATEST_ASSERT_STR_EQ("101",	aux); free(aux);

	aux = redondear(-1.846904);
	GREATEST_ASSERT_STR_EQ("-1.85",	aux); free(aux);

	aux = redondear(-10.846904);
	GREATEST_ASSERT_STR_EQ("-10.8",	aux); free(aux);

	aux = redondear(-100.846904);
	GREATEST_ASSERT_STR_EQ("-101",	aux); free(aux);

	PASS();

}

TEST testIntervaloBiseccion (void) {

	// Cargo array con FCF
	double arrayFCF[N+1];
	for (int i = 0; i < N+1; i++)
		arrayFCF[i] = 71218.447161;

	GREATEST_ASSERT_EQ(FRACASO, biseccion(-945000, arrayFCF, 1, 2));

	GREATEST_ASSERT_IN_RANGE(0.04271, biseccion(-945000, arrayFCF, 0, 2), 0.001);

	PASS();

}

TEST testDerivadaVAN (void) {

	// Cargo array con FCF
	double arrayFCF[N+1];
	for (int i = 0; i < N+1; i++)
		arrayFCF[i] = 71218.447161;

	GREATEST_ASSERT_EQ_FMT((long) FRACASO, (long) vanDerivada(-1, -945000, arrayFCF), "%li");
	GREATEST_ASSERT_IN_RANGE((long) -8270821, (long) vanDerivada(0.04271, -945000, arrayFCF), 100);
	GREATEST_ASSERT_IN_RANGE((long) -7721529, (long) vanDerivada(0.048, -945000, arrayFCF), 100);

	PASS();

}

TEST testIncerteza (void) {

	char * aux;

	aux = incerteza("1000");
	GREATEST_ASSERT_STR_EQ("1", aux); free(aux);

	aux = incerteza("123.1");
	GREATEST_ASSERT_STR_EQ("0.1", aux); free(aux);

	aux = incerteza("0.02");
	GREATEST_ASSERT_STR_EQ("0.01", aux); free(aux);

	aux = incerteza("-10.004");
	GREATEST_ASSERT_STR_EQ("0.001", aux); free(aux);

	PASS();

}

// Main de pruebas unitarias:
GREATEST_MAIN_DEFS();

int correrTests () {

	GREATEST_MAIN_BEGIN();

	RUN_TEST(testAuxiliares);
	RUN_TEST(testCalcularFCF);
	RUN_TEST(testCargarDatos);
	RUN_TEST(testRedondeoNumero);
	RUN_TEST(testIntervaloBiseccion);
	RUN_TEST(testDerivadaVAN);
	RUN_TEST(testIncerteza);

	GREATEST_MAIN_END();

}
