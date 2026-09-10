#include "AdvancedCDatatypeDecimal.h"
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct RET_PARSE_BEFORE_COMMA {
	bool error;
	size_t i;
	int64_t significand;
};
static Decimal Decimal_normalize(Decimal);
static struct RET_PARSE_BEFORE_COMMA parse_before_comma(const char* input, size_t len);
static Decimal parse_after_comma(const char* input, size_t len, int64_t significand);
static Decimal Decimal_add_unnormalized(Decimal x, Decimal y);

static Decimal Decimal_normalize(Decimal x){
	if (x.significand == 0){
		x.exponent = 0;
		return x;
	}
	for (size_t i = 0; i<32; i++){
		if (x.significand % 10 == 0){
			x.significand /= 10;
			x.exponent++;
		} else {
			return x;
		}
	}
	if (x.exponent > 840 || x.exponent < -840){
		return DECIMAL_NAN;
	}
	return x;
}

static Decimal Decimal_add_unnormalized(Decimal x, Decimal y){
	uint32_t tmp;
	if (x.exponent <= y.exponent){
		tmp = y.exponent - x.exponent;
		y.significand = y.significand << tmp;
		for (size_t i=0; i < tmp; i++){
			y.significand *= 5;
		}
		x.significand += y.significand;
		return x;
	} else {
		return Decimal_add(y, x);
	}
}

Decimal Decimal_new(int64_t significand, int32_t exponent){
	Decimal ret;
	ret.significand = significand;
	ret.exponent = exponent;
	return Decimal_normalize(ret);
}

Quotient Decimal_as_quotient(Decimal x){
	int64_t tmp;
	Quotient ret;
	if (x.exponent < 0){
		tmp = 1;
		for(int i=0; i>x.exponent; i--){
			tmp *= 10;
		}
		return Quotient_new(x.significand, tmp);
	} else {
		tmp = x.significand;
		for(int i=0; i<x.exponent; i++){
			tmp *= 10;
		}
		return Quotient_new(tmp, 1);
	}
}

Decimal Decimal_add(Decimal x, Decimal y){
	return Decimal_normalize(Decimal_add_unnormalized(x, y));
}

Decimal Decimal_sub(Decimal x, Decimal y){
	y.significand *= -1;
	return Decimal_add(x, y);
}

Decimal Decimal_mul(Decimal x, Decimal y){
	x.exponent += y.exponent;
	x.significand *= y.significand;
	return Decimal_normalize(x);
}

Decimal Decimal_neg(Decimal x){
	x.significand = -x.significand;
	return x;
}

double Decimal_div(Decimal x, Decimal y){
	double dx, dy;
	dx = Decimal_to_double(x);
	dy = Decimal_to_double(y);
	return dx / dy;
}

bool Decimal_equal(Decimal left, Decimal right){
	if (left.exponent != right.exponent) {
		return false;
	}
	return left.significand == right.significand;
}

bool Decimal_not_equal(Decimal left, Decimal right){
	return !Decimal_equal(left, right);
}

bool Decimal_less(Decimal left, Decimal right){
	return !Decimal_greater_or_equal(left, right);
}

bool Decimal_less_or_equal(Decimal left, Decimal right){
	return !Decimal_greater(left, right);
}

bool Decimal_greater(Decimal left, Decimal right){
	if(Decimal_equal(left, right)){
		return false;
	}
	return Decimal_greater_or_equal(left, right);
}

bool Decimal_greater_or_equal(Decimal left, Decimal right){
	int64_t tmp;
	if(Decimal_equal(left, right)){
		return true;
	}
	right.significand *= -1;
	left = Decimal_add_unnormalized(left, right);
	return left.significand >= 0;
}

Decimal Decimal_from_int(int64_t x){
	Decimal ret = {
		.exponent = 0,
		.significand = x,
	};
	return Decimal_normalize(ret);
}

/*
Decimal Decimal_from_double(double){
	return DECIMAL_NAN;
}
*/


double Decimal_to_double(Decimal x){
	return x.significand * pow(10, x.exponent);
}

int64_t Decimal_floor(Decimal x){
	if(x.exponent == -1000){
		return 0;
	}
	if (x.exponent <= 0 ){
		for (int32_t i=0; i > x.exponent && x.significand != 0; i--){
			x.significand /= 10;
		}
		return x.significand;
	} else {
		for (int32_t i=0; i < x.exponent; i++){
			x.significand *= 10;
		}
		return x.significand;
	}
}

int64_t Decimal_round(Decimal x){
	int tmp;
	if(x.exponent == -1000){
		return 0;
	}
	if (x.exponent <= 0 ){
		for (int32_t i=0; i > x.exponent+1 && x.significand != 0; i--){
			x.significand /= 10;
		}
		x.significand /=5;
		tmp = x.significand % 2;
		x.significand = x.significand/2;
		return x.significand + tmp;
	} else {
		for (int32_t i=0; i < x.exponent; i++){
			x.significand *= 10;
		}
		return x.significand;
	}
}

Decimal Decimal_truncate(Decimal x, int64_t exponent_cut){
	if (x.exponent >= exponent_cut){
		return x;
	}
	for(int i=x.exponent; i< exponent_cut; i++){
		x.significand /= 10;
	}
	x.exponent = exponent_cut;
	return x;
}

Decimal Decimal_negate(Decimal x){
	x.significand = -x.significand;
	return x;
}

