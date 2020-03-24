#include<iostream>
#include<fstream>
#include"complex.h"
using namespace std;

#define PI 3.141592
#define uchar unsigned char
#define H 256
#define W 256
void FFT2Radix(double* Xr, double* Xi, double* Yr, double* Yi, int nN, bool bInverse);
void FFT2D(uchar** img, double** OutputReal, double** OutputImag, int nW, int nH);
void FFT2Dinverse(double** InputReal, double** InputImag, uchar** OutputDouble, int nW, int nH);
void DNormalize2D(double **p1, uchar **p2, int nW, int nH);

int main() {
	ifstream nzopen;
	nzopen.open("twin_noise.bmp", ios::binary);
	char* header;
	uchar** RGB;
	uchar** R;
	uchar** Rswch;
	complex** fft;
	double** mag;
	double** fftRe;
	double** fftIm;
	uchar** R_;
	uchar** RGB_;
	header = new char[54];
	RGB = new uchar*[H];
	R = new uchar*[H];
	Rswch = new uchar*[H];
	fft = new complex*[H];
	mag = new double*[H];
	fftRe = new double*[H];
	fftIm = new double*[H];
	R_ = new uchar*[H];
	RGB_ = new uchar*[H];
	for (int i = 0; i < H; i++) {
		RGB[i] = new uchar[3 * W];
		R[i] = new uchar[W];
		Rswch[i] = new uchar[W];
		fft[i] = new complex[W];
		mag[i] = new double[W];
		fftRe[i] = new double[W];
		fftIm[i] = new double[W];
		R_[i] = new uchar[W];
		RGB_[i] = new uchar[3 * W];
	}

	nzopen.read((char*)header, 54);
	for (int i = 0; i < H; i++)
		nzopen.read((char*)RGB[i], 3 * W);

	for (int i = 0; i < H; i++) {
		for (int j = 0, jj = 0; j < W; j++, jj += 3) {
			R[i][j] = RGB[i][jj];
		}
	}

	FFT2D(R, fftRe, fftIm, W, H);//R값을 fftRe, fftIm값과 관련지어줌

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			fft[i][j] = complex(fftRe[i][j], fftIm[i][j]);
			mag[i][j] = 10 * log(fft[i][j].mag() + 1);
		}
	}

	DNormalize2D(mag, R_, W, H);//R과 관련된 값을 R_로 변경

	for (int i = 0; i < H; i++) {
		for (int j = 0, jj = 0; j < W; j++, jj += 3) {

			RGB_[i][jj] = R_[i][j];
			RGB_[i][jj + 1] = R_[i][j];
			RGB_[i][jj + 2] = R_[i][j];
		}
	}
	//재정렬, R_값을 Rswch에 입력하고 Rswch값을 RGB_에 입력
	
	for(int i=0;i<H;i++)
		for (int j = 0; j < W; j++)//원본기준으로 할 예정
		{
			if (i < 128 && j < 128)//왼위
				Rswch[i + 128][j + 128] = R_[i][j];
			else if (i >= 128 && j >= 128)//오아래
				Rswch[i - 128][j - 128] = R_[i][j];
			else if (i < 128 && j >= 128)//오위
				Rswch[i + 128][j - 128] = R_[i][j];
			else//왼아래
				Rswch[i - 128][j + 128] = R_[i][j];
		}

	for (int i = 0; i < H; i++) {
		for (int j = 0, jj = 0; j < W; j++, jj += 3) {

			RGB_[i][jj] = Rswch[i][j];
			RGB_[i][jj + 1] = Rswch[i][j];
			RGB_[i][jj + 2] = Rswch[i][j];
		}
	}

	ofstream Outfile11;
	Outfile11.open("노이즈전환버전.bmp", ios::binary);
	Outfile11.write((char*)header, 54);
	for (int i = 0; i < H; i++)
		Outfile11.write((char*)RGB_[i], 3 * W);

	//필터
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if ((i > 22 && i < 28) || (i > 226 && i < 230) || (j > 39 && j < 45) || (j > 212 && j < 220))
			{
				R_[i][j] = 0;
				fftRe[i][j] = 0;
				fftIm[i][j] = 0;
			}
		}
	}
	
	FFT2Dinverse(fftRe, fftIm, R_, W, H);//출력까지, R_에다가 변형된 값을 넣어줘야함

	for (int i = 0; i < H; i++) {
		for (int j = 0, jj = 0; j < W; j++, jj += 3) {

			RGB_[i][jj] = R_[i][j];
			RGB_[i][jj + 1] = R_[i][j];
			RGB_[i][jj + 2] = R_[i][j];
		}
	}

	ofstream Outfile2;
	Outfile2.open("복원영상.bmp", ios::binary);
	Outfile2.write((char*)header, 54);
	for (int i = 0; i < H; i++)
		Outfile2.write((char*)RGB_[i], 3 * W);

	system("pause");
	return 0;
}


