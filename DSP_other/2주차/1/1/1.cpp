#include<iostream>
using namespace std;
#define PHI 3.141592

float elementA(int, int);
float elementB(int, int);
void changeR(float*, int );
void changeC(float*, int );
int matrixMult(float*, float*, float*, int);

int main()
{
	float *A, *B, *C;
	int n=8; //정사각행렬을 위한 크기 설정

	A = new float[n*n];	B = new float[n*n];	C= new float[n*n]; //동적할당으로 행렬 생성
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[n * i + j] = elementA(i, j);// A의 원소 대입
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			B[n * i + j] = elementB(i, j);// B의 원소 대입

		}
	}
	changeR(A, n);
	changeC(B, n);
	matrixMult(A, B, C, n);
	
	cout << "A" << endl;
	for (int ha = 0; ha < n; ha++)//A출력
	{
		for (int yu = 0; yu < n; yu++)
		{
			cout << A[n*ha + yu] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "B" << endl;
	for (int ha = 0; ha < n; ha++)//B출력
	{
		for (int yu = 0; yu < n; yu++)
		{
			cout << B[n*ha + yu] << "  ";
		}
		cout << endl;
	}
	cout << endl; 
	
	cout << "C" << endl;
	for (int ha = 0; ha < n; ha++)//C출력
	{
		for (int yu = 0; yu < n; yu++)
		{
			cout << C[n*ha + yu] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	return 0;
}

float elementA(int x, int y)
{
	float result=0;

	if (x == 0)
		result = cos(PHI*(2 * y + 1)*x / 16) / (2. * sqrt(2));
	else if (1 <= x && x <= 7)
		result = cos(PHI*(2 * y + 1)*x / 16) / 2.;
	else
		cout << "error in eleA";
	return result;
}

float elementB(int i, int j)
{
	float result=0;

	if (j == 0)
		result = cos(PHI*(2 * i + 1)*j / 16) / (2. * sqrt(2));
	else if (1 <= j && j <= 7)
		result = cos(PHI*(2 * i + 1)*j / 16) / 2.;
	else
		cout << "error in eleB";
	return result;
}
void changeR(float *A, int n)
{
	float*RowM;
	RowM = new float[n];
	for (int i = 0; i < n; i++)//RowM에 row2 복사
	{
		RowM[i] = A[n * 2 + i];
	}
	for (int i = 0; i < n; i++)//row2에 row5 복사
	{
		A[n * 2 + i]= A[n * 5 + i];
	}
	for (int i = 0; i < n; i++)//row5에 RowM 복사
	{
		A[n * 5 + i]=RowM[i];
	}
}

void changeC(float *A, int n)
{
	float*ColM;
	ColM = new float[n];
	for (int i = 0; i < n; i++)//ColM에 col3 복사
	{
		ColM[i] = A[n * i + 3];
	}
	for (int i = 0; i < n; i++)//col3에 col4 복사
	{
		A[n * i + 3] = A[n * i + 4];
	}
	for (int i = 0; i < n; i++)//col4에 ColM 복사
	{
		A[n * i + 4] = ColM[i];
	}
}


int matrixMult(float *A, float *B, float *C, int n)
{
	float dum;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			dum = 0;
			for (int k = 0; k < n; k++)
			{
				dum += A[i*n + k] * B[k*n + j];
			}
			C[i*n + j] = dum;
		}
	}
	return 0;
}