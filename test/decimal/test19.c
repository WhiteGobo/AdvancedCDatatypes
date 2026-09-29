#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesDecimal.h"

int main(int argc, char *argv[]){
	int ret = EXIT_SUCCESS;
	char* tmpstring;
	Number x, y, z, expect;
	int result;
	x = Number_from_decimal(Decimal_parse("4", -1));
	y = Number_from_decimal(Decimal_parse("2.5", -1));
	z = Number_from_decimal(Decimal_parse("-3", -1));
	if (!Number_less(y, x)){
		fprintf(stderr, "Number_less failed (2.5 < 4)\n");
		ret = EXIT_FAILURE;
	}
	if (!Number_greater(y, z)){
		fprintf(stderr, "Number_greater failed (2.5 > -3)\n");
		ret = EXIT_FAILURE;
	}
	if (!Number_greater_or_equal(x, x)){
		fprintf(stderr, "Number_greater_or_equal failed (4 >= 4)\n");
		ret = EXIT_FAILURE;
	}
	exit(ret);
}
