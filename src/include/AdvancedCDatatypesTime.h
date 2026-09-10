#pragma once

#include <stdint.h>
#include "AdvancedCDatatypesDecimal.h"

#define DATETIME_NOOFFSET -1000
#define DATETIME_MAXOFFSET 840
#define DATETIME_MINOFFSET -840

typedef int64_t GetCurrentTimezoneInMinutes();
extern GetCurrentTimezoneInMinutes get_local_timezone;

typedef struct s_DateTime {
	int64_t year;
	int64_t month;
	int64_t day;
	int64_t hour;
	int64_t minute;
	Decimal seconds;
	int32_t offset_minutes;
} DateTime;

typedef struct s_Time {
	int64_t hour;
	int64_t minute;
	Decimal seconds;
	int32_t offset_minutes;
} Time;

typedef struct s_Date {
	int64_t year;
	int64_t month;
	int64_t day;
	int32_t offset_minutes;
} Date;

typedef struct s_Duration {
	bool is_positive;
	int64_t sum_months;
	Decimal sum_seconds;
} Duration;

static const Duration DURATION_NAN = {
	.is_positive = true,
	.sum_months = -1000,
	.sum_seconds = DECIMAL_NAN,
};

static const DateTime DATETIME_NOTVALID = {
	.year = -100000,
	.month = -10000,
	.day = -10000,
	.hour = -10000,
	.minute = -100000,
	.seconds = DECIMAL_NAN,
	.offset_minutes = DATETIME_NOOFFSET,
};

static const Date DATE_NOTVALID = {
	.year = -100000,
	.month = -10000,
	.day = -10000,
	.offset_minutes = DATETIME_NOOFFSET,
};

static const Time TIME_NOTVALID = {
	.hour = -10000,
	.minute = -100000,
	.seconds = DECIMAL_NAN,
	.offset_minutes = DATETIME_NOOFFSET,
};


Duration DateTime_offset_as_duration(DateTime);
bool DateTime_is_DateTimeStamp(DateTime);
Duration DateTime_sub(DateTime, DateTime);
DateTime DateTime_add(DateTime, Duration);

bool DateTime_equal(DateTime, DateTime);
bool DateTime_not_equal(DateTime, DateTime);
bool DateTime_less(DateTime, DateTime);
bool DateTime_less_or_equal(DateTime, DateTime);
bool DateTime_greater(DateTime, DateTime);
bool DateTime_greater_or_equal(DateTime, DateTime);

DateTime DateTime_parse(const char*);
char* DateTime_serialize(DateTime);


Duration Time_offset_as_duration(Time);
Duration Time_sub(Time, Time);
Time Time_add(Time, Duration);
bool Time_equal(Time, Time);
bool Time_not_equal(Time, Time);
bool Time_less(Time, Time);
bool Time_less_or_equal(Time, Time);
bool Time_greater(Time, Time);
bool Time_greater_or_equal(Time, Time);

Time Time_parse(const char*);
char* Time_serialize(Time);

Duration Date_offset_as_duration(Date);

/**
 * First add months to date. Then add days.
 */
Date Date_add(Date, Duration);

Duration Date_sub(Date, Date);
bool Date_equal(Date, Date);
bool Date_not_equal(Date, Date);
bool Date_less(Date, Date);
bool Date_less_or_equal(Date, Date);
bool Date_greater(Date, Date);
bool Date_greater_or_equal(Date, Date);

Date Date_new(int64_t year, int64_t month, int64_t day, int32_t offset_minutes);

Date Date_parse(const char*);
char* Date_serialize(Date);

Duration Duration_from_seconds(Decimal);
Duration Duration_from_minutes(int64_t);
Duration Duration_add(Duration, Duration);
Duration Duration_sub(Duration, Duration);
Duration Duration_mult(Duration, Decimal);
Duration Duration_divide(Duration, Decimal);
Number Duration_divide_by_Duration(Duration, Duration);

int64_t Duration_get_years(Duration);
int64_t Duration_get_months(Duration);
int64_t Duration_get_days(Duration);
int64_t Duration_get_hours(Duration);
int64_t Duration_get_minutes(Duration);
Decimal Duration_get_seconds(Duration);

bool Duration_equal(Duration, Duration);
bool Duration_not_equal(Duration, Duration);
bool Duration_less(Duration, Duration);
bool Duration_less_or_equal(Duration, Duration);
bool Duration_greater(Duration, Duration);
bool Duration_greater_or_equal(Duration, Duration);

Duration Duration_parse(const char*);
char* Duration_serialize(Duration);
char* Duration_serialize_prefer_YearMonth(Duration);

void fprintf_Duration(FILE*, Duration);
void fprintf_DateTime(FILE*, DateTime);
void fprintf_Date(FILE*, Date);
void fprintf_Time(FILE*, Time);
