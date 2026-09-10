#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1;

	dur1 = Duration_parse("-P5DT12H30M");
	if (Duration_get_minutes(dur1) != -30){
		fprintf(stderr, "wrong minute from '-PDT12H30M'. Got %d\n",
				Duration_get_minutes(dur1));
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
