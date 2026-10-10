#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

const char* reprint;

int main(int argc, char *argv[]){
	char* tmpstring;
	Decimal x, y;

	if (argc != 2){
		fprintf(stderr, "Usage: %s decimal\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	reprint = argv[1];

	x = Decimal_parse(reprint, -1);
	tmpstring = Decimal_serialize(x);
	fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	y = Decimal_parse(tmpstring, -1);
	free(tmpstring);
	if (Decimal_equal(y, DECIMAL_NAN)){
		fprintf(stderr, "reprint isnt valid decimal\n");
		exit(EXIT_FAILURE);
	}
	if (!Decimal_equal(x, y)){
		fprintf(stderr, "Failed to reprint %s. Got instead: \n",
				reprint );
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
