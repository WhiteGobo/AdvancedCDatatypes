#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1;

	dur1 = Duration_parse("P3DT10H");
	if (Duration_get_hours(dur1) != 10){
		fprintf(stderr, "wrong day from 'P3DT10H'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
