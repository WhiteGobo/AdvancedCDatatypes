#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

const char* reprint;

int main(int argc, char *argv[]){
	char* tmpstring;
	Date x, y;

	if (argc != 2){
		fprintf(stderr, "Usage: %s date\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	reprint = argv[1];

	x = Date_parse(reprint);
	tmpstring = Date_serialize(x);
	fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	y = Date_parse(tmpstring);
	if (Date_equal(y, DATE_NOTVALID)){
		fprintf(stderr, "reprint isnt valid datetime\n");
		exit(EXIT_FAILURE);
	}
	if (!Date_equal(x, y)){
		fprintf(stderr, "Failed to reprint %s. Got instead: %s\n",
				reprint, tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
