#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1, dur2, dur3, dur4;

	dur1 = Duration_parse("P2Y11M");
	dur2 = Duration_parse("P3Y3M");
	dur3 = Duration_sub(dur1, dur2);
	dur4 = Duration_parse("P4M");
	if (Duration_not_equal(dur3, dur4)){
		tmpstring = Duration_serialize(dur3);
		fprintf(stderr, "Duration_sub failed. Expected 'P4M'. Got '%s'\n", tmpstring);
		free(tmpstring);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
