#include <stdlib.h>
#include <time.h>
#include "AdvancedCDatatypesTime.h"

int main(int argc, char *argv[]){
	fprintf(stderr, "current timezone in minutes %d\n",
			get_local_timezone());
	exit(EXIT_SUCCESS);
}
