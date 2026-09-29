#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesDecimal.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	Number x, y;
	int result;
	x = Number_from_decimal(Decimal_parse("-3.5", -1));
	y = Number_from_decimal(Decimal_parse("3", -1));
	result = Number_idiv(x, y);
	//tmpstring = Decimal_serialize_plain(result);
	//fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	if (-1 != result){
		fprintf(stderr, "Failed Decimal_idiv (-3.5 idiv 3 = -1). "
				"Got: %d\n", result);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
