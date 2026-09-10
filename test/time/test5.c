#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	DateTime dt1, dt2, dt3;
	Duration dur1;

	dt1 = DateTime_parse("1999-05-31T13:20:00-05:00");
	if (dt1.minute != 20){
		fprintf(stderr, "wrong minute from '1999-05-31T13:20:00-05:00'\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
