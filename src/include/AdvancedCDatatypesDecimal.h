#pragma once

/*
 *
 * TODO: Rename Number to Numeric
 */


#include <stdint.h>
#include <stdio.h>

//https://github.com/mirotvorecc/c-decimal/blob/master/src/s21_decimal.h

#define cpy_decimal(target, source) \
	target.exponent = source.exponent;\
	target.significand = source.significand;

typedef struct s_Decimal {
	int32_t exponent;
	int64_t significand;
} Decimal;

typedef struct s_Quotient {
	int64_t numerator;
	int64_t denominator;
} Quotient;

typedef enum {
	NT_NAN,
	NT_FLOAT,
	NT_DECIMAL,
	NT_QUOTIENT,
} NumberType;

typedef struct s_Number {
	NumberType type;
	union {
		Decimal d;
		double f;
		Quotient q;
	};
} Number;

static const Decimal DECIMAL_NAN = {
	.exponent = -1000,
	.significand = 0,
};

static const Number NUMBER_NAN = {
	.type = NT_NAN,
	.f = 0,
};

Quotient Quotient_new(int64_t numerator, int64_t denominator);
Decimal Quotient_try_to_decimal(Quotient);
double Quotient_to_float(Quotient);
Quotient Quotient_div(Quotient, Quotient);
Quotient Quotient_add(Quotient, Quotient);
Quotient Quotient_inv(Quotient);
Quotient Quotient_neg(Quotient);
Quotient Quotient_mult(Quotient, Quotient);
Quotient Quotient_mod(Quotient, Quotient);
int Quotient_idiv(Quotient, Quotient);

bool Quotient_equal(Quotient, Quotient);
bool Quotient_not_equal(Quotient, Quotient);

Decimal Number_truncate(Number, int64_t exponent_cut);
double Number_as_float(Number);
Number Number_new_quotient(int64_t numerator, int64_t denominator);
Number Number_from_decimal(Decimal);
Number Number_from_float(double);
Number Number_div(Number, Number);
Number Number_inv(Number);
Number Number_neg(Number);
Number Number_mult(Number, Number);
Number Number_add(Number, Number);
Number Number_sub(Number, Number);

/*
 * Following rule for result. See `https://www.w3.org/TR/xpath-functions/#func-numeric-integer-divide`_
 */
int Number_idiv(Number, Number);

/*
 * See `https://www.w3.org/TR/xpath-functions/#func-numeric-mod`_
 */
Number Number_mod(Number, Number);


bool Number_equal(Number, Number);
bool Number_not_equal(Number, Number);
bool Number_less(Number left, Number right);
bool Number_less_or_equal(Number left, Number right);
bool Number_greater(Number left, Number right);
bool Number_greater_or_equal(Number left, Number right);


Decimal Decimal_new(int64_t significand, int32_t exponent);
Decimal Decimal_add(Decimal, Decimal);
Decimal Decimal_sub(Decimal, Decimal);
Decimal Decimal_mul(Decimal, Decimal);
double Decimal_div(Decimal, Decimal);
Decimal Decimal_neg(Decimal);

bool Decimal_equal(Decimal left, Decimal right);
bool Decimal_not_equal(Decimal left, Decimal right);
bool Decimal_less(Decimal left, Decimal right);
bool Decimal_less_or_equal(Decimal left, Decimal right);
bool Decimal_greater(Decimal left, Decimal right);
bool Decimal_greater_or_equal(Decimal left, Decimal right);
Quotient Decimal_as_quotient(Decimal);

Decimal Decimal_from_int(int64_t);
//Decimal Decimal_from_double(double);
double Decimal_to_double(Decimal);

int64_t Decimal_floor(Decimal);
int64_t Decimal_round(Decimal);
Decimal Decimal_truncate(Decimal, int64_t exponent_cut);
Decimal Decimal_negate(Decimal);

Decimal Decimal_parse(const char*, int32_t len);
char* Decimal_serialize(Decimal);
char* Decimal_serialize_plain(Decimal);

void fprintf_Number(FILE*, Number);
void fprintf_Quotient(FILE*, Quotient);
void fprintf_Decimal(FILE*, Decimal);
