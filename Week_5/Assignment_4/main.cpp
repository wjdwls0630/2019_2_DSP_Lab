//
// Created by ParkJungJin on 2019-10-27.
//

#include <iostream>
#include <cmath>
#include "../complex_jin/complex_jin.hpp"
#include "../matrix_jin/matrix_jin.hpp"

void equation_2_order(complex_jin& x1, complex_jin& x2, double a, double b, double c);
int main(){
    complex_jin x1(0, 0);
    complex_jin x2(0, 0);

    equation_2_order(x1, x2, 3, 2, 7);
    std::cout<<"x1 : "<<x1<<'\t'<<"x2 : "<<x2<<'\n';

    return 1;
}

void equation_2_order(complex_jin& x1, complex_jin& x2, double a, double b, double c){
    double discriminant = pow(b, 2)-4*a*c;
    if (discriminant>0){
        x1.setRe((-b+sqrt(discriminant))/(2*a));
        x1.setIm(0);
        x2.setRe((-b-sqrt(discriminant))/(2*a));
        x2.setIm(0);
    } else if(discriminant==0){
        x1.setRe((-b)/(2*a));
        x1.setIm(0);
        x1 = x2;
    } else {
        x1.setRe((-b)/(2*a));
        x1.setIm(sqrt(-discriminant)/(2*a));
        x2 = x1;
        x2.conjugate();
    }

}


