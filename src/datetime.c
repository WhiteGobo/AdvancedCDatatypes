#include "AdvancedCDatatypesTime.h"
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>


static const Duration durzero = {
	.is_positive = true,
	.sum_months = 0,
	.sum_seconds = 0,
};

static DateTime DateTime_normalize(DateTime);


#define REGDATETIME "^(\\-?[0-9]+)-([0-9]+)-([0-9]+)"\
	"T([0-9]+):([0-9]+):"\
	"(([0-9]+)?(\\.[0-9]+)?)"\
	"(Z)?([-+]?([0-9]+):([0-9]+))?$"

DateTime DateTime_parse(const char* input){
	DateTime ret;
	int err, tmpi;
	regmatch_t matches[15];
	regex_t reg_datetime;
	err = regcomp(&reg_datetime, REGDATETIME, REG_EXTENDED);
	if (err != 0){
		return DATETIME_NOTVALID;
	}
	err = regexec(&reg_datetime, input, 15, matches, 0);
	if (err != 0){
		return DATETIME_NOTVALID;
	}
	ret.year = strtol(input + matches[1].rm_so, NULL, 10);
	ret.month = strtol(input + matches[2].rm_so, NULL, 10);
	ret.day = strtol(input + matches[3].rm_so, NULL, 10);
	ret.hour = strtol(input + matches[4].rm_so, NULL, 10);
	ret.minute = strtol(input + matches[5].rm_so, NULL, 10);
	ret.seconds = Decimal_parse(input + matches[6].rm_so,
			matches[6].rm_eo - matches[6].rm_so);
	if (matches[9].rm_so >= 0){
		ret.offset_minutes = 0;
	} else if (matches[10].rm_so >= 0){
		tmpi = 60 * strtol(input + matches[11].rm_so, NULL, 10);
		tmpi += strtol(input + matches[13].rm_so, NULL, 10);
		switch(input[matches[10].rm_so]){
			case '-':
				ret.offset_minutes = -tmpi;
				break;
			default:
				ret.offset_minutes = tmpi;
		}
	} else {
		ret.offset_minutes = DATETIME_NOOFFSET;
	}
	return DateTime_normalize(ret);
}

char* DateTime_serialize(DateTime dt){
	char rettmp[50];
	char* ret, *tmpdec, *tmp;
	int tmpi, tmphour, tmpminute;
	if(DateTime_equal(dt, DATETIME_NOTVALID)){
		return NULL;
	}

	tmpdec = Decimal_serialize_plain(dt.seconds);
	sprintf(rettmp, "%d-%d-%dT%02d:%02d:",
			dt.year, dt.month, dt.day, dt.hour, dt.minute);
	tmp = rettmp + strlen(rettmp);
	//seconds can only have values from 0 to <60
	if (strlen(tmpdec) == 1){ //single integer
		sprintf(tmp, "0%s", tmpdec);
	} else if (tmpdec[0] == '.'){
		sprintf(tmp, "00%s", tmpdec);
	} else if (tmpdec[1] == '.'){
		sprintf(tmp, "0%s", tmpdec);
	} else {
		sprintf(tmp, "%s", tmpdec);
	}
	if(dt.offset_minutes == DATETIME_NOOFFSET){
	} else if (dt.offset_minutes == 0){
		tmp += strlen(tmp);
		sprintf(tmp, "Z");
	} else if (dt.offset_minutes > 0){
		tmphour = dt.offset_minutes / 60;
		tmpminute = dt.offset_minutes % 60;
		tmp += strlen(tmp);
		sprintf(tmp, "+%d:%02d", tmphour, tmpminute);
	} else {
		dt.offset_minutes = -dt.offset_minutes;
		tmphour = dt.offset_minutes / 60;
		tmpminute = dt.offset_minutes % 60;
		tmp += strlen(tmp);
		sprintf(tmp, "-%d:%02d", tmphour, tmpminute);
	}
	free(tmpdec);
	ret = malloc(strlen(rettmp) + 1);
	strcpy(ret, rettmp);
	return ret;
}

DateTime DateTime_add(DateTime dt, Duration dur){
	if (
			DateTime_equal(dt, DATETIME_NOTVALID)
			|| Duration_equal(dur, DURATION_NAN)
	) {
		return DATETIME_NOTVALID;
	}
	if (!dur.is_positive){
		Decimal tmp = Decimal_from_int(-1);
		dur.sum_seconds = Decimal_mul(dur.sum_seconds, tmp);
		dur.sum_months = -dur.sum_months;
	}
	dt.seconds = Decimal_add(dt.seconds, dur.sum_seconds);
	dt.month = dt.month + dur.sum_months;
	return DateTime_normalize(dt);
}

bool DateTime_not_equal(DateTime x, DateTime y){
	return !DateTime_equal(x, y);
}

