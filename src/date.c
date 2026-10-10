#include "AdvancedCDatatypesTime.h"
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

static Date Date_normalize(Date);

#define REGDATE "^(\\-?[0-9]+)-([0-9]+)-([0-9]+)"\
	"(Z)?([-+]?([0-9]+):([0-9]+))?$"
//Needed matches are '(' + 1
#define REGDATE_NEEDED_MATCHES 8

Date Date_parse(const char* input){
	Date ret;
	int err, tmpi;
	regmatch_t matches[REGDATE_NEEDED_MATCHES];
	regex_t reg_datetime;
	err = regcomp(&reg_datetime, REGDATE, REG_EXTENDED);
	if (err != 0){
		return DATE_NOTVALID;
	}
	err = regexec(&reg_datetime, input, REGDATE_NEEDED_MATCHES, matches, 0);
	regfree(&reg_datetime);
	if (err != 0){
		return DATE_NOTVALID;
	}
	ret.year = strtol(input + matches[1].rm_so, NULL, 10);
	ret.month = strtol(input + matches[2].rm_so, NULL, 10);
	ret.day = strtol(input + matches[3].rm_so, NULL, 10);
	if (matches[4].rm_so >= 0){
		ret.offset_minutes = 0;
	} else if (matches[5].rm_so >= 0){
		tmpi = 60 * strtol(input + matches[6].rm_so, NULL, 10);
		tmpi += strtol(input + matches[7].rm_so, NULL, 10);
		switch(input[matches[5].rm_so]){
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

char* Date_serialize(Date date){
	char rettmp[50];
	char* ret, *tmp;
	int tmpi, tmphour, tmpminute;
	if(Date_equal(date, DATE_NOTVALID)){
		return NULL;
	}

	sprintf(rettmp, "%d-%d-%d", date.year, date.month, date.day);
	tmp = rettmp + strlen(rettmp);
	if(date.offset_minutes == DATETIME_NOOFFSET){
	} else if (date.offset_minutes == 0){
		tmp += strlen(tmp);
		sprintf(tmp, "Z");
	} else if (date.offset_minutes > 0){
		tmphour = date.offset_minutes / 60;
		tmpminute = date.offset_minutes % 60;
		tmp += strlen(tmp);
		sprintf(tmp, "+%d:%02d", tmphour, tmpminute);
	} else {
		date.offset_minutes = -date.offset_minutes;
		tmphour = date.offset_minutes / 60;
		tmpminute = date.offset_minutes % 60;
		tmp += strlen(tmp);
		sprintf(tmp, "-%d:%02d", tmphour, tmpminute);
	}
	ret = malloc(strlen(rettmp) + 1);
	strcpy(ret, rettmp);
	return ret;
}


Date Date_new(int64_t year, int64_t month, int64_t day, int32_t offset_minutes){
	Date ret = {
		.year = year,
		.month = month,
		.day = day,
		.offset_minutes = offset_minutes,
	};
	return Date_normalize(ret);
}


bool Date_equal(Date x, Date y){
	if(x.year != y.year){
		return false;
	}
	if(x.month != y.month){
		return false;
	}
	if(x.day != y.day){
		return false;
	}
	if(x.offset_minutes != y.offset_minutes){
		return false;
	}
	return true;
}
bool Date_not_equal(Date x, Date y){
	return !Date_equal(x, y);
}


#define LEAPYEAR(dts) (((dts.year % 100 != 0) || (dts.year % 400 == 0)) && (dts.year % 4 == 0))
#define MONTH31(dts) ((dts.month == 1) || (dts.month == 3) || (dts.month == 5) || (dts.month == 7) || (dts.month == 8) || (dts.month == 10) || (dts.month == 12))
#define MONTH29(dts) ((dts.month == 2) && LEAPYEAR(dts))
#define MONTH28(dts) ((dts.month == 2) && !LEAPYEAR(dts))
#define MONTH30(dts) ((dts.month == 4) || (dts.month == 6) || (dts.month == 9) || (dts.month == 11))


static Date Date_normalize(Date date){
	bool done_something = true;
	while (done_something){
		if (date.month < 1){
			date.year -= 1;
			date.month += 12;
		} else if (date.month > 12){
			date.year += 1;
			date.month -= 12;
		} else if (date.day < 1){
			date.month -= 1;
			if (date.month < 1){
				date.year -= 1;
				date.month += 12;
			}
			if (MONTH28(date)){
				date.day += 28;
			} else if (MONTH29(date)) {
				date.day += 29;
			} else if (MONTH30(date)) {
				date.day += 30;
			} else {
				date.day += 31;
			}
		} else if (date.day > 28 && MONTH28(date)){
			date.month += 1;
			date.day -= 28;
		} else if (date.day > 29 && MONTH29(date)){
			date.month += 1;
			date.day -= 29;
		} else if (date.day > 30 && MONTH30(date)){
			date.month += 1;
			date.day -= 30;
		} else if (date.day > 31){
			date.month += 1;
			date.day -= 31;
		} else {
			done_something = false;
		}
	}
	return date;
}

Duration Date_offset_as_duration(Date x){
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

Date Date_add(Date date, Duration dur){
	date.month += Duration_get_months(dur);
	date.year += Duration_get_years(dur);
	date = Date_normalize(date);
	date.day += Duration_get_days(dur);
	return Date_normalize(date);
}

static int64_t increase_year(Date*);
static int64_t decrease_year(Date*);
static int64_t increase_month(Date*);
static int64_t decrease_month(Date*);

Duration Date_sub(Date first, Date second){
	int64_t delta_minutes;
	int64_t delta_day = 0;
	while (first.year < second.year){
		delta_day -= increase_year(&first);
		fprintf(stderr, "increase year %d\n", delta_day);
	}
	while (first.year > second.year){
		delta_day += decrease_year(&first);
		fprintf(stderr, "decrease year %d\n", delta_day);
	}
	while (first.month < second.month){
		delta_day -= increase_month(&first);
		fprintf(stderr, "increase month %d\n", delta_day);
	}
	while (first.month > second.month){
		delta_day += decrease_month(&first);
		fprintf(stderr, "decrease month %d\n", delta_day);
	}
	delta_day += first.day - second.day;
		fprintf(stderr, "change_days %d\n", delta_day);
	delta_minutes = delta_day*24*60;
	return Duration_from_minutes(delta_minutes);
}

static int64_t increase_year(Date* x){
	int64_t tmp;
	if (x->month <= 2){
		tmp = x->year;
	} else {
		tmp = x->year + 1;
	}
	x->year += 1;
	if(((tmp % 100 != 0) || (tmp % 400 == 0)) && (tmp % 4 == 0)){
		return 364;
	}
	return 365;
}

#define IS_LEAPYEAR(y) (((y % 100 != 0) || (y % 400 == 0)) && (y % 4 == 0))
static int64_t decrease_year(Date* x){
	int64_t tmp;
	if (x->month <= 2){
		tmp = x->year - 1;
	} else {
		tmp = x->year;
	}
	x->year -= 1;
	if (IS_LEAPYEAR(tmp)){
		return 366;
	}
	return 365;
}

static int64_t increase_month(Date* x){
	int64_t tmp = x->month;
	x->month += 1;
	switch(tmp){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 2:
			if (IS_LEAPYEAR(x->year)){
				return 29;
			} else {
				return 28;
			}
		default:
			return 30;
	}
}

static int64_t decrease_month(Date* x){
	x->month -= 1;
	switch(x->month){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 2:
			if (IS_LEAPYEAR(x->year)){
				return 29;
			} else {
				return 28;
			}
		default:
			return 30;
	}
}

bool Date_less(Date first, Date second){
	if (first.year < second.year){
		return true;
	}
	if (first.month < second.month){
		return true;
	}
	return first.day < second.day;
}

bool Date_less_or_equal(Date x, Date y){
	if (Date_equal(x, y)){
		return true;
	}
	return Date_less(x, y);
}

bool Date_greater(Date x, Date y){
	if (Date_equal(x, y)){
		return false;
	}
	return !Date_less(x, y);
}

bool Date_greater_or_equal(Date x, Date y){
	return !Date_less(x, y);
}

void fprintf_Date(FILE* f, Date x){
	char* tmpstring = Date_serialize(x);
	if(tmpstring != NULL){
		fprintf(f, "%s", tmpstring);
		free(tmpstring);
	} else {
		fprintf(f, "Date_not_valid");
	}
}
