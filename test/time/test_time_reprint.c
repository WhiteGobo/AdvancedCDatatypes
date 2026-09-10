#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

const char* reprint;

int main(int argc, char *argv[]){
	char* tmpstring;
	Time x, y;

	if (argc != 2){
		fprintf(stderr, "Usage: %s time\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	reprint = argv[1];

	x = Time_parse(reprint);
	tmpstring = Time_serialize(x);
	fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	y = Time_parse(tmpstring);
	if (Time_equal(y, TIME_NOTVALID)){
		fprintf(stderr, "reprint isnt valid time\n");
		exit(EXIT_FAILURE);
	}
	if (!Time_equal(x, y)){
		fprintf(stderr, "Failed to reprint %s. Got instead: %s\n",
				reprint, tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
