#include<iostream>
#include<fstream>
#include"complex.h"
using namespace std;
#define PI 3.141592
#define WORD unsigned short
#define DWORD unsigned int

int main()
{
	ifstream Infile;//읽어올 것
	Infile.open("MixA.wav", ios::binary);
	char* header = new char[44];
	Infile.read((char*)header, 44);//문법적인 사항으로 기억하자

	cout << "RIFF     " << header[0] << header[1] << header[2] << header[3] << endl;
	cout << "filesize " << *(DWORD*)(header + 4) << endl;//wav 파일의 특성, 실제는 +8해줘야 함
	cout << "WAVE     " << header[8] << header[9] << header[10] << header[11] << endl;
	cout << "cksize   " << *(DWORD*)(header + 16) << endl;
	cout << "channels " << *(WORD*)(header + 22) << endl;//중간에 불필요한 부분 삭제돼있음(1이면 모노 2면 스테레오)
	cout << "fs       " << *(DWORD*)(header + 24) << endl;//샘플링 주파수 8000
	cout << "bytes/s  " << *(DWORD*)(header + 28) << endl;
	cout << "bits/sam " << *(WORD*)(header + 34) << endl;//샘플당 바이트, 16비트=2바이트->short형 선언이 유리
	cout << "data     " << header[36] << header[37] << header[38] << header[39] << endl;
	cout << "cksize   " << *(DWORD*)(header + 40) << endl; //sub-chunk 2size
	
	short* data = new short[16000]; //샘플의 수만큼 크기를 할당하고 하나당 2바이트이므로 short형으로 선언
	Infile.read((char*)data, 16000*sizeof(short)); //char*는 문법적인 내용 반드시 저렇게 써야함, 콤마뒤에는 전체용량
	//음악파일의 모든 정보 "data"에 저장.

	ofstream OFk, OFm, OFph;
	OFk.open("k.txt");
	OFm.open("mag.txt");
	OFph.open("phase.txt");

	complex* x = new complex[16000];
	for (int n=0;n<16000;n++)
	x[n] = complex(data[n], 0);

	complex* X = new complex[16000];
	for (int k = 0; k < 16000; k++)
	{
		for (int n = 0; n < 16000; n++)
		{
			X[k] += complex(data[n],0)*complex(cos((-2. * PI*k*n) / (double)16000), sin((-2. * PI*k*n) / (double)16000));
		}
	}
	for (int k = 0; k < 16000; k++)
	{
		OFk << (double)8000/16000*k << endl;//인덱스에서 주파수로 변경
		OFm << X[k].mag() << endl;
		OFph << X[k].phase() << endl;
	}
	OFk.close();
	OFm.close();
	OFph.close();

	for (int k = 2000; k < 16000; k++)//필터를 통해 특정 주파수의 크기를 0으로 만듬
	{
		X[k] = complex(0, 0);
	}
	for (int n = 0; n < 16000; n++)
	{
		for (int k = 0; k < 16000; k++)
		{
			x[n] += X[k] * complex(cos((2. * PI*k*n) / (double)16000), sin((2. * PI*k*n) / (double)16000));
		}
		x[n] = x[n] / 16000;
	}
	short*data_ = new short[16000];
	for (int i = 0; i < 16000; i++)
	{
		data_[i] = x[i].re;
	}

	ofstream TEST("NEWA.wav", ios::binary);
	TEST.write((char*)header, 44);
	TEST.write((char*)data_, 32000);

	return 0;
}