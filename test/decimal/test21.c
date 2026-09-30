#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesDecimal.h"

int main(int argc, char *argv[]){
	int ret = EXIT_SUCCESS;
	char* tmpstring;
	Number x, y, z, w;
	int result;
	x = Number_from_decimal(Decimal_parse("4", -1));
	y = Number_from_decimal(Decimal_parse("2.5001", -1));
	z = Number_from_decimal(Decimal_parse("-2.5101", -1));
	w = Number_from_decimal(Decimal_parse("-2.50", -1));
	fprintf_Number(stderr, x);
	if (4 != Number_round(x)){
		fprintf(stderr, "Number_round(4) failed: %d\n", Number_round(x));
		ret = EXIT_FAILURE;
	}
	if (3 != Number_round(y)){
		fprintf(stderr, "Number_round(2.5) failed: %d\n",
				Number_round(y));
		ret = EXIT_FAILURE;
	}
	if (-3 != Number_round(z)){
		fprintf(stderr, "Number_round(-2.51) failed: %d\n",
				Number_round(z));
		ret = EXIT_FAILURE;
	}
	if (-2 != Number_round(w)){
		fprintf(stderr, "Number_round(-2.5) failed: %d\n",
				Number_round(w));
		ret = EXIT_FAILURE;
	}
	exit(ret);
}