void FFT2Radix(double* Xr, double* Xi, double* Yr, double* Yi, int nN, bool bInverse)
{
	//N =8
	double T, Wr, Wi;

	if (nN <= 1) return;

	for (int i = 0; i < nN; i++) {
		Yr[i] = Xr[i];
		Yi[i] = Xi[i];
	}

	int j = 0, k = 0;
	for (int i = 1; i < (nN - 1); i++) {   // (1) i = 1, j = 0, k = 0 (2) i =2, (3) i=3 (4) i =4,j=6 (5)i = 5, j =4
		k = nN / 2; //  // k = 4  (2) k=4 (3) k=4,j=2 (4) k = 4 (5) k=4
		while (k <= j) {// (1) k=4, j=0 (x) (2) j =4, k=4 (o) (3) x (4) (o) (5) (o)
			j = j - k;  // (2) j =0 (4) j = 2  (5) j = 0 
			k = k / 2;  // (2)k =2  (4) k = 2 *5) k = 2
		}
		j = j + k; //(1) j = 4, (2) j = 2 (3) j=6, (4) j = 4, 
		if (i < j) {  //(2) j =2 k=2     (3) i = 3, j=6   (4) j =4, i = 4
			T = Yr[j]; // (1) i=1 j =4 swap, (3) 3, 6 swap 
			Yr[j] = Yr[i];
			Yr[i] = T; // j = 4, i = 1 swap

			T = Yi[j]; // j = 4, i = 1 swap
			Yi[j] = Yi[i];
			Yi[i] = T;// j = 4, i = 1 swap  (1,4)
		}
	}

	double Tr, Ti;
	int iter, j2, pos;
	k = nN >> 1;  // (0) k= 1000<2>  k = 100<2> =4 
	iter = 1;
	while (k > 0) {
		j = 0;
		j2 = 0;

		for (int i = 0; i < nN >> 1; i++) {  // 0 ~i ~4 (1) i =0, (2) i=1 j=2, k =4 (3) i=2, j =4 (4) j =6, 
			Wr = cos(2.*PI*(j2*k) / nN);  // Wk(re)
			if (bInverse == 0)
				Wi = -sin(2.*PI*(j2*k) / nN); //Wk(im) 
			else
				Wi = sin(2.*PI*(j2*k) / nN);

			pos = j + (1 << (iter - 1)); // (1) pos = 1 = 1 (2)pos 2+1=3 (3) pos =5 j =4 (4) j =6, pos=7

			Tr = Yr[pos] * Wr - Yi[pos] * Wi; // Y[2] 
			Ti = Yr[pos] * Wi + Yi[pos] * Wr;

			Yr[pos] = Yr[j] - Tr; // (1) Y[pos=1], j = 0 (2) y[2] y[3]: X[2],X[6], (3)y[4],[5] (4) y[6],[7]
			Yi[pos] = Yi[j] - Ti;

			Yr[j] += Tr;
			Yi[j] += Ti;

			j += 1 << iter; // j= 0+ 10<2>= 2 (2) j = 2+ 2 = 4 =100(3) j=1000=6 , j =12  
			if (j >= nN) j = ++j2; //(1) x (2) (3) o j = 1, j2=1
		}

		k >>= 1; // (1) k = k>>1; 100=4 :: 10=2
		iter++; // (1) iter=2 
	}
	if (bInverse) {
		for (int i = 0; i < nN; i++) {
			Yr[i] /= nN;
			Yi[i] /= nN;
		}
	}
}

