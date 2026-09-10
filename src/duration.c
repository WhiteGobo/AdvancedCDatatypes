#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "AdvancedCDatatypesTime.h"
#include <string.h>
#include <math.h>


static const Decimal dzero = {
	.exponent = 0,
	.significand = 0,
};

#define REGDURATION "^(-)?P"\
	"([0-9]+Y)?"\
	"([0-9]+M)?"\
	"([0-9]+D)?"\
	"(T"\
	"([0-9]+H)?"\
	"([0-9]+M)?"\
	"(([0-9]+)?(.[0-9]+)?S)?"\
	")?$"

Duration Duration_parse(const char* input){
	uint64_t tmp;
	Decimal tmp_decimal;
	Duration ret = {
		.sum_months = 0,
		.sum_seconds = 0,
	};
	int err;
	regmatch_t matches[15];
	regex_t reg_duration;
	err = regcomp(&reg_duration, REGDURATION, REG_EXTENDED);
	if (err != 0){
		return DURATION_NAN;
	}
	err = regexec(&reg_duration, input, 15, matches, 0);
	if (err != 0){
		return DURATION_NAN;
	}
	if (matches[1].rm_so >= 0){
		ret.is_positive = false;
	} else {
		ret.is_positive = true;
	}
	tmp = 0;
	if (matches[2].rm_so >= 0){
		tmp = 12*strtol(input + matches[2].rm_so, NULL, 10);
	}
	if (matches[3].rm_so >= 0){
		tmp += strtol(input + matches[3].rm_so, NULL, 10);
	}
	ret.sum_months = tmp;
	tmp = 0;
	if (matches[4].rm_so >= 0){
		tmp = 24*60*60*strtol(input + matches[4].rm_so, NULL, 10);
	}
	if (matches[6].rm_so >= 0){
		tmp += 60*60*strtol(input + matches[6].rm_so, NULL, 10);
	}
	if (matches[7].rm_so >= 0){
		tmp += 60*strtol(input + matches[7].rm_so, NULL, 10);
	}
	ret.sum_seconds = Decimal_from_int(tmp);
	if (matches[8].rm_so >= 0){
		tmp_decimal = Decimal_parse(input + matches[8].rm_so,
					matches[8].rm_eo - matches[8].rm_so -1);
		ret.sum_seconds = Decimal_add(ret.sum_seconds, tmp_decimal);
	}
	if (Decimal_equal(ret.sum_seconds, DECIMAL_NAN)){
		return DURATION_NAN;
	}
	return ret;
}


bool Duration_equal(Duration x, Duration y){
	if (x.sum_months != y.sum_months){
		return false;
	}
	return Decimal_equal(x.sum_seconds, y.sum_seconds);
}
bool Duration_not_equal(Duration x, Duration y){
	return !Duration_equal(x, y);
}


static char* Duration_serialize_full(Duration dur, bool prefer_year_month);

char* Duration_serialize(Duration dur){
	return Duration_serialize_full(dur, false);
}

char* Duration_serialize_prefer_YearMonth(Duration dur){
	return Duration_serialize_full(dur, true);
}

