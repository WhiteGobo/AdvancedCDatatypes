#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Duration dur1, dur2, dur3, dur4;
	Decimal decimal;
	Number result, compare;

	dur1 = Duration_parse("P4DT8.2S");
	dur2 = Duration_parse("P2DT4.1S");
	decimal = Decimal_parse("2", -1);
	result = Duration_divide_by_Duration(dur1, dur2);
	compare = Number_from_decimal(decimal);
	if (Number_not_equal(result, compare)){
		fprintf(stderr, "Duration_divide_by_Duration failed. "
				"Expected '2' Got '");
		fprintf_Number(stderr, result);
		fprintf(stderr, "'\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
