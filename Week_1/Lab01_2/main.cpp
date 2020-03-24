//
// Created by ParkJungJin on 2019-09-21.
//

#include <iostream>
#include <fstream>
#include <cmath>

int main(){
    std::ofstream outFile;
    outFile.open("data.txt", std::ios::out);
    float t = 0, fs = 500, dt = 1./fs; //time, sampling freq more than 2 times, sampling period
    int f0 = 50, n = 3, smp_cnt; //basic freq, number of period, number of signal sample

    smp_cnt = (fs/f0)*n;
    for (int i = 0; i <= smp_cnt ; i++, t+=dt) {
        outFile<<t<< " "<<2*cos(2.*M_PI*50*t+M_PI_2)+cos(2*M_PI*150*t)<<'\n';
    }

    outFile.close();
    return 0;
}