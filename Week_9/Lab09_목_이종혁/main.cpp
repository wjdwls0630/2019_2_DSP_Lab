#include<iostream>
#include<fstream>
#define PI 3.141592
using namespace std;

void DCT_2D(unsigned char**data, double**dct);
void IDCT_2D(double**dct, unsigned char**result_data);

int main()
{
	ifstream InF;//파일 열음
	InF.open("twin_.bmp", ios::binary);
	char*header = new char[54];
	InF.read((char*)header, 54);

	unsigned char** A, **AA, **AAA;
	A = new unsigned char*[256];
	AA = new unsigned char*[256];
	AAA = new unsigned char*[256];

	for (int i = 0; i < 256; i++)
	{
		A[i] = new unsigned char[256];
		AA[i] = new unsigned char[256];
		AAA[i] = new unsigned char[256];

	}
	unsigned char**B;
	unsigned char**G;
	unsigned char**R;
	unsigned char**BGR;
	double **dct1, **dct2, **dct3;
	B = new unsigned char*[256];
	G = new unsigned char*[256];
	R = new unsigned char*[256];
	BGR = new unsigned char*[3 * 256];
	dct1 = new double*[256];
	dct2 = new double*[256];
	dct3 = new double*[256];

	for (int i = 0; i < 256; i++)
	{
		B[i] = new unsigned char[256];
		G[i] = new unsigned char[256];
		R[i] = new unsigned char[256];
		BGR[i] = new unsigned char[3 * 256];
		dct1[i] = new double[256];
		dct2[i] = new double[256];
		dct3[i] = new double[256];

	}//여기까지는 인덱스, 칸 세팅

	for (int i = 0; i < 256; i++)
	{
		InF.read((char*)BGR[i], 3 * 256 * sizeof(char));
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0, jj = 0; j < 256; j++, jj += 3)
		{
			B[i][j] = BGR[i][jj];
			G[i][j] = BGR[i][jj + 1];
			R[i][j] = BGR[i][jj + 2];
		}
	}
	DCT_2D(R, dct1);
	DCT_2D(R, dct2);
	DCT_2D(R, dct3);
	//dct 필터링 시작
	
	//dct1번
	int N = 8;
	int mcrNb = 32;
	int u, v;
	for (int mcr_i = 0; mcr_i < mcrNb; mcr_i++)
	{
		for (int mcr_j = 0; mcr_j < mcrNb; mcr_j++)
		{
			for (int k = 0; k < N; k++)
			{
				u = mcr_i * N + k;
				for (int l = 0; l < N; l++)
				{
					v = mcr_j * N + l;
					if (k > 4 || l > 4)
					{
						dct1[u][v] = 0;
					}
				}
			}
		}
	}
	//2번
	for (int mcr_i = 0; mcr_i < mcrNb; mcr_i++)
	{
		for (int mcr_j = 0; mcr_j < mcrNb; mcr_j++)
		{
			for (int k = 0; k < N; k++)
			{
				u = mcr_i * N + k;
				for (int l = 0; l < N; l++)
				{
					v = mcr_j * N + l;
					if (k > 1 && l > 1)
					{
						dct2[u][v] = 0;
					}
				}
			}
		}
	}
	//3번
	for (int mcr_i = 0; mcr_i < mcrNb; mcr_i++)
	{
		for (int mcr_j = 0; mcr_j < mcrNb; mcr_j++)
		{
			for (int k = 0; k < N; k++)
			{
				u = mcr_i * N + k;
				for (int l = 0; l < N; l++)
				{
					v = mcr_j * N + l;
					if (k < 3 && l < 3)
					{
						dct3[u][v] = 0;
					}
				}
			}
		}
	}
	
	IDCT_2D(dct1, A);
	IDCT_2D(dct2, AA);
	IDCT_2D(dct3, AAA);

	ofstream first("fst.bmp", ios::binary);//1번출력
	first.write((char*)header, 54);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0, jj = 0; j < 256; j++, jj += 3)
		{
			BGR[i][jj] = A[i][j];
			BGR[i][jj + 1] = A[i][j];
			BGR[i][jj + 2] = A[i][j];
		}
	}
	for (int i = 0; i < 256; i++)
	{
		first.write((char*)BGR[i], 3 * 256 * sizeof(char));
	}

	ofstream second("scd.bmp", ios::binary);//2번출력
	second.write((char*)header, 54);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0, jj = 0; j < 256; j++, jj += 3)
		{
			BGR[i][jj] = AA[i][j];
			BGR[i][jj + 1] = AA[i][j];
			BGR[i][jj + 2] = AA[i][j];
		}
	}
	for (int i = 0; i < 256; i++)
	{
		second.write((char*)BGR[i], 3 * 256 * sizeof(char));
	}

	ofstream third("thd.bmp", ios::binary);//3번출력
	third.write((char*)header, 54);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0, jj = 0; j < 256; j++, jj += 3)
		{
			BGR[i][jj] = AAA[i][j];
			BGR[i][jj + 1] = AAA[i][j];
			BGR[i][jj + 2] = AAA[i][j];
		}
	}
	for (int i = 0; i < 256; i++)
	{
		third.write((char*)BGR[i], 3 * 256 * sizeof(char));
	}

	system("pause");
	return 0;
}

