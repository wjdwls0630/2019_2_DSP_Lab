//
// Created by ParkJungJin on 2019-09-21.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

int gcd(int a, int b); // Greatest common divisor
int lcm(int a, int b); // Least common Multiple
float signal(float &t, int* freqs); // signal

int main(){
    std::ofstream outFile;
    outFile.open("data.txt", std::ios::out);

    int f_1 = 15, f_2 =20, f_3 = 30; //frequencies of components
    int *freqs = new int [3] {f_1, f_2, f_3};

    float t = 0 ; // start time

    //sampling freq must be more 2 times of maximum freq
    float fs = 5.*float(*(std::max_element(freqs, freqs + 3))), dt = 1./fs; //sampling freq, sampling period

    //if frequencies is integer, base freq is GCD of frequencies,
    //if frequencies is not integer, we sholuld get base freq by period, LCM  of period will be base band period

    int f0 = gcd(gcd(freqs[0], freqs[1]), freqs[2]);// basic freq
    int n = 3, smp_cnt; // number of period, number of signal sample

    smp_cnt = (fs/f0)*n;

    for (int i = 0; i <= smp_cnt ; i++, t+=dt) {
        outFile<<t<< " "<<signal(t, freqs)<<'\n';
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

float signal(float &t, int* freqs){
    return 2+4*cos(2.*M_PI*(*freqs)*t-(M_PI/5))+3*sin(2.*M_PI*(*(freqs+1)*t))+4*cos(2.*M_PI*(*(freqs+2))*t-(M_PI/3));
}