static char* Duration_serialize_full(Duration dur, bool prefer_year_month){
	uint64_t tmp, hour, minutes;
	Decimal seconds;
	char* tmpstr, *endptr;
	char* ret, tmpret[100];
	if (Duration_equal(dur, DURATION_NAN)){
		return NULL;
	}
	if (dur.is_positive){
		sprintf(tmpret, "P");
		endptr = tmpret + 1;
	} else {
		sprintf(tmpret, "-P");
		endptr = tmpret + 2;
	}
	tmp = dur.sum_months / 12;
	if (tmp > 0){
		sprintf(endptr, "%dY", tmp);
		endptr += strlen(endptr);
	}
	tmp = dur.sum_months % 12;
	if (tmp > 0){
		sprintf(endptr, "%dM", tmp);
		endptr += strlen(endptr);
	}
	if (Decimal_equal(dzero, dur.sum_seconds)){
		if (dur.sum_months != 0){
			ret = malloc(strlen(tmpret) + 1);
			strcpy(ret, tmpret);
		} else if (prefer_year_month) {
			ret = malloc(4);
			sprintf(ret, "P0M");
		} else {
			ret = malloc(5);
			sprintf(ret, "PT0S");
		}
		return ret;
	}
	tmp = Decimal_floor(dur.sum_seconds) / 60;
	seconds = Decimal_sub(dur.sum_seconds, Decimal_from_int(tmp * 60));
	minutes = tmp % 60;
	tmp = tmp / 60;
	hour = tmp % 24;
	tmp = tmp / 24;
	if (tmp > 0){
		sprintf(endptr, "%dD", tmp);
		endptr += strlen(endptr);
	}
	if (Decimal_equal(dzero, seconds) && minutes == 0 && hour == 0){
		ret = malloc(strlen(tmpret) + 1);
		strcpy(ret, tmpret);
		return ret;
	}
	endptr[0] = 'T';
	endptr++;
	if (hour != 0){
		sprintf(endptr, "%dH", hour);
		endptr += strlen(endptr);
	}
	if (minutes != 0){
		sprintf(endptr, "%dM", minutes);
		endptr += strlen(endptr);
	}
	if (Decimal_not_equal(dzero, seconds)){
		tmpstr = Decimal_serialize(seconds);
		sprintf(endptr, "%sS", tmpstr);
		free(tmpstr);
	}

	ret = malloc(strlen(tmpret) + 1);
	strcpy(ret, tmpret);
	return ret;
}

Duration Duration_from_minutes(int64_t x){
	Duration ret;
	if (x < 0){
		ret.is_positive = false;
		ret.sum_months = 0;
		ret.sum_seconds = Decimal_from_int(-60 * x);
	} else {
		ret.is_positive = true;
		ret.sum_months = 0;
		ret.sum_seconds = Decimal_from_int(60 * x);
	}
	return ret;
}

Duration Duration_from_seconds(Decimal x){
	Duration ret;
	if (Decimal_less(x, dzero)){
		ret.is_positive = false;
		ret.sum_months = 0;
		ret.sum_seconds = Decimal_neg(x);
	} else {
		ret.is_positive = true;
		ret.sum_months = 0;
		ret.sum_seconds = x;
	}
	return ret;
}

Duration Duration_add(Duration x, Duration y){
	if (x.is_positive == y.is_positive){
		x.sum_months += y.sum_months;
		x.sum_seconds = Decimal_add(x.sum_seconds, y.sum_seconds);
	} else {
		x.sum_months -= y.sum_months;
		x.sum_seconds = Decimal_sub(x.sum_seconds, y.sum_seconds);
		if (x.sum_months < 0 || Decimal_less(x.sum_seconds, dzero)){
			if (x.sum_months > 0 || Decimal_greater(x.sum_seconds, dzero)){
				return DURATION_NAN;
			}
			x.sum_months = -x.sum_months;
			x.sum_seconds = Decimal_neg(x.sum_seconds);
			x.is_positive = !x.is_positive;
		}
	}
	return x;
}

Duration Duration_sub(Duration x, Duration y){
	if (Duration_equal(y, DURATION_NAN)){
		return DURATION_NAN;
	}
	y.is_positive = !y.is_positive;
	return Duration_add(x, y);
}

Duration Duration_mult(Duration dur, Decimal factor){
	Decimal tmp;
	if (Decimal_less(factor, dzero)){
		factor = Decimal_neg(factor);
		dur.is_positive = !dur.is_positive;
	}
	tmp = Decimal_from_int(dur.sum_months);
	tmp = Decimal_mul(tmp, factor);
	dur.sum_months = Decimal_round(tmp);
	dur.sum_seconds = Decimal_mul(dur.sum_seconds, factor);
	return dur;
}

