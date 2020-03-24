//
// Created by ParkJungJin on 2019-09-29.
//

#include <iostream>
#include <cmath>
#include <fstream>

int main(){
    std::ofstream out("data.txt", std::ios::out);
    double *x_n, *y_n;
    x_n = new double [30];
    y_n = new double [30];
    memset(x_n, 0, 30 * sizeof(double));
    memset(y_n, 0, 30 * sizeof(double));
    for (int i = 0; i <= 30; i++) {
        if (i>=5 && i<25) {
            out<<i<<" "<<cos (M_PI/10*(i-5))<<"\n";
            *(x_n+i) = cos (M_PI/10*(i-5));
        } else{
            out<<i<<" "<<0.<<"\n";
            *(x_n+i) = 0.;
        }
    }
    out.close();
    std::ofstream out1("data_1.txt", std::ios::out);

    for (int i = 0; i<25 ; i++) {
        //y_n[i] = 0. ;
        for (int k = 0; k <=4 ; k++) {
            y_n[i] += x_n[i+k];
        }
        out1<<i<<" "<<0.2*y_n[i]<<"\n";
    }

    for (int j = 0; j <30 ; ++j) {
        std::cout<<y_n[j]<<" ";

    }
    std::cout<<"\n";

    out1.close();
    delete [] x_n;
    delete [] y_n;




}