#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Time dt1;

	dt1 = Time_parse("08:20:00-05:00");
	if (dt1.hour != 8){
		fprintf(stderr, "wrong hour from '08:20:00-05:00'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
