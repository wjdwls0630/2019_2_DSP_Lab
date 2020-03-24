#include<iostream>
#include"complex.h"
using namespace std;

int main()
{
	int m = 10;
	int N = 8;
	int n = m;
	double sum = 0, prod;

	for (int i = 0; i < 8; i++)
	{
		complex Vm = complex(2 * PHI*m*i / N) / sqrt(N);
		complex Vn = complex(-2 * PHI*n*i / N) / sqrt(N);
		prod = Vm.re*Vn.re - Vm.im*Vn.im;
		sum += prod;
	}
	cout << sum << endl;
	return 0;
}