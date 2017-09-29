#include "greatest.h"
#include "main.h"

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
	GREATEST_ASSERT_IN_RANGE(0.35,	datos.ganancias, 0.000001);
	GREATEST_ASSERT_IN_RANGE(1.9,	datos.costoElec, 0.000001);

	PASS();

}

TEST testRedondeoNumero (void) {

	GREATEST_ASSERT_EQ_FMT(4,largoDeNumeroRedondeado(1),				"%d"); // 1.00
	GREATEST_ASSERT_EQ_FMT(4,largoDeNumeroRedondeado(1.00015456),		"%d"); // 1.00
	GREATEST_ASSERT_EQ_FMT(4,largoDeNumeroRedondeado(1000.1),			"%d"); // 1000
	GREATEST_ASSERT_EQ_FMT(5,largoDeNumeroRedondeado(-0.0006),			"%d"); // -0.00
	GREATEST_ASSERT_EQ_FMT(5,largoDeNumeroRedondeado(71218.4504876),	"%d"); // 71218
	GREATEST_ASSERT_EQ_FMT(5,largoDeNumeroRedondeado(87566.846904),		"%d"); // 87567
	GREATEST_ASSERT_EQ_FMT(4,largoDeNumeroRedondeado(1.846904),			"%d"); // 1.85
	GREATEST_ASSERT_EQ_FMT(4,largoDeNumeroRedondeado(10.846904),		"%d"); // 10.8
	GREATEST_ASSERT_EQ_FMT(3,largoDeNumeroRedondeado(100.846904),		"%d"); // 101
	GREATEST_ASSERT_EQ_FMT(5,largoDeNumeroRedondeado(-10.846904),		"%d"); // -10.8

	PASS();

}

SUITE (suiteTests) {

	RUN_TEST(testCalcularFCF);
	RUN_TEST(testCargarDatos);
	RUN_TEST(testRedondeoNumero);

}

// Main de pruebas unitarias:
GREATEST_MAIN_DEFS();

int correrTests () {

	GREATEST_MAIN_BEGIN();

	RUN_SUITE(suiteTests);

	GREATEST_MAIN_END();

}
