#include<iostream>
#include<fstream>
#include"complex.h"
using namespace std;
#define PI 3.141592
#define W 64
#define H 64
#define Size 12342
#define HSize 54

int main()
{
	ifstream InF;
	InF.open("twin_noise_64.bmp", ios::binary);
	char*header = new char[HSize];
	InF.read((char*)header, 54);
	
	unsigned char** A;
	A = new unsigned char*[64];
	for (int i = 0; i < 64; i++)
	{
		A[i] = new unsigned char[64];
	}

	unsigned char**B;
	unsigned char**G;
	unsigned char**R;
	unsigned char**BGR;
	complex **dft;
	B = new unsigned char*[64];
	G = new unsigned char*[64];
	R = new unsigned char*[64];
	BGR = new unsigned char*[3 * 64];
	dft = new complex*[64];
	for (int i = 0; i < 64; i++)
	{
		B[i] = new unsigned char[64];
		G[i] = new unsigned char[64];
		R[i] = new unsigned char[64];
		BGR[i] = new unsigned char[3 * 64];
		dft[i] = new complex[64];
	}//dft값 초기화
	for (int i = 0; i < 64; i++) 
	{
		for (int j = 0; j < 64; j++)
		{
			dft[i][j] = 0;
		}
	}

	for (int i = 0; i < 64; i++)
	{
		InF.read((char*)BGR[i], 3 * 64 * sizeof(char));
	}
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0, jj=0; j < 64; j++,jj+=3)
		{
			B[i][j] = BGR[i][jj];
			G[i][j] = BGR[i][jj+1];
			R[i][j] = BGR[i][jj+2];
		}
	}
	for (int v = 0; v < 64; v++) //DFT
	{
		for (int u = 0; u < 64; u++) 
		{
			for (int y = 0; y < 64; y++) 
			{
				for (int x = 0; x < 64; x++)
				{
					dft[v][u] += complex(R[y][x], 0)*complex(-2.*PI*(((double)u*x / W) + ((double)v*y / H)));
				}
			}
		}
	}
	//노이즈값 제거
	for (int i = 10; i < 30; i++)
	{
		for (int j = 0; j < 64 ; j++)
		{
			if (j > 10 && j < 30)
				dft[i][j] = complex(0, 0);
		}
	}
	for (int i = 30; i< 50; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			if (j > 30 && j < 50)
				dft[i][j] = complex(0, 0);
		}
	}
	ofstream please;//텍스트로 결과출력
	please.open("pease.txt");

	for (int i = 0; i < 64; i++)
	{
		for(int j = 0; j < 64;j++)
		{
			please << dft[i][j].mag() <<"\t";
		}
		please << endl;
	}

	complex** idft;
	idft = new complex*[64];
	for (int i = 0; i < 64; i++)
	{
		idft[i] = new complex[64];
	}

	for (int v = 0; v < 64; v++)//IDFT
	{
		for (int u = 0; u < 64; u++)
		{
			for (int y = 0; y < 64; y++)
			{
				for (int x = 0; x < 64; x++)
				{
					idft[v][u] += dft[y][x] * complex(2.*PI*(((double)u*x / W) + ((double)v*y / H)));

				}
			}
			idft[v][u] = idft[v][u] / (64 * 64);
			R[v][u] = idft[v][u].re;
		}
	}
	for (int i = 0; i < W; i++) 
	{
		for (int j = 0, jj = 0; j < H; j++, jj += 3) 
		{
			BGR[i][jj] = R[i][j];
			BGR[i][jj + 1] = R[i][j];
			BGR[i][jj + 2] = R[i][j];
		}
	}
	ofstream TEST("endgame.bmp", ios::binary);
	TEST.write((char*)header, 54);


	for (int i = 0; i < H; i++) {
		TEST.write((char*)BGR[i], 3 * W);
	}

	return 0;
}