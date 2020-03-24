#include<iostream>
#include "complex.h"
#include<cmath>
using namespace std;

int main() {

	double a = 3, b = 2, c = 7;
	double det = b * b - 4 * a*c;

	if (det < 0)
	{
		complex x1, x2;
		x1 = complex(b / (2 * a), sqrt(abs(det)) / (2 * a));
		x2 = complex(b / (2 * a), 0. - sqrt(abs(det)) / (2 * a));
		cout << "x1 = " << x1.re << " + (" << x1.im << ")j" << endl;
		cout << "x2 = " << x2.re << " + (" << x2.im << ")j" << endl;
	}
	else if (det = 0)
	{
		double x;
		x = double(b / (2 * a) + sqrt(det) / (2 * a));
		cout << "x = " << x << endl << "x´Â Áß±Ù";
	}
	else
	{
		double x1, x2;
		x1 = double(b / (2 * a) + sqrt(det) / (2 * a));
		x2 = double(b / (2 * a) - sqrt(det) / (2 * a));
		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
	}

	return 0;
}