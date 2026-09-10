#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	int ret = EXIT_SUCCESS;
	Decimal x, y, z, q;
	fprintf(stderr, "Generate Decimal with Decimal_from_int\n");
	x = Decimal_from_int(20);
	y = Decimal_parse("20", -1);
	if (!Decimal_equal(x, y)){
		fprintf(stderr, "Failed: \"20\" = 20\n");
		ret = EXIT_FAILURE;
	}
	tmpstring = Decimal_serialize(x);
	fprintf(stderr, "print 'Decimal_from_int(20)': %s\n", tmpstring);
	free(tmpstring);
	exit(ret);
}
