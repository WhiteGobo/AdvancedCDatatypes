#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypeTime.h"

int main(int argc, char *argv[]){
	char* tmpstring;
	int ret = EXIT_SUCCESS;
	Decimal x, y, z, q;
	x = Decimal_parse("05.05", -1);
	y = Decimal_parse("15.15", -1);
	if (!Decimal_less(x, y)){
		fprintf(stderr, "Failed: 5.05 < 15.15\n");
		ret = EXIT_FAILURE;
	}
	exit(ret);
}
