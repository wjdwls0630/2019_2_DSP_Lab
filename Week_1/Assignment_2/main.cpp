//
// Created by ParkJungJin on 2019-09-21.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

int gcd(int a, int b); // Greatest common divisor
int lcm(int a, int b); // Least common Multiple
float signal(float &t); // signal

int main(){
    std::ofstream outFile;
    outFile.open("data.txt", std::ios::out);

    //in this case , modulation, we use the formula
    //sinA * cosB = 0.5(sin(A+B)+ sin(A-B)
    //so signal can be presented by 0.5(sin(2*pi*1800)+sin(2*pi*1400))

    int f_0 = 1800, f_c =1400; //base band freq, carrier freq
    int *freqs = new int [2] {f_0, f_c};

    float t = 0 ; // start time

    //sampling freq must be more 2 times of maximum freq
    float fs = 3.*float(*(std::max_element(freqs, freqs + 2))), dt = 1./fs; //sampling freq, sampling period

    //if frequencies is integer, base freq is GCD of frequencies,
    //if frequencies is not integer, we sholuld get base freq by period, LCM  of period will be base band period

    int f0 = gcd(freqs[0], freqs[1]); // basic freq
    int n = 3, smp_cnt; // number of period, number of signal sample

    smp_cnt = (fs/f0)*n;

    for (int i = 0; i <= smp_cnt ; i++, t+=dt) {
        outFile<<t<< " "<<signal(t)<<'\n';
    }
    
    outFile.close();
    delete [] freqs; //de-allocate memory

    return 0;
}

int gcd(int a, int b){
    while(b!=0){
        int r = a%b;
        a= b;
        b= r;
    }
    return a;
}

int lcm(int a, int b){
    return a * b / gcd(a,b);
}

float signal(float &t){
    return cos(2.*M_PI*(200)*t)*sin(2.*M_PI*(1600)*t);
}