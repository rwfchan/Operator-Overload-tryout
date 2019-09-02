#include "MyFloat.h"

MyFloat::MyFloat(){
  sign = 0;
  exponent = 0;
  mantissa = 0;
}

MyFloat::MyFloat(float f){
  unpackFloat(f);
}

MyFloat::MyFloat(const MyFloat & rhs){
	sign = rhs.sign;
	exponent = rhs.exponent;
	mantissa = rhs.mantissa;
}

ostream& operator<<(std::ostream &strm, const MyFloat &f){
	//this function is complete. No need to modify it.
	strm << f.packFloat();
	return strm;
}


MyFloat MyFloat::operator+(const MyFloat& rhs) const{
	MyFloat lhs_float(*this);
	MyFloat rhs_float(rhs);
	MyFloat result_float;

	//Rewrite mantissa so they have a one in the front
	lhs_float.mantissa |= 0b100000000000000000000000;
	rhs_float.mantissa |= 0b100000000000000000000000;

	//Compare two float, rewrite smaller float, or in this case, shift the bigger float
	//First compare exponent, shift the bigger float

	if(lhs_float.exponent > rhs_float.exponent) {
		result_float.exponent = lhs_float.exponent;
		rhs_float.mantissa >>= (lhs_float.exponent - rhs_float.exponent);
	} else if(rhs_float.exponent > lhs_float.exponent) {
		result_float.exponent = rhs_float.exponent;
		lhs_float.mantissa >>= (rhs_float.exponent - lhs_float.exponent);
	} else {//If both exponents are the same, no need to shift
		result_float.exponent = lhs_float.exponent;
	}
	//Adding the two mantissa
	//If one of them is negative, negate one of them
	//If both of them is negative, do addition, but ending with negative

	//If either one and only one of them is negative
	if(lhs_float.sign != rhs_float.sign) {
		//If lhs < rhs, just make lhs to -1
		if (lhs_float.sign == 1 && lhs_float.mantissa < rhs_float.mantissa) {
			lhs_float.mantissa = (~lhs_float.mantissa) + 1;
			//But if lhs > rhs, make rhs -1, but result_float is negative
		} else if (lhs_float.sign == 1 && lhs_float.mantissa > rhs_float.mantissa) {
			result_float.sign = 1;
			rhs_float.mantissa = (~rhs_float.mantissa) + 1;
			//Same logic for rhs
		} else if (rhs_float.sign == 1 && lhs_float.mantissa > rhs_float.mantissa) {
			rhs_float.mantissa = (~rhs_float.mantissa) + 1;
		} else if (rhs_float.sign == 1 && lhs_float.mantissa < rhs_float.mantissa) {
			result_float.sign = 1;
			lhs_float.mantissa = (~lhs_float.mantissa) + 1;
		} else {
			result_float.mantissa = 0;
			result_float.exponent = 0;
			return result_float;
		}

	} else if (lhs_float.sign == 1 && (lhs_float.sign == rhs_float.sign)){
		result_float.sign = 1;
	}

	//Put sum into result_float
	result_float.mantissa = lhs_float.mantissa + rhs_float.mantissa;

	//Normalize the result_float

	//If this is negative addition/ simple subtraction, remove potiental overflow
	//Remove potiental overflow
    //FIXME START OF ORG. CODE
	/*if(lhs_float.sign != rhs_float.sign) {
		result_float.mantissa &= 0b0111111111111111111111111;
	}*/

	//Starting from bit 24, check if that bit is 1
	//If that bit is 1 at 24, result_exponent + 1, this is overflow
	//If not, move on to current_bit - 1
	//result_exponent -= amount of bit until 1 found - 1
	/*int current_bit = 0;
	for(int i = 24; i >= 0; i--) {
		//If the mantissa at i is 1, actually shift current_bit amount
		//Also, check the exponent
		if((result_float.mantissa >> i) == 1) {
			//Check for overflow, aka i = 24
			//if overflow occur, bit shift left

			//This is for addition rule
			if(i == 24 && (lhs_float.sign == rhs_float.sign)) {
				result_float.mantissa >>= 1;

			//Move bits only for subtraction
			} else if (lhs_float.sign != rhs_float.sign) {
				result_float.mantissa <<= (current_bit - 1);
			}

			//Remove filter bit
			result_float.mantissa &= 0b011111111111111111111111;

			result_float.exponent -= (current_bit - 1);
			break;
		} else { //else, current_bit checked + 1
			current_bit += 1;
		}
	}*/
  //FIXME END OF ORG. CODE
    if((result_float.mantissa >> 24) == 1 && (lhs_float.sign == rhs_float.sign)) {
      result_float.mantissa >>= 1;
    } else if(lhs_float.sign != rhs_float.sign) {
      result_float.mantissa &= 0b0011111111111111111111111;
    }

	return result_float; //you don't have to return *this. it's just here right now so it will compile
}

MyFloat MyFloat::operator-(const MyFloat& rhs) const{
	MyFloat result_float;
	MyFloat rhs_float(rhs);

	rhs_float.sign = (~rhs_float.sign)&1;

	result_float = *this + rhs_float;
	
	return result_float; //you don't have to return *this. it's just here right now so it will compile
}

bool MyFloat::operator==(const float rhs) const{
	return false; //this is just a stub so your code will compile
}


void MyFloat::unpackFloat(float f) {
	//this function must be written in inline assembly
	//extracts the fields of f into sign, exponent, and mantissa
	__asm__(
		"movl %%eax, %%edx;"	//move f onto mantissa
		"andl $8388607, %%edx;"	//only get the first 23 digits
		"movl %%eax, %%ecx;"	//move f onto exponent
		"shrl $23, %%ecx;"		//shift to get the exponent field
		"andl $255, %%ecx;"		//only get the first 8 digits
		"shrl $31, %%eax;"		//shift all the way to most-sig bit to get sign bit

		: "=a" (this->sign), "=c" (this->exponent), "=d" (this->mantissa) // output
		: "a" (f)	// input
	);

	//unsigned int number1 = this->sign;
	//unsigned int number2 = this->exponent;
	//unsigned int number3 = this->mantissa;

}//unpackFloat

float MyFloat::packFloat() const{
	//this function must be written in inline assembly
  //returns the floating point number represented by this
  float f = 0;
	//unsigned int answer = 0;

	//unsigned int number1 = this->sign;
	//unsigned int number2 = this->exponent;
	//unsigned int number3 = this->mantissa;

	__asm__(
		"shll $31, %%eax;"
		"shll $23, %%ecx;"
		"orl %%ecx, %%eax;"
		"orl %%edx, %%eax;"

		: "=a" (f)
		: "a" (this->sign), "c" (this->exponent), "d" (this->mantissa) // output
	);

	return f;
}//packFloat
//



