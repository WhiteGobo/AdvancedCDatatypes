#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Time dt1;

	dt1 = Time_parse("13:20:00-05:00");
	if (Decimal_not_equal(dt1.seconds, Decimal_from_int(0))){
		fprintf(stderr, "wrong seconds from '13:20:00-05:00'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
