// Name Surname :
// Student ID   :

#include <stdio.h>

using namespace std;

#define k           8 
#define f           23
#define bias        ((1 << (k-1)) - 1)
#define expMask     ((1 << k) - 1)
#define fracMask    ((1 << f) - 1)

struct FloatValue {
private:    
    unsigned char signBit;
    unsigned char expValue;
    unsigned int fracValue;
    
public:    
    FloatValue(float value) 
    {
        unsigned int intValue = *(unsigned int*)(&value);
        
        // student code
    }
    
    FloatValue(unsigned char signBit, unsigned char expValue, unsigned int fracValue) 
        : signBit{(unsigned char)(signBit & 1)}, expValue{expValue}, fracValue{fracValue & fracMask}
    {
        
    }
    
    unsigned char getSignBit() {
        // student code
    }
    
    unsigned char getExpValue() {
        // student code
    }
    
    int getE() {
        // student code
    }

    unsigned int getFracValue() {
        return fracValue;
    }

    // (a) Zero and (b) Equispaced numbers closest to zero
    bool isDenormalized() {
        // student code
    }

    bool isZero() {
        // student code
    }

    // (a) Infinity or (b) NaN
    bool isSpecial() {
        // student code
    }   
    
    bool isInf() {
        // student code
    }
    
    bool isNaN() {
        // student code
    }
    
    float value() {
        // student code       
    }

};


int main()
{
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
    printf("sign=%d, exp=%d (E=%d), frac=%d \n", number.getSignBit(), number.getExpValue(), number.getE(), number.getFracValue());
    printf("Is Denormalized : %d \t (Is Zero : %d) \n", number.isDenormalized(), number.isZero());
    printf("Is Infinity : %d \t (Is Special : %d) \n", number.isInf(), number.isSpecial());
    printf("Is NaN :  %d \t\t (Is Special : %d) ", number.isNaN(), number.isSpecial());

    return 0;
}
