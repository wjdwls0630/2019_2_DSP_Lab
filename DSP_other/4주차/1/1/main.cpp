#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
using namespace std;
#define WORD unsigned short
#define DWORD unsigned int
#define PI 3.141592

int main()
{
	//���� �б�
	int header_size = 44;
	char* header = new char[header_size];
	ifstream fff;
	fff.open("LetItGo.wav", ios::binary);
	if (!fff)
	{
		cout << "can't open file" << endl;
		exit(123);
	}
	//44����Ʈ¥�� ������� �б�
	fff.read((char*)header, header_size);
	if (header == NULL)
	{
		cout << "fail to read header" << endl;
		exit(444);
	}
	//����������
	cout << "RIFF    " << header[0] << header[1] << header[2] << header[3] << endl;
	cout << "filesize" <<*(DWORD*)(header+4) << endl;
	cout << "WAVE    " << header[8] << header[9] << header[10] << header[11] << endl;
	cout << "cksize  " << *(DWORD*)(header + 16) << endl;
	cout << "channels" << *(WORD*)(header + 22) << endl;
	cout << "fs      " << *(DWORD*)(header + 24) << endl;
	cout << "bytes/s " << *(DWORD*)(header + 28) << endl;
	cout << "bits/sam" << *(WORD*)(header + 34) << endl;
	cout << "data    " << header[36] << header[37] << header[38] << header[39] << endl;
	cout << "cksize  " << *(DWORD*)(header + 40) << endl; //sub-chunk 2size

	int size_music = (int)((*(DWORD*)(header + 4))) + 8 - 44;
	int monosize = size_music / 2;

	short *data = new short[size_music];//���׷���
	short *left_data = new short[monosize], *right_data = new short[monosize];//���

	fff.read((char*)data, size_music);//���� �о��
	for (int i = 0, ii = 0; i < monosize; i++, ii += 2)
	{
		left_data[i] = data[ii];
		right_data[i] = data[ii + 1];
	}
	//���䳢 ġȯ
	float fs= 48000;
	float dt = 1.0 / fs; //dt�� ���ø����ļ��� ������ ���
	int s = 3;//���۽ð� 3��
	int start_index = fs * s;
	//���� ���� ����
	for (double t = 0; t < 0.9; t += dt)
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 784 * t));
		start_index++;
	}
	for (double t = 0; t < 0.1; t += dt)//�Ҹ�����
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 0 * t));
		start_index++;
	}
	for (double t = 0; t < 0.4; t += dt)
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 659.26 * t));
		start_index++;
	}
	for (double t = 0; t < 0.1; t += dt)//�Ҹ�����
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 0 * t));
		start_index++;
	}
	for (double t = 0; t < 0.4; t += dt)
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 659.26 * t));
		start_index++;
	}
	for (double t = 0; t < 0.1; t += dt)//�Ҹ�����
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 0 * t));
		start_index++;
	}
	for (double t = 0; t < 0.4; t += dt)
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 784 * t));
		start_index++;
	}
	for (double t = 0; t < 0.1; t += dt)//�Ҹ�����
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 0 * t));
		start_index++;
	}
	for (double t = 0; t < 0.4; t += dt)
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 659.26 * t));
		start_index++;
	}
	for (double t = 0; t < 0.1; t += dt)//�Ҹ�����
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 0 * t));
		start_index++;
	}
	for (double t = 0; t < 0.9; t += dt)
	{
		left_data[start_index] = right_data[start_index] = short(20000.0*sin(2 * PI * 523.25 * t));
		start_index++;
	}


	for (int i = 0, ii = 0; i < monosize; i++, ii += 2)//���׷����� ����
	{
		data[ii] = left_data[i];
		data[ii + 1] = right_data[i];
	}

	ofstream TEST("NEWLetItGo.wav", ios::out | ios::binary);
	TEST.write((char*)header, 44);
	TEST.write((char*)data, size_music);
	delete[] header;
	delete[] data;
	delete[] left_data;
	delete[] right_data;
	system("pause");
	return 0;
}