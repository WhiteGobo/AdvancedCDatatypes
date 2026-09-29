#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesDecimal.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	Number x, y, z, expect;
	int result;
	x = Number_from_decimal(Decimal_parse("6.05", -1));
	y = Number_from_decimal(Decimal_parse("3.2", -1));
	z = Number_sub(x, y);
	expect = Number_from_decimal(Decimal_parse("2.85", -1));
	if (!Number_equal(z, expect)){
		fprintf(stderr, "Failed Decimal_add (6.05 - 3.2 = 2.85). "
				"Got: ");
		fprintf_Number(stderr, z);
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
