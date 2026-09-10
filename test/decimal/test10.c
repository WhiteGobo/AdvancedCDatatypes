#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	int ret = EXIT_SUCCESS;
	Decimal x, y;
	x = Decimal_parse("1100", -1);
	tmpstring = Decimal_serialize_plain(x);
	fprintf(stderr, "Plain print of '1100': %s\n", tmpstring);
	y = Decimal_parse(tmpstring, -1);
	if (!Decimal_equal(x, y)){
		fprintf(stderr, "Failed to reprint 1100. Got instead: %s\n",
				tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
