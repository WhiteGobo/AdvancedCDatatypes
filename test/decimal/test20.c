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
	z = Number_new_quotient(5, 2);
	if (!Number_is_int(x)){
		fprintf(stderr, "Number_is_int failed to identify decimal 4.\n");
		ret = EXIT_FAILURE;
	}
	if (Number_is_int(y)){
		fprintf(stderr, "Number_is_int failed to identify "
				"decimal 2.5.\n");
		ret = EXIT_FAILURE;
	}
	if (Number_is_int(z)){
		fprintf(stderr, "Number_is_int failed to identify "
				"quotient 5/2.\n");
		ret = EXIT_FAILURE;
	}
	exit(ret);
}
