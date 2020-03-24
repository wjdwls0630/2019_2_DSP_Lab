#include<iostream>
#include<fstream>
using namespace std;
#define PHI 3.141592
int main()
{
	ofstream outFile;
	outFile.open("data.txt");
	float t, dt, fs, f0, n;
	t = 0;
	fs = 60;
	dt = 1. / fs;
	f0 = 5;
	n = 3;
	int smp_count = (fs / f0)*n;

	for (int i = 0 ; i <=smp_count ; i++,t += dt)
		outFile << t << " " << 2+4*cos(30. * PHI*t-0.2*PHI)+3*sin(40.*PHI*t)+4*cos(60.*PHI*t-PHI/3.) << endl; //"\t" ÀÔ·ÂÇÏ¸é ÀÚµ¿ Ä­ ³ª´²Áü

	outFile.close();
	return 0;
}