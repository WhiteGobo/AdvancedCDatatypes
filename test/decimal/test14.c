#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesDecimal.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	Number x, y, result, expect;
	x = Number_from_decimal(Decimal_parse("5", -1));
	y = Number_from_decimal(Decimal_parse("3", -1));
	expect = Number_from_decimal(Decimal_parse("2", -1));
	result = Number_mod(x, y);
	//tmpstring = Decimal_serialize_plain(result);
	//fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	if (!Number_equal(result, expect)){
		fprintf(stderr, "Failed Decimal_mod (5 % 3 = 2). Got: ");
		fprintf_Number(stderr, result);
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
