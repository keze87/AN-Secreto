#include "greatest.h"
#include "main.h"

TEST testCalcularFCF (void) {

	double factorUso = 0.18 * NUMERODEPADRON / 100000;

	GREATEST_ASSERT_IN_RANGE(7.44652e+07, fcf(30000,factorUso,1.9,250,5000,0.35), 0.1);

	PASS();

}

SUITE (suiteTests) {

	RUN_TEST(testCalcularFCF);

}

// Main de pruebas unitarias:
GREATEST_MAIN_DEFS();

int correrTests () {

	GREATEST_MAIN_BEGIN();

	RUN_SUITE(suiteTests);

	GREATEST_MAIN_END();

}
