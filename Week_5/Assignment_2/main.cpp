//
// Created by ParkJungJin on 2019-10-27.
//

#include <iostream>
#include "../complex_jin/complex_jin.hpp"

inline void getXY(double &x, double &y, double a, double b, double e, double c, double d, double f){
    x = (e*d-f*b)/(a*d-b*c);
    y = (a*f-c*e)/(a*d-b*c);
}

inline void getXY_complex(complex_jin &x, complex_jin &y, complex_jin &a, complex_jin &b, complex_jin &e, complex_jin &c, complex_jin &d, complex_jin &f){
    x = (e*d-f*b)/(a*d-b*c);
    y = (a*f-c*e)/(a*d-b*c);
}

int main(){
    complex_jin x(0, 0);
    complex_jin y(0, 0);
    complex_jin a(2, 1), b(3, -2), e(2, 4), c(3, 0), d(-3, 5), f(1, 1);
    getXY_complex(x, y, a, b, e, c, d, f);
    std::cout<<"x : "<<x<<'\t'<<"y : "<<y<<'\n';

    return 1;
}

