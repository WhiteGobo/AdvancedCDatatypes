#include <stdint.h>
#include <time.h>
#include "AdvancedCDatatypesTime.h"

int64_t get_local_timezone(){
	time_t now = time(NULL);
	struct tm local_time;

	localtime_r(&now, &local_time);
	return local_time.tm_gmtoff / 60;
}
