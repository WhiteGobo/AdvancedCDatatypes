#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1, dur2, dur3, dur4;

	dur1 = Duration_parse("P2Y11M");
	dur2 = Duration_parse("P3Y3M");
	dur3 = Duration_add(dur1, dur2);
	dur4 = Duration_parse("P6Y2M");
	if (Duration_not_equal(dur3, dur4)){
		fprintf(stderr, "Duration_add failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
