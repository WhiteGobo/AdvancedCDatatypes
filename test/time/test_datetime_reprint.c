#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

const char* reprint;

int main(int argc, char *argv[]){
	char* tmpstring;
	DateTime x, y;

	if (argc != 2){
		fprintf(stderr, "Usage: %s datetime\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	reprint = argv[1];

	x = DateTime_parse(reprint);
	tmpstring = DateTime_serialize(x);
	fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	y = DateTime_parse(tmpstring);
	if (DateTime_equal(y, DATETIME_NOTVALID)){
		fprintf(stderr, "reprint isnt valid datetime\n");
		exit(EXIT_FAILURE);
	}
	if (!DateTime_equal(x, y)){
		fprintf(stderr, "Failed to reprint %s. Got instead: %s\n",
				reprint, tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
