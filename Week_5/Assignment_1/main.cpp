//
// Created by ParkJungJin on 2019-10-27.
//

#include <iostream>

inline void getXY(double &x, double &y, double a, double b, double e, double c, double d, double f){
    x = (e*d-f*b)/(a*d-b*c);
    y = (a*f-c*e)/(a*d-b*c);
}
int main(){
    double x = 0, y = 0;
    getXY(x, y, 2, 3, 1, 3, -3, 9);
    std::cout<<"x : "<<x<<'\t'<<"y : "<<y<<'\n';
    return 1;
}


