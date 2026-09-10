#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	int ret = EXIT_SUCCESS;
	Decimal x, y, z, q;
	x = Decimal_parse("1.0", -1);
	y = Decimal_parse("1.0", -1);
	if (!Decimal_equal(x, y)){
		fprintf(stderr, "Failed: 1.0 = 1.0\n");
		ret = EXIT_FAILURE;
	}
	tmpstring = Decimal_serialize(x);
	fprintf(stderr, "print 1.0: %s\n", tmpstring);
	free(tmpstring);
	x = Decimal_parse("1.0", -1);
	y = Decimal_parse("10", -1);
	z = Decimal_parse("11", -1);
	x = Decimal_add(x, y);
	if (!Decimal_equal(x, z)){
		tmpstring = Decimal_serialize(x);
		fprintf(stderr, "Failed: 11 = 1.0 + 10(Got: %s)\n", tmpstring);
		free(tmpstring);
		ret = EXIT_FAILURE;
	}
	exit(ret);
}
