#include <iostream>

#include "Math/MathUtils.h"

int main() {

double pointOne[2] = {1,10};
double pointTwo[2] = {3,16};

MathUtils::GCD(15,30,true);
MathUtils::LCM(3, 9,true);
MathUtils::isPrime(47,true);
MathUtils::isPrime(48,true);
MathUtils::slope(1,10,3,16,true);
MathUtils::slope(pointOne,pointTwo,true);

return 0;
}
