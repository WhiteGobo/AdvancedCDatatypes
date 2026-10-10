#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

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
	if(DateTime_equal(x, DATETIME_NOTVALID)){
		fprintf(stderr, "Parsing of %s produced not valid datetime\n", reprint);
		exit(EXIT_FAILURE);
	}
	tmpstring = DateTime_serialize(x);
	if(tmpstring == NULL){
		fprintf(stderr, "Failed to serialize reprint of %s\n", reprint);
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Plain print of '%s': %s\n", reprint, tmpstring);
	y = DateTime_parse(tmpstring);
	free(tmpstring);
	if (DateTime_equal(y, DATETIME_NOTVALID)){
		fprintf(stderr, "reprint isnt valid datetime\n");
		exit(EXIT_FAILURE);
	}
	if (!DateTime_equal(x, y)){
		fprintf(stderr, "Failed to reprint %s. Got instead: ",reprint);
		fprintf_DateTime(stderr, x);
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
