#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	DateTime dt1, dt2, dt3;
	Duration dur1;

	dt1 = DateTime_parse("2000-12-13T00:11:11.3");
	dur1 = Duration_parse("-P1Y1M1DT1H1M1.1S");
	fprintf(stderr, "To '2000-12-13T00:11:11.3' add '-P1Y1M1DT1H1M1.1S'\n");
	dt2 = DateTime_add(dt1, dur1);
	tmpstring = DateTime_serialize(dt2);
	fprintf(stderr, "Expect '1999-11-11T23:10:10.2'; got %s\n", tmpstring);
	free(tmpstring);
	if(DateTime_equal(dt2, DATETIME_NOTVALID)){
		fprintf(stderr, "Add produced non valid DateTime\n");
		exit(EXIT_FAILURE);
	}
	if (DateTime_equal(dt2, dt3)){
		fprintf(stderr, "Add failed to produced correct datetime\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
