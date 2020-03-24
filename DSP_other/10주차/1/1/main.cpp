#include<iostream>
#include<fstream>
#include"complex.h"
using namespace std;

#define PI 3.141592
void DFT(int, complex*, complex*);
void IDFT(int, complex*, short*);
void DoDirichlet(int, int, complex*, complex*);

int main()
{
	ifstream Infile;//읽어올 것
	Infile.open("noiseMusic.wav", ios::binary);
	char* header = new char[44];
	Infile.read((char*)header, 44);//헤더작성+필요한 값 추출
	unsigned int fs= *(unsigned int*)(header + 24);
	cout << "fs=" << fs << endl;//8000
	int size = (int)((*(unsigned int*)(header + 4))) + 8 - 44;
	cout << "size=" << size << endl;//32000
	

	short*data = new short[size/2];
	Infile.read((char*)data, size);//여기까지 header와 data저장
	complex* compdata=new complex[size/2];

	for (int i = 0; i < size/2; i++)
	{
		compdata[i] = complex(data[i], 0);
	}

	complex *dft = new complex[fs*2];//dft
	DFT(fs, compdata, dft);

	ofstream dftfile("dft.txt");
	for (int i = 0; i < 2 * fs; i++)
		dftfile << dft[i].mag() << endl;


	complex*output = new complex[fs * 2];//디리디리
	int L = (int)((double)fs/1000);//L=8
	DoDirichlet(L, fs, dft, output);
	
	short*result = new short[size/2];//idft
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
	complex* x=new complex[Fs];
	cout << "IDFT 수행" << endl;
	for (int n = 0; n < Fs; n++)
	{
		for (int k = 0; k < Fs; k++)
		{
			x[n] += output[k] * complex(cos((2. * PI*k*n) / (double)Fs), sin((2. * PI*k*n) / (double)Fs));
		}
		x[n] = x[n]/(double)(Fs);
	}
	for (int i = 0; i < Fs; i++)
		result[i] = x[i].re;
}

void DoDirichlet(int L, int fs, complex* dft, complex* output)
{
	cout << "디리클레 수행" << endl;
	complex *H = new complex[2*fs];
	complex upper, bottom;
	double lim = 8.;
	for (int k = 0; k < 2*fs; k++) 
	{
		bottom = complex(sin(2.*PI*k / (double)(4.*fs)), 0);
		if (bottom.mag() == 0.0) 
		{
			H[k] = complex(cos(-2.*PI*k*((L - 1) / 2.) / (double)(2*fs)),
				sin(-2.*PI*k*((L - 1) / 2.) / (double)(2*fs)))*lim;
		}
		else 
		{
			upper = complex(sin(2.*PI*k*L / (double)(4.*fs)), 0.0);
			H[k] = upper / bottom * complex(cos(-2.*PI*k*((L - 1) / 2.) / (double)(2*fs)),
				sin(-2.*PI*k*((L - 1) / 2.) / (double)(2*fs)));
		}
	}
	ofstream Hfile("Hfil.txt");
	for (int i = 0; i < 2 * fs; i++)
		Hfile << H[i].mag() << endl;
	for (int k = 0; k < 2*fs; k++)
	{
		output[k] = dft[k]* H[k]/5.;//증폭되는효과발생하므로 사이즈를 줄여줘도 좋음
	}
}
