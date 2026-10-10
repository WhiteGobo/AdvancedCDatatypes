#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesDecimal.h"

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	char* tmpstring;
	Number x, y, z;
	Decimal x_d, y_d, z_d;
	int result;
	x = Number_from_decimal(Decimal_parse("-3.5", -1));
	x_d = Number_try_to_decimal(x);
	if(Decimal_equal(DECIMAL_NAN, x_d)){
		fprintf(stderr, "failed 1\n");
		err = EXIT_FAILURE;
	}
	y = Number_new_quotient(5, 2);
	y_d = Number_try_to_decimal(y);
	if(Decimal_equal(DECIMAL_NAN, y_d)){
		fprintf(stderr, "failed 2\n");
		err = EXIT_FAILURE;
	}
	z = Number_new_quotient(5, 3);
	z_d = Number_try_to_decimal(z);
	if(Decimal_not_equal(DECIMAL_NAN, z_d)){
		fprintf(stderr, "failed 3\n");
		err = EXIT_FAILURE;
	}
	exit(err);
}