Decimal Decimal_parse(const char* input, int32_t len){
	Decimal ret;
	bool is_negative = false;
	if (input == NULL) return DECIMAL_NAN;
	if (len < 0){
		len = strlen(input);
	}
	if (len == 0){
		ret.exponent = 0;
		ret.significand = 0;
		return ret;
	}
	switch(input[0]){
		case '-':
			is_negative = true;
		case '+':
			input++;
			len--;
	}
	struct RET_PARSE_BEFORE_COMMA ret_pbc = parse_before_comma(input, len);
	if (ret_pbc.error){
		return DECIMAL_NAN;
	}

	ret = parse_after_comma(input + ret_pbc.i, len - ret_pbc.i,
				ret_pbc.significand);
	if (is_negative){
		ret.significand = -ret.significand;
	}
	return ret;
}


static Decimal parse_after_comma(const char* input, size_t len, int64_t significand)
{
	Decimal ret = {
		.exponent = 0,
		.significand = significand,
	};
	for(size_t i = 0; i<len; i++){
		switch(input[i]){
			case '0':
				ret.exponent -= 1;
				ret.significand *= 10;
				break;
			case '1':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 1;
				break;
			case '2':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 2;
				break;
			case '3':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 3;
				break;
			case '4':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 4;
				break;
			case '5':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 5;
				break;
			case '6':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 6;
				break;
			case '7':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 7;
				break;
			case '8':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 8;
				break;
			case '9':
				ret.exponent -= 1;
				ret.significand = (ret.significand * 10) + 9;
				break;
			default:
				return DECIMAL_NAN;
		}
	}
	return Decimal_normalize(ret);
}

static struct RET_PARSE_BEFORE_COMMA parse_before_comma(const char* input, size_t len)
{
	struct RET_PARSE_BEFORE_COMMA ret = {
		.error = false,
		.i = 0,
		.significand = 0,

	};
	while(ret.i < len){
		switch(input[ret.i]){
			case '0':
				ret.significand *= 10;
				break;
			case '1':
				ret.significand = (ret.significand * 10) + 1;
				break;
			case '2':
				ret.significand = (ret.significand * 10) + 2;
				break;
			case '3':
				ret.significand = (ret.significand * 10) + 3;
				break;
			case '4':
				ret.significand = (ret.significand * 10) + 4;
				break;
			case '5':
				ret.significand = (ret.significand * 10) + 5;
				break;
			case '6':
				ret.significand = (ret.significand * 10) + 6;
				break;
			case '7':
				ret.significand = (ret.significand * 10) + 7;
				break;
			case '8':
				ret.significand = (ret.significand * 10) + 8;
				break;
			case '9':
				ret.significand = (ret.significand * 10) + 9;
				break;
			case '.':
				ret.i++;
				return ret;
			default:
				ret.error = true;
				return ret;
		}
		ret.i++;
	}
	return ret;
}

static char* Decimal_serialize_full(Decimal x, bool never_print_exponent);

char* Decimal_serialize(Decimal x){
	return Decimal_serialize_full(x, false);
}

char * Decimal_serialize_plain(Decimal x){
	return Decimal_serialize_full(x, true);
}

static char* Decimal_serialize_full(Decimal x, bool never_print_exponent){
	bool print_exponent;
	char* ret;
	char tmp[24], tmp_exponent[5];
	int32_t tmp_exp;
	size_t i, tmp_len, tmp_exponent_len;
	if (Decimal_equal(DECIMAL_NAN, x)){
		return NULL;
	}
	if (x.significand >= 0){
		sprintf(tmp, "%d", x.significand);
	} else {
		sprintf(tmp, "%d", -x.significand);
	}
	tmp_len = strlen(tmp);
	tmp_exp = x.exponent + tmp_len - 1;
	print_exponent = !never_print_exponent
				&& !(tmp_exp >= -1 && tmp_exp <= 3);
	if (print_exponent){
		sprintf(tmp_exponent, "%d", tmp_exp);
		tmp_exponent_len = strlen(tmp_exponent);
		if (x.significand >= 0){
			ret = malloc(tmp_len + tmp_exponent_len + 5);
			sprintf(ret, "%c.%sE%s", tmp[0], tmp+1, tmp_exponent);
		} else {
			ret = malloc(tmp_len + tmp_exponent_len + 6);
			sprintf(ret, "-%c.%sE%s", tmp[0], tmp+1, tmp_exponent);
		}
	} else if(tmp_exp < 0){
		size_t j = 0;
		ret = malloc(tmp_len + 6);
		if (x.significand < 0){
			ret[0] = '-';
			j++;
		}
		ret[j] = '.';
		j++;
		for (int i = -1; i > tmp_exp; i--){
			ret[j] = '0';
			j++;
		}
		sprintf(ret + j, "%s", tmp);
	} else if(tmp_exp + 1 < tmp_len){
		size_t j = 0;
		char *qq;
		ret = malloc(tmp_len + 6);
		qq = ret;
		if (x.significand < 0){
			ret[0] = '-';
			qq = ret+1;
		}
		for (int i = 0; i <= tmp_exp; i++){
			qq[j] = tmp[i];
			j++;
		}
		sprintf(qq+j, ".%s", tmp+j);
	} else {
		size_t j = 0;
		ret = malloc(6 + tmp_exp);
		if (x.significand < 0){
			ret[0] = '-';
			j++;
		}
		memcpy(ret+j, tmp, tmp_len);
		j += tmp_len;
		for (int i = tmp_len-1; i<tmp_exp; i++){
			ret[j] = '0';
			j++;
		}
		ret[j] = '\0';
	}
	return ret;
}

void fprintf_Decimal(FILE* f, Decimal x){
	char* tmp = Decimal_serialize(x);
	fprintf(f, "%s", tmp);
	free(tmp);
}