bool DateTime_equal(DateTime x, DateTime y){
	if(x.year != y.year){
		return false;
	}
	if(x.month != y.month){
		return false;
	}
	if(x.day != y.day){
		return false;
	}
	if(x.hour != y.hour){
		return false;
	}
	if(x.minute != y.minute){
		return false;
	}
	if(Decimal_not_equal(x.seconds, y.seconds)){
		return false;
	}
	if(x.offset_minutes != y.offset_minutes){
		return false;
	}
	return true;
}

static DateTime DateTime_normalize(DateTime dt){
	int tmpi;
	Decimal tmpd;
	Decimal sixty = Decimal_from_int(60);
	Date tmpdate;
	tmpi = Decimal_floor(dt.seconds) / 60;
	if (tmpi < 0) tmpi -= 1;
	dt.minute += tmpi;
	tmpd = Decimal_from_int(tmpi * -60);
	dt.seconds = Decimal_add(dt.seconds, tmpd);

	tmpi = dt.minute / 60;
	if (tmpi < 0) tmpi -= 1;
	dt.minute -= tmpi * 60;
	dt.hour += tmpi;

	tmpi = dt.hour / 24;
	if (tmpi < 0) tmpi -= 1;
	dt.hour -= tmpi * 24;
	dt.day += tmpi;

	tmpdate = Date_new(dt.year, dt.month, dt.day, dt.offset_minutes);
	dt.year = tmpdate.year;
	dt.month = tmpdate.month;
	dt.day = tmpdate.day;
	return dt;
}

Duration DateTime_offset_as_duration(DateTime x){
	Duration ret = {
		.sum_months = 0,
	};
	if (x.offset_minutes < 0){
		ret.is_positive = false;
		ret.sum_seconds = Decimal_from_int(x.offset_minutes * (-60));
	} else {
		ret.is_positive = true;
		ret.sum_seconds = Decimal_from_int(x.offset_minutes * 60);
	}
	return ret;
}

bool DateTime_is_DateTimeStamp(DateTime x){ 
	return x.offset_minutes != DATETIME_NOOFFSET;
}


Duration DateTime_sub(DateTime first, DateTime second){
	Decimal dzero = Decimal_from_int(0);
	Duration ret, dur1, dur2, delta_time;
	Time time1 = {
		.hour = first.hour,
		.minute = first.minute,
		.offset_minutes = first.offset_minutes,
	}, time2 = {
		.hour = second.hour,
		.minute = second.minute,
		.offset_minutes = second.offset_minutes,
	};
	cpy_decimal(time1.seconds, first.seconds);
	cpy_decimal(time2.seconds, second.seconds);
	Date date1 = {
		.year = first.year,
		.month = first.month,
		.day = first.day,
	}, date2 = {
		.year = second.year,
		.month = second.month,
		.day = second.day,
	};
	dur1 = Date_sub(date1, date2);
	dur2 = Time_sub(time1, time2);
	if (Duration_equal(dur1, durzero)){
		return dur2;
	}
	Duration one_day = Duration_from_minutes(24*60);
	if (dur1.is_positive && !dur2.is_positive){
		first.day -= 1;
		first = DateTime_normalize(first);
		date1.year = first.year;
		date1.month = first.month;
		date1.day = first.day;
		dur1 = Date_sub(date1, date2);
		dur2 = Duration_add(dur2, one_day);
	} else if (!dur1.is_positive && dur2.is_positive){
		first.day += 1;
		first = DateTime_normalize(first);
		date1.year = first.year;
		date1.month = first.month;
		date1.day = first.day;
		dur1 = Date_sub(date1, date2);
		dur2 = Duration_sub(dur2, one_day);
	}
	return Duration_add(dur1, dur2);
}


bool DateTime_less(DateTime first, DateTime second){
	if (first.year < second.year){
		return true;
	} else if (first.year > second.year){
		return false;
	}
	if (first.month < second.month){
		return true;
	} else if (first.month > second.month){
		return false;
	}
	if (first.day+1 < second.day){
		return true;
	} else if (first.day-1 > second.day){
		return false;
	}
	Duration diff = DateTime_sub(first, second);
	fprintf_Duration(stderr, diff);
	fprintf(stderr, " < 0?\n");
	bool q = Duration_less(diff, durzero);
	if (q){
		fprintf(stderr, "true\n");
	} else {
		fprintf(stderr, "false\n");
	}
	return q;
}


bool DateTime_less_or_equal(DateTime x, DateTime y){
	if (DateTime_equal(x, y)){
		return true;
	}
	return DateTime_less(x, y);
}
bool DateTime_greater(DateTime x, DateTime y){
	if (DateTime_equal(x, y)){
		return false;
	}
	return !DateTime_less(x, y);
}

bool DateTime_greater_or_equal(DateTime x, DateTime y){
	return !DateTime_less(x, y);
}
