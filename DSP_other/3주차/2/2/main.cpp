#include<iostream>
#include"complex.h"
using namespace std;

int main()
{
	complex a, b, c, d, e, f, x, y;
	a.re = 2; a.im = 1;
	b.re = 3; b.im = -2;
	c.re = 3; c.im = 0;
	d.re = -3; d.im = 5;
	e.re = 2; e.im = 4;
	f.re = 1; f.im = 1;

	x = (e*d - f * b) / (a*d - b * c);
	y = (a*f - c * e) / (a*d) / (b*c);

	cout << "(2+j)x+(3-2j)y=2+4j, 3x-(3-5j)y=1+j ÀÇ ÇØ" << endl;
	cout << "x=" << x.re << "+(" << x.im << "j), y="<<y.re<< "+(" << y.im << "j)";

	return 0;
}