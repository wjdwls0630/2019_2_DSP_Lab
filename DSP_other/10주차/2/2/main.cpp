#include<iostream>
#include<fstream>
#include"complex.h"
using namespace std;

#define PI 3.141592
void DFT(int, complex*, complex*);
void IDFT(int, complex*, short*);
void Filter(int, complex*, complex*);

int main()
{
	ifstream Infile;//읽어올 것
	Infile.open("noiseMusic.wav", ios::binary);
	char* header = new char[44];
	Infile.read((char*)header, 44);//헤더작성+필요한 값 추출
	unsigned int fs = *(unsigned int*)(header + 24);
	cout << "fs=" << fs << endl;//8000
	int size = (int)((*(unsigned int*)(header + 4))) + 8 - 44;
	cout << "size=" << size << endl;//32000


	short*data = new short[size / 2];
	Infile.read((char*)data, size);//여기까지 header와 data저장
	complex* compdata = new complex[size / 2];

	for (int i = 0; i < size / 2; i++)
	{
		compdata[i] = complex(data[i], 0);
	}

	complex *dft = new complex[fs * 2];//dft
	DFT(fs, compdata, dft);

	ofstream dftfile("dft.txt");
	for (int i = 0; i < 2 * fs; i++)
		dftfile << dft[i].mag() << endl;


	complex*output = new complex[fs * 2];//필터링
	Filter(fs, dft, output);

	short*result = new short[size / 2];//idft
	IDFT(fs, output, result);

	ofstream Filtered("Filted.wav", ios::binary);
	Filtered.write((char*)header, 44);
	Filtered.write((char*)result, 32000);

	return 0;
}

void DFT(int fs, complex* data, complex* dft)
{
	int Fs = 2 * fs;
	cout << "DFT 수행" << endl;
	for (int k = 0; k < Fs; k++)
	{
		for (int n = 0; n < Fs; n++)
		{
			dft[k] += data[n] * complex(cos((-2. * PI*k*n) / (double)Fs), sin((-2. * PI*k*n) / (double)Fs));
		}
	}
}

void IDFT(int fs, complex*output, short*result)
{
	int Fs = 2 * fs;
	complex* x = new complex[Fs];
	cout << "IDFT 수행" << endl;
	for (int n = 0; n < Fs; n++)
	{
		for (int k = 0; k < Fs; k++)
		{
			x[n] += output[k] * complex(cos((2. * PI*k*n) / (double)Fs), sin((2. * PI*k*n) / (double)Fs));
		}
		x[n] = x[n] / (double)(Fs);
	}
	for (int i = 0; i < Fs; i++)
		result[i] = x[i].re;
}
void Filter(int fs, complex* dft, complex* output)
{
	ofstream out_mag;
	out_mag.open("mag.txt");

	complex* H = new complex[2 * fs];
	complex* Z = new complex[2 * fs];

	complex zero1 = complex(2 * PI * 0 / 16000)*0.9;
	complex zero2 = complex(2 * PI * 8000 / 16000)*0.9;
	complex pole1 = complex(2 * PI * 4000 / 16000)*0.9;
	complex pole2 = complex(2 * PI * 12000 / 16000)*0.9;


	for (int k = 0; k < 2 * fs; k++)
	{
		Z[k] = complex(2 * PI*k / (double)(2 * fs));

		H[k] = (Z[k] - zero1)*(Z[k] - zero2) / ((Z[k] - pole1)*(Z[k] - pole2));
	}

	for (int k = 0; k < 2 * fs; k++)
		out_mag << H[k].mag() << endl;
}