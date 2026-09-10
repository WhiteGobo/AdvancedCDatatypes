#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1;

	dur1 = Duration_parse("P3DT10H");
	if (Duration_get_days(dur1) != 3){
		fprintf(stderr, "wrong day from 'P3DT10H'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
