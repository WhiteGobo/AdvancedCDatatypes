#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesDecimal.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	Number x, y, z, expect;
	int result;
	x = Number_from_decimal(Decimal_parse("4", -1));
	y = Number_from_decimal(Decimal_parse("2.5", -1));
	z = Number_mult(x, y);
	expect = Number_from_decimal(Decimal_parse("10", -1));
	if (!Number_equal(z, expect)){
		fprintf(stderr, "Failed Decimal_mult (4 * 2.5 = 10). "
				"Got: ");
		fprintf_Number(stderr, z);
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
