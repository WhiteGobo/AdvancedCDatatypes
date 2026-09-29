#include "AdvancedCDatatypesDecimal.h"

static int64_t find_gcd(int64_t a, int64_t b);
static Quotient Quotient_normalize(Quotient);

Quotient Quotient_new(int64_t numerator, int64_t denominator){
	Quotient ret;
	ret.numerator = numerator;
	ret.denominator = denominator;
	return Quotient_normalize(ret);
}

Quotient Quotient_div(Quotient x, Quotient y){
	y = Quotient_inv(y);
	return Quotient_mult(x, y);
}

Quotient Quotient_inv(Quotient x){
	int64_t tmp;
	tmp = x.numerator;
	x.numerator = x.denominator;
	x.denominator = tmp;
	return x;
}

Quotient Quotient_neg(Quotient x){
	x.numerator = -x.numerator;
	return x;
}

Quotient Quotient_mult(Quotient x, Quotient y){
	x.numerator *= y.numerator;
	x.denominator *= y.denominator;
	return Quotient_normalize(x);
}

Decimal Quotient_try_to_decimal(Quotient x){
	int64_t tmp, significand, exp, exp1 = 0, exp2 = 0;
	x = Quotient_normalize(x);
	tmp = x.denominator;
	if(tmp == 0) return DECIMAL_NAN;
	while(tmp % 2 == 0){
		tmp = tmp>>1;
		exp1 -= 1;
	}
	while(tmp >= 5){
		if (tmp % 5 != 0){
			return DECIMAL_NAN;
		}
		tmp /= 5;
		exp2 -= 1;
	}
	if (tmp != 1){
		return DECIMAL_NAN;
	}
	significand = x.numerator;
	if (exp1 == exp2){
		exp = exp1;
	} else if (exp1 > exp2){
		for(int i=exp2; i < exp1; i++){
			significand *= 2;
		}
		exp = exp2;
	} else {
		for(int i=exp1; i < exp2; i++){
			significand *= 5;
		}
		exp = exp1;
	}
	return Decimal_new(significand, exp);
}

double Quotient_to_float(Quotient x){
	double n, q;
	n = x.numerator;
	q = x.denominator;
	return n/q;
}


Quotient Quotient_mod(Quotient x, Quotient y){
	int64_t qx, qy, lcm, tmp, gcd;
	gcd = find_gcd(x.denominator, y.denominator);
	lcm = x.denominator * (y.denominator / gcd);
	qx = x.numerator * (y.denominator / gcd);
	qy = y.numerator * (x.denominator / gcd);
	tmp = qx % qy;
	return Quotient_new(tmp, lcm);
}


int Quotient_idiv(Quotient x, Quotient y){
	int ret;
	bool is_positive = true;
	x.numerator *= y.denominator;
	x.denominator *= y.numerator;
	if (x.numerator < 0){
		is_positive = !is_positive;
		x.numerator = -x.numerator;
	}
	if (x.denominator < 0){
		is_positive = !is_positive;
		x.denominator = -x.denominator;
	}
	//integer division works as floor(x/y)
	ret = x.numerator / x.denominator;
	if (is_positive){
		return ret;
	} else {
		return -ret;
	}
}



static Quotient Quotient_normalize(Quotient x){
	int gcd = find_gcd(x.numerator, x.denominator);
	x.numerator /= gcd;
	x.denominator /= gcd;
	if (x.denominator < 0){
		x.numerator = -x.numerator;
		x.denominator = -x.denominator;
	}
	return x;
}


/**
 * greatest common divisor
 * Euclidean Algorithm
 */
static int64_t find_gcd(int64_t a, int64_t b)
{
	if (a < 0){
		a = -a;
	}
	if (b < 0){
		b = -b;
	}
	for(int i=0; i < 10000; i++){
		if (a == 0) {
			return b;
		} else if (b == 0) {
			return a;
		} else if (a == b) {
			return a;
		} else if (a > b) {
			a = a-b;
		} else {
			b = b-a;
		}
	}
	return 1;
}

bool Quotient_equal(Quotient x, Quotient y){
	if (x.numerator != y.numerator){
		return false;
	}
	return x.denominator == y.denominator;
}

bool Quotient_not_equal(Quotient x, Quotient y){
	return !Quotient_equal(x, y);
}

void fprintf_Quotient(FILE* f, Quotient q){
	fprintf(f, "%d/%d", q.numerator, q.denominator);
}
