#include <stdlib.h>
#include <stdio.h>
#include "AdvancedCDatatypesDecimal.h"

int main(int argc, char *argv[]){
	int err = EXIT_SUCCESS;
	if(!NAN_parse("NAN")){
		fprintf(stderr, "ERROR NAN_parse couldnt recognise 'NAN'\n");
		err = EXIT_FAILURE;
	}
	if(NAN_parse("foo")){
		fprintf(stderr, "ERROR NAN_parse failed 'foo'\n");
		err = EXIT_FAILURE;
	}
	exit(err);
}
