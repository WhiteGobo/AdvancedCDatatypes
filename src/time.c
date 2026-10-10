#include "AdvancedCDatatypesTime.h"
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

#define REGTIME "^([0-9]+):([0-9]+):"\
	"(([0-9]+)?(\\.[0-9]+)?)"\
	"(Z)?([-+]?([0-9]+):([0-9]+))?$"
//Needed matches are '(' + 1
#define REGTIME_NEEDED_MATCHES 10

static Decimal Time_to_seconds(Time);

Time Time_parse(const char* input){
	Time ret;
	int err, tmpi;
	regmatch_t matches[REGTIME_NEEDED_MATCHES];
	regex_t reg_datetime;
	err = regcomp(&reg_datetime, REGTIME, REG_EXTENDED);
	if (err != 0){
		return TIME_NOTVALID;
	}
	err = regexec(&reg_datetime, input, REGTIME_NEEDED_MATCHES, matches, 0);
	regfree(&reg_datetime);
	if (err != 0){
		return TIME_NOTVALID;
	}
	ret.hour = strtol(input + matches[1].rm_so, NULL, 10);
	ret.minute = strtol(input + matches[2].rm_so, NULL, 10);
	ret.seconds = Decimal_parse(input + matches[3].rm_so,
			matches[3].rm_eo - matches[3].rm_so);
	if (matches[6].rm_so >= 0){
		ret.offset_minutes = 0;
	} else if (matches[7].rm_so >= 0){
		tmpi = 60 * strtol(input + matches[8].rm_so, NULL, 10);
		tmpi += strtol(input + matches[9].rm_so, NULL, 10);
		switch(input[matches[7].rm_so]){
			case '-':
				ret.offset_minutes = -tmpi;
				break;
			default:
				ret.offset_minutes = tmpi;
		}
	} else {
		ret.offset_minutes = DATETIME_NOOFFSET;
	}
	return ret;
}

char* Time_serialize(Time time){
	char rettmp[50];
	char* ret, *tmpdec, *tmp;
	int tmpi, tmphour, tmpminute;
	if(Time_equal(time, TIME_NOTVALID)){
		return NULL;
	}

	tmpdec = Decimal_serialize_plain(time.seconds);
	sprintf(rettmp, "%02d:%02d:", time.hour, time.minute);
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
	if(time.offset_minutes == DATETIME_NOOFFSET){
	} else if (time.offset_minutes == 0){
		tmp += strlen(tmp);
		sprintf(tmp, "Z");
	} else if (time.offset_minutes > 0){
		tmphour = time.offset_minutes / 60;
		tmpminute = time.offset_minutes % 60;
		tmp += strlen(tmp);
		sprintf(tmp, "+%d:%02d", tmphour, tmpminute);
	} else {
		time.offset_minutes = -time.offset_minutes;
		tmphour = time.offset_minutes / 60;
		tmpminute = time.offset_minutes % 60;
		tmp += strlen(tmp);
		sprintf(tmp, "-%d:%02d", tmphour, tmpminute);
	}
	free(tmpdec);
	ret = malloc(strlen(rettmp) + 1);
	strcpy(ret, rettmp);
	return ret;
}


bool Time_equal(Time x, Time y){
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

bool Time_not_equal(Time x, Time y){
	return !Time_equal(x, y);
}

Duration Time_offset_as_duration(Time x){
	int64_t tmp;
	Duration ret = {
		.sum_months = 0,
	};
	if (x.offset_minutes == DATETIME_NOOFFSET){
		tmp = get_local_timezone();
		if (tmp < 0){
			ret.is_positive = false;
			ret.sum_seconds = Decimal_from_int(-60*tmp);
		} else {
			ret.is_positive = true;
			ret.sum_seconds = Decimal_from_int(60*tmp);
		}
	} else if (x.offset_minutes < 0){
		ret.is_positive = false;
		ret.sum_seconds = Decimal_from_int(x.offset_minutes * (-60));
	} else {
		ret.is_positive = true;
		ret.sum_seconds = Decimal_from_int(x.offset_minutes * 60);
	}
	return ret;
}

Duration Time_sub(Time first, Time second){
	int64_t delta_offset;
	bool with_timeoffset = first.offset_minutes != DATETIME_NOOFFSET;
	if (with_timeoffset != (second.offset_minutes != DATETIME_NOOFFSET)){
		return DURATION_NAN;
	}
	Decimal x = Time_to_seconds(first);
	Decimal y = Time_to_seconds(second);
	Decimal delta = Decimal_sub(x, y);
	if (with_timeoffset){
		delta_offset = 60*(second.offset_minutes - first.offset_minutes);
		if (delta_offset != 0){
			delta = Decimal_add(delta,
					Decimal_from_int(delta_offset));
		}
	}
	return Duration_from_seconds(delta);
}

Time Time_add(Time time, Duration dur){
	Time ret;
	int64_t tmp;
	if (dur.sum_months != 0){
		return TIME_NOTVALID;
	}
	ret.seconds = Decimal_add(time.seconds, dur.sum_seconds);
	tmp = Decimal_floor(ret.seconds) / 60;
	ret.seconds = Decimal_sub(ret.seconds, Decimal_from_int(tmp*60));
	ret.minute = time.minute + tmp;
	tmp = ret.minute / 60;
	ret.minute -= tmp * 60;
	ret.hour = (ret.hour + tmp) % 24;
	return ret;
}

bool Time_less(Time time1, Time time2){
	Duration tmpdur1, tmpdur2;
	Decimal seconds1 = Time_to_seconds(time1);
	Decimal seconds2 = Time_to_seconds(time2);

	tmpdur1 = Time_offset_as_duration(time1);
	if (tmpdur1.is_positive){
		seconds1 = Decimal_sub(seconds1, tmpdur1.sum_seconds);
	} else {
		seconds1 = Decimal_add(seconds1, tmpdur1.sum_seconds);
	}

	tmpdur2 = Time_offset_as_duration(time2);
	if (tmpdur2.is_positive){
		seconds2 = Decimal_sub(seconds2, tmpdur2.sum_seconds);
	} else {
		seconds2 = Decimal_add(seconds2, tmpdur2.sum_seconds);
	}
	return Decimal_less(seconds1, seconds2);
}

bool Time_less_or_equal(Time left, Time right){
	if (Time_equal(left, right)){
		return true;
	}
	return Time_less(left, right);
}

bool Time_greater(Time left, Time right){
	return !Time_less_or_equal(left, right);
}

bool Time_greater_or_equal(Time left, Time right){
	return !Time_less(left, right);
}

static Decimal Time_to_seconds(Time x){
	int64_t tmp = 60*((60*x.hour)+x.minute);
	return Decimal_add(x.seconds, Decimal_from_int(tmp));
}

void fprintf_Time(FILE* f, Time x){
	char* tmpstring = Time_serialize(x);
	if(tmpstring != NULL){
		fprintf(f, "%s", tmpstring);
		free(tmpstring);
	} else {
		fprintf(f, "Time_not_valid");
	}
}
