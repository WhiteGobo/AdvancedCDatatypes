#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1, dur2, dur3, dur4;
	Decimal mult;

	dur1 = Duration_parse("P2Y11M");
	mult = Decimal_parse("1.5", -1);
	dur3 = Duration_divide(dur1, mult);
	dur4 = Duration_parse("P1Y11M");
	if (Duration_not_equal(dur3, dur4)){
		fprintf(stderr, "Duration_divide failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
