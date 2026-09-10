#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	int ret = EXIT_SUCCESS;
	Decimal x, y, z, q;
	x = Decimal_parse("15.15", -1);
	y = Decimal_parse("05.05", -1);
	z = Decimal_add(x, y);
	q = Decimal_parse("20.20", -1);
	if (!Decimal_equal(z, q)){
		fprintf(stderr, "Failed: 20.20 = 15.15 + 5.05\n");
		ret = EXIT_FAILURE;
	}
	tmpstring = Decimal_serialize(z);
	fprintf(stderr, "print 15.15 + 5.05: %s\n", tmpstring);
	free(tmpstring);
	exit(ret);
}
