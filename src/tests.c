#include "greatest.h"
#include "main.h"

TEST testCalcularFCF (void) {

	double factorUso = 0.18 * NUMERODEPADRON / 100000;

	GREATEST_ASSERT_IN_RANGE(7.44652e+07, fcf(30000,factorUso,1.9,250,5000,0.35), 0.1);

	PASS();

}

TEST testCargarDatos (void) {

	struct vectorDatos datos = cargarDatos();

	GREATEST_ASSERT_EQ(30000,	datos.potencia);
	GREATEST_ASSERT_EQ(1800,	datos.costoUnitarioPotencia);
	GREATEST_ASSERT_EQ(5000,	datos.costos);

	double factorUso = 0.18 * NUMERODEPADRON / 100000;
	GREATEST_ASSERT_EQ(factorUso,	datos.factorUso);
	GREATEST_ASSERT_EQ(250,			datos.costoPot);
	GREATEST_ASSERT_IN_RANGE(0.35,	datos.ganancias, 0.000001);
	GREATEST_ASSERT_IN_RANGE(1.9,	datos.costoElec, 0.000001);

	PASS();

}

SUITE (suiteTests) {

	RUN_TEST(testCalcularFCF);
	RUN_TEST(testCargarDatos);

}

// Main de pruebas unitarias:
GREATEST_MAIN_DEFS();

int correrTests () {

	GREATEST_MAIN_BEGIN();

	RUN_SUITE(suiteTests);

	GREATEST_MAIN_END();

}
