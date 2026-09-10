#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Date dt1;

	dt1 = Date_parse("1999-05-31");
	if (dt1.day != 31){
		fprintf(stderr, "wrong day from '1999-05-31'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
