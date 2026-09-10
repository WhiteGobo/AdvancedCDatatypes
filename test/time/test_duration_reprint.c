#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

const char* reprint;

int main(int argc, char *argv[]){
	char* tmpstring;
	Duration x, y;

	if (argc != 2){
		fprintf(stderr, "Usage: %s duration\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	reprint = argv[1];

	x = Duration_parse(reprint);
	if (Duration_equal(x, DURATION_NAN)){
		fprintf(stderr, "Parsing '%s' got DURATION_NAN\n", reprint);
		exit(EXIT_FAILURE);
	}
	tmpstring = Duration_serialize(x);
	fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	y = Duration_parse(tmpstring);
	if (Duration_equal(y, DURATION_NAN)){
		fprintf(stderr, "reprint isnt valid duration\n");
		exit(EXIT_FAILURE);
	}
	if (!Duration_equal(x, y)){
		fprintf(stderr, "Failed to reprint %s. Got instead: %s\n",
				reprint, tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
