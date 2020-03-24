#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

int main()
{
	double cosf[10];
	double expf[10];
	double result[19];
	double stor = 0;
	//초기화
	for (int i = 0; i < 10; i++)
	{
		cosf[i] = cos(i);
		expf[i] = exp(-1*i);
		result[i] = 0;
	}
	
	//컨벌루션
	for (int n = 0; n < 19; n++)//result에 값 대입
	{
		for (int k = 0; k < 10; k++)
		{
			if (n - k < 0)
				stor += 0;
			else if (n - k > 9)
				stor += 0;
			else
				stor += cosf[k] * expf[n - k];
		}
		result[n] = stor;
		stor = 0;
	}
	
	//출력 및 파일 생성
	ofstream conv("out.txt");

	for (int r = 0; r < 19; r++)
	{
		cout << r << " " << result[r] << endl;
		conv << r << " " << result[r] << endl;
	}
	system("pause");
	return 0;
}