Duration Duration_divide(Duration dur, Decimal factor){
	Number tmpn1, tmpn2;
	double f = Decimal_to_double(factor);
	dur.sum_months = round(dur.sum_months / f);
	tmpn1 = Number_from_decimal(dur.sum_seconds);
	tmpn2 = Number_from_decimal(factor);
	tmpn1 = Number_div(tmpn1, tmpn2);
	dur.sum_seconds = Number_truncate(tmpn1, -3);
	return dur;
}

Number Duration_divide_by_Duration(Duration dur1, Duration dur2){
	Number ret, n1, n2;
	bool calc_months = (dur2.sum_months != 0);
	if (calc_months){
		if (Decimal_not_equal(dur1.sum_seconds, dzero)
				|| Decimal_not_equal(dur2.sum_seconds, dzero))
		{
			return NUMBER_NAN;
		}
		ret = Number_new_quotient(dur1.sum_months, dur2.sum_months);
	} else {
		if (dur1.sum_months != 0 || dur2.sum_months != 0){
			return NUMBER_NAN;
		}
		n1 = Number_from_decimal(dur1.sum_seconds);
		n2 = Number_from_decimal(dur2.sum_seconds);
		ret = Number_div(n1, n2);
	}
	if (dur1.is_positive != dur2.is_positive){
		return Number_neg(ret);
	}
	return ret;
}

int64_t Duration_get_years(Duration dur){
	int64_t ret;
	ret = dur.sum_months / 12;
	if (!dur.is_positive){
		ret = -ret;
	}
	return ret;
}

int64_t Duration_get_months(Duration dur){
	int64_t ret;
	ret = dur.sum_months % 12;
	if (!dur.is_positive){
		ret = -ret;
	}
	return ret;
}

int64_t Duration_get_days(Duration dur){
	int64_t ret = Decimal_floor(dur.sum_seconds);
	ret = ret / 86400;
	if (!dur.is_positive){
		ret = -ret;
	}
	return ret;
}
int64_t Duration_get_hours(Duration dur){
	int64_t ret = Decimal_floor(dur.sum_seconds);
	ret = (ret / 3600) % 24;
	if (!dur.is_positive){
		ret = -ret;
	}
	return ret;
}
int64_t Duration_get_minutes(Duration dur){
	int64_t ret = Decimal_floor(dur.sum_seconds);
	ret = (ret / 60) % 60;
	if (!dur.is_positive){
		ret = -ret;
	}
	return ret;
}

Decimal Duration_get_seconds(Duration dur){
	Decimal ret;
	int64_t tmp = Decimal_floor(dur.sum_seconds);
	tmp = tmp - (tmp % 60);
	ret = Decimal_sub(dur.sum_seconds, Decimal_from_int(tmp));
	if (!dur.is_positive){
		ret = Decimal_neg(ret);
	}
	return ret;
}


bool Duration_less(Duration x, Duration y){
	bool ret;
	if (x.is_positive != y.is_positive){
		if (x.is_positive){
			return false;
		} else {
			return true;
		}
	}
	if (x.sum_months < y.sum_months){
		ret = true;
	} else {
		ret = Decimal_less(x.sum_seconds, y.sum_seconds);
	}
	if (x.is_positive){
		return ret;
	} else {
		return !ret;
	}
}
bool Duration_less_or_equal(Duration x, Duration y){
	if (Duration_equal(x, y)){
		return true;
	}
	return Duration_less(x, y);
}

bool Duration_greater(Duration x, Duration y){
	if (Duration_equal(x, y)){
		return false;
	}
	return !Duration_less(x, y);
}

bool Duration_greater_or_equal(Duration x, Duration y){
	return !Duration_less(x, y);
}

void fprintf_Duration(FILE* f, Duration x){
	char* tmp = Duration_serialize(x);
	fprintf(f, "%s", tmp);
	free(tmp);
}
