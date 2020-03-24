#include<iostream>
#include<fstream>
using namespace std;
#define PHI 3.141592
int main()
{
	ofstream outFile;
	outFile.open("data.txt");

	double f0, fc, t, fs, dt;
	f0 = 200;
	fc = 1600;
	t = 0;
	fs = 3600;
	dt = 1. / fs;
	
	for (int i = 0; i <= 100; i++, t += dt)
		outFile << t <<" "<< cos(2.* PHI*f0*t)*sin(2.* PHI*fc*t) << endl; //"\t" ÀÔ·ÂÇÏ¸é ÀÚµ¿ Ä­ ³ª´²Áü

	outFile.close();
	return 0;
}