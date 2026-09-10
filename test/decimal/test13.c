#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

const char* reprint = ".0012";

int main(int argc, char *argv[]){
	char* tmpstring;
	Decimal x, y;
	x = Decimal_parse(reprint, -1);
	tmpstring = Decimal_serialize_plain(x);
	fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	y = Decimal_parse(tmpstring, -1);
	if (!Decimal_equal(x, y)){
		fprintf(stderr, "Failed to reprint %s. Got instead: %s\n",
				reprint, tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
