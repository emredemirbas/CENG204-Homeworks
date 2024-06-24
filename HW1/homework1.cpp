// Name Surname : Emre Demirbaş
// Student ID   : 21050111069

#include <stdio.h>
#include <limits>

using namespace std;

#define k           8
#define f           23
#define bias        ((1 << (k-1)) - 1) // (2^k-1) - 1
#define expMask     ((1 << k) - 1) // 2^k - 1
#define fracMask    ((1 << f) - 1) // 2^f - 1

struct FloatValue {
private:
    unsigned char signBit;
    unsigned char expValue;
    unsigned int fracValue;

public:

    FloatValue(float value) {
        unsigned int intValue = *(unsigned int *) (&value);

        // s    ->  1 bit
        // exp  ->  8 bits (defined as k)
        // frac -> 23 bits (defined as f)
        // <s> <exp> <frac>

        // to determine the signBit, we should check the intValue's MSB.
        // if MSB of the intValue is 1, then signBit must be 1. Otherwise, it must be 0.
        // In order to obtain signBit, all the bits except MSB must be ignored.
        // Therefore, I applied right shift to intValue k + f = 31 positions.
        signBit = (unsigned char) ((intValue >> (k + f)) & 1);

        // to determine expValue, firstly we should get rid of sign bit.
        // then, apply right shift f + 1 bits, so that we can extract exp field.
        unsigned int temp = intValue;
        temp = temp << 1;
        temp = temp >> (f + 1);
        // temp now will look like -> <24 times 0><exp field>
        // apply bitwise & to extract expValue.
        expValue = (unsigned char) (temp & expMask);

        // since frac field is at the right-hand side,
        // no need to apply any shifting operations to obtain fracValue.
        fracValue = intValue & fracMask;
    }


    FloatValue(unsigned char signBit, unsigned char expValue, unsigned int fracValue)
            : signBit{(unsigned char) (signBit & 1)}, expValue{expValue}, fracValue{fracValue & fracMask} {

    }

    unsigned char getSignBit() {
        return signBit;
    }

    unsigned char getExpValue() {
        return expValue;
    }

    // E = Exp - Bias -> Normalized
    // E = 1 - Bias -> Denormalized
    int getE() {
        return (!isDenormalized()) ? expValue - bias : 1 - bias;
    }

    unsigned int getFracValue() {
        return fracValue;
    }


    // (a) Zero and (b) Equispaced numbers closest to zero
    // exp = 000...0
    bool isDenormalized() {
        return expValue == 0;
    }

    // a number is 0 if all the bits except signBit is 0.
    // we should not take signBit into account because there is positive and negative 0 in IEEE standards.
    bool isZero() {
        return expValue == 0 && fracValue == 0;
    }

    // (a) Infinity or (b) NaN
    // exp = 111...1 => equivalent to (2^k - 1) in decimal
    bool isSpecial() {
        return expValue == expMask;
    }

    // exp = 111...1 and frac = 000...0
    bool isInf() {
        return isSpecial() && fracValue == 0;
    }

    // exp = 111...1 and frac != 000...0
    bool isNaN() {
        return isSpecial() && fracValue != 0;
    }

    float value() {
        unsigned int res = 0; // 0 00000000 00000000000000000000000

        res = res | (signBit << (k + f)); // res = <s> 00000000 00000000000000000000000
        res = res | (expValue << f); // res = <s> <exp> 00000000000000000000000
        res = res | fracValue; // res = <s> <exp> <frac>

        return *(float *) (&res); // this is going to convert float without manipulating bits in res.
    }

};


int main() {
    // Special
    struct FloatValue number(-1.0f / 0.0f);
    //struct FloatValue number(1.0f / 0.0f);
    //struct FloatValue number(numeric_limits<float>::quiet_NaN());
    //struct FloatValue number(0.0f / 0.0f);
    //struct FloatValue number(-0.0f / 0.0f);

    // Denormalized
    //struct FloatValue number(0.0f);
    //struct FloatValue number(-0.0f);
    //struct FloatValue number(0, 0, 0);
    //struct FloatValue number(0, 0, 0b00000000000000000000001);
    //struct FloatValue number(0, 0, 0b1);

    // Normalized
    //struct FloatValue number(0, 1, 0b0);
    //struct FloatValue number(0, 1, 0b00000000000000000000001);
    //struct FloatValue number(0, 2, 0b00000000000000000000001);
    //struct FloatValue number(15213.0);
    //struct FloatValue number(0, 13 + bias, 0b11011011011010000000000);
    //struct FloatValue number(-15213.0);
    //struct FloatValue number(1, 13 + bias, 0b11011011011010000000000);
    //struct FloatValue number(15213.239258);
    //struct FloatValue number(-15213.239258);
    //struct FloatValue number(0.239258);
    //struct FloatValue number(3.402823466e38);

    printf("Float Value: %.50f \n", number.value());
    printf("Float Value: %e \n", number.value());
    printf("sign=%d, exp=%d (E=%d), frac=%d \n", number.getSignBit(), number.getExpValue(), number.getE(),
           number.getFracValue());
    printf("Is Denormalized : %d \t (Is Zero : %d) \n", number.isDenormalized(), number.isZero());
    printf("Is Infinity : %d \t (Is Special : %d) \n", number.isInf(), number.isSpecial());
    printf("Is NaN :  %d \t\t (Is Special : %d) ", number.isNaN(), number.isSpecial());


    return 0;
}