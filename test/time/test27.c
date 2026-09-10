#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1, dur2, dur3, dur4;
	Decimal mult;

	dur1 = Duration_parse("P2Y11M");
	mult = Decimal_parse("2.3", -1);
	dur3 = Duration_mult(dur1, mult);
	dur4 = Duration_parse("P6Y9M");
	if (Duration_not_equal(dur3, dur4)){
		tmpstring = Duration_serialize(dur3);
		fprintf(stderr, "Duration_mult failed. Expected 'P6Y9M' Got: '%s'\n", tmpstring);
		free(tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