void DCT_2D(unsigned char**data, double**dct)
{
	int N = 8;
	int mcrNb = 32;

	double sum = 0;
	int u, v, y, x;
	for (int mcr_i = 0; mcr_i < mcrNb; mcr_i++)
	{
		for (int mcr_j = 0; mcr_j < mcrNb; mcr_j++)
		{
			for (int k = 0; k < N; k++)
			{
				u = mcr_i * N + k;
				for (int l = 0; l < N; l++)
				{
					v = mcr_j * N + l;
					sum = 0;
					for (int i = 0; i < N; i++)
					{
						y = N * mcr_i + i;
						for (int j = 0; j < N; j++)
						{
							x = mcr_j * N + j;
							double th1 = (double)(2.*i + 1)*k*PI / (2.*N);
							double th2 = (double)(2.*j + 1)*l*PI / (2.*N);

							sum += (double)cos(th1)*cos(th2)*data[y][x];
						}
					}
					double ck;
					if (l == 0 && k == 0)   // l 과 k로 정의 
						ck = 1. / 8.;
					else if (l != 0 && k != 0)
						ck = 1. / 4.;
					else
						ck = sqrt(2.) / 8.;
					dct[u][v] = ck * sum;
				}
			}
		}
	}
	ofstream Txt;//텍스트로 결과출력
	Txt.open("DCT_re.txt");
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			Txt << dct[i][j] << "\t";
		}
		Txt << endl;
	}
}
void IDCT_2D(double**dct, unsigned char**result_data)
{
	int N = 8;
	int mcrNb = 32;

	double sum = 0;
	int u, v, y, x;
	for (int mcr_i = 0; mcr_i < mcrNb; mcr_i++)
	{
		for (int mcr_j = 0; mcr_j < mcrNb; mcr_j++)
		{
			for (int i = 0; i < N; i++)
			{
				y = mcr_i * N + i;
				for (int j = 0; j < N; j++)
				{
					sum = 0;
					x = mcr_j * N + j;
					for (int k = 0; k < N; k++)
					{
						u = mcr_i * N + k;
						for (int l = 0; l < N; l++)
						{
							v = mcr_j * N + l;

							double ck;
							if (l == 0 && k == 0)  // l 과 k로 정의 
								ck = 1. / 8;
							else if (l != 0 && k != 0)
								ck = 1. / 4;
							else
								ck = sqrt(2.) / 8.;

							sum += ck * cos((2. * (double)i + 1)*k*PI / 16)*cos((2. * (double)j + 1)*l*PI / 16)*dct[u][v];
						}
					}
					if (sum < 0)
						result_data[y][x] = 0;
					else if (sum > 255)
						result_data[y][x] = 255;
					else
						result_data[y][x] = (int)sum;
				}
			}
		}
	}
}