#include "AdvancedCDatatypesDecimal.h"
#include <math.h>
#include <stdlib.h>

Decimal Number_truncate(Number x, int64_t exponent_cut){
	switch(x.type){
		case NT_FLOAT:
			return DECIMAL_NAN;
		case NT_DECIMAL:
			return Decimal_truncate(x.d, exponent_cut);
		case NT_QUOTIENT:
			return DECIMAL_NAN;
	}
}

double Number_as_float(Number x){
	switch(x.type){
		case NT_FLOAT:
			return x.f;
		case NT_DECIMAL:
			return x.d.significand * pow(10, x.d.exponent);
		case NT_QUOTIENT:
			return x.q.numerator / x.q.denominator;
	}
}

Number Number_new_quotient(int64_t numerator, int64_t denominator){
	Number ret;
	ret.type = NT_QUOTIENT;
	ret.q = Quotient_new(numerator, denominator);
	return ret;
}

Number Number_from_decimal(Decimal decimal){
	Number ret;
	ret.type = NT_DECIMAL;
	ret.d = decimal;
	char*q = Decimal_serialize(decimal);
	fprintf(stderr, "brubru  %s\n", q);
	fprintf_Number(stderr, ret);
	return ret;
}

Number Number_from_float(double x){
	Number ret;
	ret.type = NT_FLOAT;
	ret.f = x;
	return ret;
}

Number Number_div(Number x, Number y){
	Number ret;
	Quotient qx, qy;
	Decimal tmpd;
	if (x.type == NT_FLOAT || y.type == NT_FLOAT){
		ret.type = NT_FLOAT;
		ret.f = Number_as_float(x) / Number_as_float(y);
		return ret;
	}
	switch (x.type){
		case NT_DECIMAL:
			qx = Decimal_as_quotient(x.d);
			break;
		case NT_QUOTIENT:
			qx = x.q;
			break;
	}
	switch (y.type){
		case NT_DECIMAL:
			qy = Decimal_as_quotient(y.d);
			break;
		case NT_QUOTIENT:
			qy = y.q;
			break;
	}
	ret.type = NT_QUOTIENT;
	ret.q = Quotient_div(qx, qy);
	tmpd = Quotient_try_to_decimal(ret.q);
	if (Decimal_not_equal(tmpd, DECIMAL_NAN)){
		ret.type = NT_DECIMAL;
		ret.d = tmpd;
	}
	return ret;
}

/*
Number Number_inv(Number){
}

Number Number_neg(Number){
}

Number Number_mult(Number, Number){
}
*/


bool Number_equal(Number x, Number y){
	Decimal tmpd;
	if (x.type == y.type){
		switch (x.type){
			case NT_FLOAT:
				return x.f == y.f;
			case NT_DECIMAL:
				return Decimal_equal(x.d, y.d);
			case NT_QUOTIENT:
				return Quotient_equal(x.q, y.q);
		}
	}
	if (x.type == NT_FLOAT || y.type == NT_FLOAT){
		return false;
	}
	if (x.type == NT_DECIMAL && y.type == NT_QUOTIENT){
		tmpd = Quotient_try_to_decimal(y.q);
		if (Decimal_equal(tmpd, DECIMAL_NAN)){
			return false;
		}
		return Decimal_equal(tmpd, x.d);
	}
	if (y.type == NT_DECIMAL && x.type == NT_QUOTIENT){
		tmpd = Quotient_try_to_decimal(x.q);
		if (Decimal_equal(tmpd, DECIMAL_NAN)){
			return false;
		}
		return Decimal_equal(tmpd, y.d);
	}
	return false;
}

bool Number_not_equal(Number x, Number y){
	return !Number_equal(x, y);
}

Number Number_neg(Number x){
	switch(x.type){
		case NT_FLOAT:
			x.f = -x.f;
			return x;
		case NT_DECIMAL:
			x.d = Decimal_neg(x.d);
			return x;
		case NT_QUOTIENT:
			x.q = Quotient_neg(x.q);
			return x;
	}
}


int Number_idiv(Number x, Number y){
	Number ret;
	Quotient qx, qy;
	Decimal tmpd;
	if (x.type == NT_FLOAT || y.type == NT_FLOAT){
		return Number_as_float(x) / Number_as_float(y);
	}
	switch (x.type){
		case NT_DECIMAL:
			qx = Decimal_as_quotient(x.d);
			break;
		case NT_QUOTIENT:
			qx = x.q;
			break;
	}
	switch (y.type){
		case NT_DECIMAL:
			qy = Decimal_as_quotient(y.d);
			break;
		case NT_QUOTIENT:
			qy = y.q;
			break;
	}
	return Quotient_idiv(qx, qy);
}


Number Number_mod(Number x, Number y){
	Number ret;
	Quotient qx, qy;
	Decimal tmpd;
	if (x.type == NT_FLOAT || y.type == NT_FLOAT){
		ret.type = NT_FLOAT;
		ret.f = fmod(Number_as_float(x), Number_as_float(y));
		return ret;
	}
	switch (x.type){
		case NT_DECIMAL:
			qx = Decimal_as_quotient(x.d);
			break;
		case NT_QUOTIENT:
			qx = x.q;
			break;
	}
	switch (y.type){
		case NT_DECIMAL:
			qy = Decimal_as_quotient(y.d);
			break;
		case NT_QUOTIENT:
			qy = y.q;
			break;
	}
	ret.type = NT_QUOTIENT;
	ret.q = Quotient_mod(qx, qy);
	tmpd = Quotient_try_to_decimal(ret.q);
	if (Decimal_not_equal(tmpd, DECIMAL_NAN)){
		ret.type = NT_DECIMAL;
		ret.d = tmpd;
	}
	return ret;
}


void fprintf_Number(FILE* f, Number n){
	char* tmp;
	switch(n.type){
		case NT_FLOAT:
			fprintf(f, "%f", n.f);
			return;
		case NT_DECIMAL:
			tmp = Decimal_serialize(n.d);
			if (tmp != NULL){
				fprintf(f, "%s", tmp);
				free(tmp);
			} else {
				fprintf(f, "NAN");
			}
			return;
		case NT_QUOTIENT:
			fprintf_Quotient(f, n.q);
			return;
	}
}