void FFT2D(uchar** img, double** OutputReal, double** OutputImag, int nW, int nH)
{
	int x, y;
	double *dRealX, *dImagX;
	double *dRealY, *dImagY;
	dRealX = new double[nW];
	dImagX = new double[nW];
	dRealY = new double[nW];
	dImagY = new double[nW];

	for (y = 0; y < nH; y++) {
		for (x = 0; x < nW; x++) {
			dRealX[x] = img[y][x];
			dImagX[x] = 0.;
		}
		FFT2Radix(dRealX, dImagX, dRealY, dImagY, nW, false);
		for (x = 0; x < nW; x++) {
			OutputReal[y][x] = dRealY[x];
			OutputImag[y][x] = dImagY[x];
		}
	}
	delete[] dRealX;
	delete[] dImagX;
	delete[] dRealY;
	delete[] dImagY;

	dRealX = new double[nH];
	dImagX = new double[nH];
	dRealY = new double[nH];
	dImagY = new double[nH];
	for (x = 0; x < nW; x++) {
		for (y = 0; y < nH; y++) {
			dRealX[y] = OutputReal[y][x];
			dImagX[y] = OutputImag[y][x];
		}
		FFT2Radix(dRealX, dImagX, dRealY, dImagY, nH, false);
		for (y = 0; y < nH; y++) {
			OutputReal[y][x] = dRealY[y];
			OutputImag[y][x] = dImagY[y];
		}
	}
	delete[] dRealX;
	delete[] dImagX;
	delete[] dRealY;
	delete[] dImagY;
}

void FFT2Dinverse(double** InputReal, double** InputImag, uchar** OutputDouble, int nW, int nH)
{
	int x, y;
	double *dRealX, *dImagX;
	double *dRealY, *dImagY;
	double** OutputReal, **OutputImag;

	OutputReal = new double*[nH];
	OutputImag = new double*[nH];
	for (int i = 0; i < nH; i++) {
		OutputReal[i] = new double[nW];
		OutputImag[i] = new double[nW];
	}
	dRealX = new double[nW];
	dImagX = new double[nW];
	dRealY = new double[nW];
	dImagY = new double[nW];
	for (y = 0; y < nH; y++) {
		for (x = 0; x < nW; x++) {
			dRealX[x] = InputReal[y][x];
			dImagX[x] = InputImag[y][x];
		}
		FFT2Radix(dRealX, dImagX, dRealY, dImagY, nW, true);
		for (x = 0; x < nW; x++) {
			OutputReal[y][x] = dRealY[x];
			OutputImag[y][x] = dImagY[x];
		}
	}
	delete[] dRealX;
	delete[] dImagX;
	delete[] dRealY;
	delete[] dImagY;

	dRealX = new double[nH];
	dImagX = new double[nH];
	dRealY = new double[nH];
	dImagY = new double[nH];
	for (x = 0; x < nW; x++) {
		for (y = 0; y < nH; y++) {
			dRealX[y] = OutputReal[y][x];
			dImagX[y] = OutputImag[y][x];
		}
		FFT2Radix(dRealX, dImagX, dRealY, dImagY, nH, true);
		for (y = 0; y < nH; y++) {
			OutputReal[y][x] = dRealY[y];
			OutputImag[y][x] = dImagY[y];
		}
	}
	delete[] dRealX;
	delete[] dImagX;
	delete[] dRealY;
	delete[] dImagY;

	for (y = 0; y < nH; y++) {
		for (x = 0; x < nW; x++) {
			OutputDouble[y][x] = OutputReal[y][x];
		}
	}
	for (int i = 0; i < nH; i++) {
		delete[] OutputReal[i];
		delete[] OutputImag[i];
	}
	delete[] OutputReal;
	delete[] OutputImag;
}
void DNormalize2D(double **p1, uchar **p2, int nW, int nH)//p2에 값 입력, p1에 mag입력
{
	int x, y;
	double min = 9999.;
	double max = -9999.;
	double val;
	for (y = 0; y < nH; y++)
	{
		for (x = 0; x < nW; x++)
		{
			val = p1[y][x];
			if (val > max) max = val;
			if (val < min) min = val;
		}
	}
	if (max == min)
	{
		for (y = 0; y < nH; y++)
		{
			for (x = 0; x < nW; x++)
				p2[y][x] = 0;
		}
		return;
	}
	double dfactor = 255 / (max - min);
	for (y = 0; y < nH; y++)
	{
		for (x = 0; x < nW; x++)
			p2[y][x] = (unsigned char)((p1[y][x] - min)*dfactor);
	}
}