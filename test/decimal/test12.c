#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

const char* reprint = ".12";

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	char* tmpstring;
	Decimal x, y;
	x = Decimal_parse(reprint, -1);
	tmpstring = Decimal_serialize_plain(x);
	y = Decimal_parse(tmpstring, -1);
	if (!Decimal_equal(x, y)){
		fprintf(stderr, "Failed to reprint %s. Got instead: %s\n",
				reprint, tmpstring);
		err = EXIT_FAILURE;
	} else {
		err = EXIT_SUCCESS;
	}
	free(tmpstring);
	exit(err);
}
