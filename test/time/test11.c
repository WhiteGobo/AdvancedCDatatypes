#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	char* tmp, *tmpstring;
	Time dt1;

	dt1 = Time_parse("13:20:00-05:00");
	if (dt1.minute != 20){
		fprintf(stderr, "wrong minute from '13:20:00-05:00'.");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
