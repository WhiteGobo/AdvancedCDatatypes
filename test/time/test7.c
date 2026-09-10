#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Date dt1;

	dt1 = Date_parse("1999-12-31");
	if (dt1.year != 1999){
		fprintf(stderr, "wrong year from '1999-12-31'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
