//
// Created by ParkJungJin on 2019-10-27.
//

#include <iostream>
#include "../complex_jin/complex_jin.hpp"
#include "../matrix_jin/matrix_jin.hpp"
#define N 8
int main(){
    complex_jin* vm;
    complex_jin* vn;
    vm = new complex_jin[N];
    vn = new complex_jin[N];
    complex_jin temp(1, 0);

    //initialize
    for (int i = 0; i < N; i++) {
        temp.setPhase(2*M_PI*(double)i/N);
        temp.makeUnit();
        temp.setMag(sqrt(1/N));
        vm[i] = temp;
    }

    for (int i = 0; i < N; i++) {
        temp.setPhase(2*M_PI*(double)i/N);
        temp.makeUnit();
        temp.setMag(sqrt(1/N));
        temp.conjugate();
        vn[i] = temp;
    }
    matrix_jin<complex_jin> vm_matrix(1, 8, "vm_matrix", vm);
    matrix_jin<complex_jin> vn_matrix(8, 1, "vn_matrix", vn);
    std::cout<<vm_matrix*vn_matrix<<'\n';

    return 1;
}


