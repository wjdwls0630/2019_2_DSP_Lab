#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	int x[5] = { 1, 1, 1, 1, 1 };
	int h1[7] = { 1, 0, 0, 0, 0, 0, 1 };
	int h2[5] = { 1, 2, 3, 2, 1 };
	int result1[9];
	int result2[15];
	int stor=0;
	//�ʱ�ȭ
	for (int i=0; i < 9; i++)
	{
		result1[i] = 0;
	}
	for (int i=0; i < 15; i++)
	{
		result2[i] = 0;
	}

	//x��h2���� �������
	for (int n = 0; n < 9; n++)//result1�� �� ����
	{
		for (int k = 0; k < 5; k++)
		{
			if (n - k < 0)
				stor += 0;
			else if (n - k > 4)
				stor += 0;
			else
				stor += x[k] * h2[n - k];
		}
		result1[n] = stor;
		stor = 0;
	}
	for (int r = 0; r < 9; r++)
	{
		cout << r << " " << result1[r] << endl;
	}//������� �� �۵���
	stor = 0;
	//������ �������
	for (int n = 0; n < 15; n++)//result2�� �� ����
	{
		for (int k = 0; k <9 ; k++)
		{
			if (n - k < 0)
				stor += 0;
			else if (n - k > 6)
				stor += 0;
			else
				stor += result1[k] * h1[n - k];
		}
		result2[n] = stor;
		stor = 0;
	}
	//��� �� ���� ����
	ofstream conv("out.txt");

	for (int r = 0; r < 15; r++)
	{
		cout << r << " " << result2[r] << endl;
		conv << r << " " << result2[r] << endl;
	}
	system("pause");
	return 0;
}