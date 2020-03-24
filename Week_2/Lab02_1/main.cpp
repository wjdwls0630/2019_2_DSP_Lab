//
// Created by ParkJungJin on 2019-10-02.
//

#include <iostream>
#include "../matrix_jin/matrix_jin.hpp"
#include "../matrix_jin/Error/matrix_out_of_range.hpp"

int main(){
    int m, n, p;
    m=2, n=3, p=2;

    int *a, *b;
    a = new int[m*n]{2, 3, 4, 5, 6, 7};
    b = new int [n*p]{2, 3, 5, 7, 1, 3};



    Matrix_Jin<int> A(m, n, "A", a), B(n, p, "B", b), C(m, p);

    C = A*B;
    C.setName("C");
    C.showMatrix();
    A.showMatrix();
    A.swapRow(0, 1);
    A.showMatrix();
    A.swapCol(0, 2);
    A.showMatrix();
}

