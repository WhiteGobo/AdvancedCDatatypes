#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	int ret = EXIT_SUCCESS;
	Decimal tmpd;
	Quotient x, y, z, w, q;
	x = Decimal_as_quotient(Decimal_parse("15.15", -1));
	y = Decimal_as_quotient(Decimal_parse("05.05", -1));
	z = Decimal_as_quotient(Decimal_parse("0", -1));
	w = Decimal_as_quotient(Decimal_parse("-5.3", -1));
	q = Decimal_as_quotient(Decimal_parse("-15.3", -1));
	if (!Quotient_less(y, x)){
		fprintf(stderr, "Failed: 5.05 < 15.15\n");
		ret = EXIT_FAILURE;
	}
	if (!Quotient_less(z, y)){
		fprintf(stderr, "Failed: 0 < 5.05\n");
		ret = EXIT_FAILURE;
	}
	if (!Quotient_less(w, z)){
		fprintf(stderr, "Failed: -5.3 < 0\n");
		ret = EXIT_FAILURE;
	}
	if (!Quotient_less(w, y)){
		fprintf(stderr, "Failed: -5.3 < 5.05\n");
		ret = EXIT_FAILURE;
	}
	if (!Quotient_less(q, w)){
		fprintf(stderr, "Failed: -15.3 < -5.3\n");
		ret = EXIT_FAILURE;
	}
	if (!Quotient_less_or_equal(y, y)){
		fprintf(stderr, "Failed: 5.05 <= 5.05\n");
		ret = EXIT_FAILURE;
	}
	exit(ret);
}
