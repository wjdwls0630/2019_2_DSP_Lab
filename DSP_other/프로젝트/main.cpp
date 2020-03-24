#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define PI (3.141592653)
using uchar = unsigned char;

struct point { int x, y; };

int min(int a, int b) {
	return a < b ? a : b;
}

void FFT2Radix(double *Xr, double *Xi, double *Yr, double *Yi, int nN, bool binverse);
void FFT2D(uchar **img, double **OutputReal, double **OutputImag, int nW, int nH);
void FFT2DInverse(double **InputReal, double **InputImag, double **Output, int W, int H);
void DNormalize2D(double **p1, uchar **p2, int W, int H);
void DNormalize2D2(double **p1, uchar **p2, int W, int H);
void arrange(double **real, double **imag, int W, int H);
void readbmp(ifstream &in, uchar **data, char *header, int header_size, string basepath, string filepath, int W, int H);
void writedata(ofstream &out, double **data, string basepath, string filepath, int W, int H, bool logscale = false, char *header = 0, int header_size = 0);
void writedata2(ofstream &out, double **data, string basepath, string filepath, int W, int H, bool logscale, char *header, int header_size);
void bilinear(uchar **x, uchar **y, int Win, int Wout, int Hin, int Hout);
void find_noisy_region(double **mag, vector<point> &peak_points, vector<point> &noisy_region, int W, int H, int nNoisyPeaks = 2, double tau = 8e-3);
void compute_GaSF(double **mag, double **GaSF, double a[], double b[], int W, int H, int nNoisyPeaks = 2, double tau = 8e-3, double tol = 1e-3);
void median(double** before, double** after, int Height, int Width);

int main() {

	string basepath = "";
	ifstream in;
	ofstream out;
	const int header_size = 54, noise_header_size = 54;
	const int H = 256, W = 256, HH = 252, WW = 252;
	char header[header_size], noise_header[noise_header_size];

	//////////////////////////// declare ////////////////////////////

	uchar **noised;
	uchar **image;
	double **mag;
	double **Yr;
	double **Yi;
	double **GaSF;

	////////////////////////// allocate ////////////////////////////

	noised = new uchar*[H];
	image = new uchar*[H];
	mag = new double*[H];
	Yr = new double*[H];
	Yi = new double*[H];
	GaSF = new double*[H];

	for (int i = 0; i < H; i++) {
		noised[i] = new uchar[W];
		image[i] = new uchar[W];
		mag[i] = new double[W];
		Yr[i] = new double[W];
		Yi[i] = new double[W];
		GaSF[i] = new double[W];
	}

	////////////////////////////////////////////////////////////////

	// read real header
	in.open(basepath + "twin_.bmp", ios::binary);
	in.read((char*)header, header_size);
	in.close();

	readbmp(in, noised, noise_header, noise_header_size, basepath, "twins_noise.bmp", WW, HH);
	for (int i = 0; i < HH; i++) for (int j = 0; j < WW; j++) noised[i][j] = noised[i][j + 1];
	bilinear(noised, image, WW, W, HH, H);
	// now variable image is 256x256

	////////////////////////////////////////////////////////////////

	FFT2D(image, Yr, Yi, W, H);
	arrange(Yr, Yi, W, H);
	for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) mag[i][j] = sqrt(pow(Yr[i][j], 2) + pow(Yi[i][j], 2));
	writedata(out, mag, basepath, "fft_noised_resized.bmp", W, H, true, header, header_size);
	writedata(out, mag, basepath, "fft_noised_resized.csv", W, H);

	////////////////////////////////////////////////////////////////
	//////////////////////// process here //////////////////////////
	////////////////////////////////////////////////////////////////


	double a[] = { 20, 20 }, b[] = { 2, 2 };//a, b값이 커지면 값이 십자가가 작아짐
	for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
		mag[i][j] = log(1. + mag[i][j]);

	//double aa = 3, bb = 0., cc = 0.5;
	compute_GaSF(mag, GaSF, a, b, W, H);
	for (int v = 0; v < H; v++) for (int u = 0; u < W; u++)
	{
		Yr[v][u] *= GaSF[v][u];
		Yi[v][u] *= GaSF[v][u];//십자노이즈 제거
		
		Yr[v][u] *= ((32768 - pow(v - 128, 2) - pow(u - 128, 2))/ 32768. );
		Yi[v][u] *= ((32768 - pow(v - 128, 2) - pow(u - 128, 2)) / 32768.);

		Yr[v][u] *= ((32768 - pow(v - 128, 2) - pow(u - 128, 2)) / 32768.);
		Yi[v][u] *= ((32768 - pow(v - 128, 2) - pow(u - 128, 2)) / 32768.);
		
	}

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) mag[i][j] = sqrt(pow(Yr[i][j], 2) + pow(Yi[i][j], 2));
	writedata2(out, mag, basepath, "fft_denoised.bmp", W, H, true, header, header_size);

	arrange(Yr, Yi, W, H);
	FFT2DInverse(Yr, Yi, mag, W, H);
	//median(mag, mag, 256, 256);//노이즈 감소
	//median(mag, mag, 256, 256);
	writedata(out, mag, basepath, "denoised.bmp", W, H, false, header, header_size);

	//////////////////////////// release ////////////////////////////

	for (int i = 0; i < H; i++) {
		delete[] noised[i];
		delete[] image[i];
		delete[] mag[i];
		delete[] Yr[i];
		delete[] Yi[i];
		delete[] GaSF[i];
	}
	delete[] noised;
	delete[] image;
	delete[] mag;
	delete[] Yr;
	delete[] Yi;
	delete[] GaSF;

	return 0;
}
void FFT2Radix(double *Xr, double *Xi, double *Yr, double *Yi, int nN, bool binverse) {
	// Cooley?Tukey FFT algorithm
	// https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
	double Wr, Wi;

	if (nN <= 1) return;

	////////////////////// assign //////////////////////
	for (int i = 0; i < nN; i++) {
		Yr[i] = Xr[i];
		Yi[i] = Xi[i];
	}

	////////////////////// swap values //////////////////////
	int j = 0, k = 0;
	for (int i = 1; i < (nN - 1); i++) {  // 양 끝점은 index 어차피 안 바뀜

		k = nN / 2;

		while (k <= j) {
			j -= k;
			k /= 2;
		}

		j += k;
		if (i < j) {
			swap(Yr[i], Yr[j]);
			swap(Yi[i], Yi[j]);
		}
	}

	////////////////////// transform //////////////////////
	double Tr, Ti;  // tmp??
	int iter, j2, pos;
	k = nN >> 1;  // floor(nN / 2)
	iter = 1;

	while (k > 0) {
		j = j2 = 0;

		for (int i = 0; i < (nN >> 1); i++) {
			// assign kernel
			Wr = cos(2. * PI * (j2 * k) / nN);
			if (binverse) Wi = -sin(2. * PI * (j2 * k) / nN);
			else Wi = sin(2. * PI * (j2 * k) / nN);

			pos = j + (1 << (iter - 1));

			Tr = Yr[pos] * Wr - Yi[pos] * Wi;
			Ti = Yr[pos] * Wi + Yi[pos] * Wr;
			Yr[pos] = Yr[j] - Tr;
			Yi[pos] = Yi[j] - Ti;
			Yr[j] += Tr;
			Yi[j] += Ti;

			j += 1 << iter;
			if (j >= nN) j = ++j2;  // assign j2 -> increment j2
		}
		k >>= 1;
		iter++;
	}

	if (binverse) {
		for (int i = 0; i < nN; i++) {
			Yr[i] /= nN;
			Yi[i] /= nN;
		}
	}
}
void FFT2DInverse(double **InputReal, double **InputImag, double **Output, int W, int H) {
	int x, y;
	double *dRealX, *dImagX;
	double *dRealY, *dImagY;
	double **OutputReal, **OutputImag;

	OutputReal = new double*[H];
	OutputImag = new double*[W];
	for (int i = 0; i < H; i++) {
		OutputReal[i] = new double[W];
		OutputImag[i] = new double[H];
	}

	dRealX = new double[W];
	dImagX = new double[W];
	dRealY = new double[W];
	dImagY = new double[W];

	for (y = 0; y < H; y++) {
		for (x = 0; x < W; x++) {
			dRealX[x] = InputReal[y][x];
			dImagX[x] = InputImag[y][x];
		}
		FFT2Radix(dRealX, dImagX, dRealY, dImagY, W, true);
		for (x = 0; x < W; x++) {
			OutputReal[y][x] = dRealY[x];
			OutputImag[y][x] = dImagY[x];
		}
	}

	delete[] dRealX;
	delete[] dImagX;
	delete[] dRealY;
	delete[] dImagY;

	dRealX = new double[H];
	dImagX = new double[H];
	dRealY = new double[H];
	dImagY = new double[H];

	for (x = 0; x < W; x++) {
		for (y = 0; y < H; y++) {
			dRealX[y] = OutputReal[y][x];
			dImagX[y] = OutputImag[y][x];
		}
		FFT2Radix(dRealX, dImagX, dRealY, dImagY, H, true);
		for (y = 0; y < H; y++) {
			OutputReal[y][x] = dRealY[y];
			OutputImag[y][x] = dImagY[y];
		}
	}

	delete[] dRealX;
	delete[] dImagX;
	delete[] dRealY;
	delete[] dImagY;

	for (y = 0; y < H; y++)
		for (x = 0; x < W; x++)
			Output[y][x] = OutputReal[y][x];

	for (int i = 0; i < H; i++) {
		delete[] OutputReal[i];
		delete[] OutputImag[i];
	}
	delete[] OutputReal;
	delete[] OutputImag;
}
void FFT2D(uchar **img, double **OutputReal, double **OutputImag, int W, int H) {
	int x, y;
	double *dRealX, *dImagX;
	double *dRealY, *dImagY;

	dRealX = new double[W];
	dImagX = new double[W];
	dRealY = new double[W];
	dImagY = new double[W];

	for (y = 0; y < H; y++) {
		for (x = 0; x < W; x++) {
			dRealX[x] = img[y][x];
			dImagX[x] = 0.;
		}

		FFT2Radix(dRealX, dImagX, dRealY, dImagY, W, false);

		for (x = 0; x < W; x++) {
			OutputReal[y][x] = dRealY[x];
			OutputImag[y][x] = dImagY[x];
		}
	}

	delete[] dRealX;
	delete[] dImagX;
	delete[] dRealY;
	delete[] dImagY;

	dRealX = new double[H];
	dImagX = new double[H];
	dRealY = new double[H];
	dImagY = new double[H];

	for (x = 0; x < W; x++) {
		for (y = 0; y < H; y++) {
			dRealX[y] = OutputReal[y][x];
			dImagX[y] = OutputImag[y][x];
		}

		FFT2Radix(dRealX, dImagX, dRealY, dImagY, H, false);

		for (y = 0; y < H; y++) {
			OutputReal[y][x] = dRealY[y];
			OutputImag[y][x] = dImagY[y];
		}
	}

	delete[] dRealX;
	delete[] dImagX;
	delete[] dRealY;
	delete[] dImagY;
}
void DNormalize2D2(double **p1, uchar **p2, int W, int H) {
	int x, y;
	double min = 9999.;
	double max = -9999.;
	double val;
	for (y = 0; y < H; y++)
		for (x = 0; x < W; x++) {
			val = p1[y][x];
			if (val > max) max = val;
			if (val < min) min = val;
		}

	if (max == min) {  // 모두 다 같음
		for (y = 0; y < H; y++)
			for (x = 0; x < W; x++)
				p2[y][x] = 0;
		return;
	}

	double dfactor = 255. / (max - min);
	for (y = 0; y < H; y++)
		for (x = 0; x < W; x++)
			p2[y][x] = (uchar)(pow((p1[y][x] - min) / (max - min), 1.3) * 255);
}
void DNormalize2D(double **p1, uchar **p2, int W, int H) {
	int x, y;
	double min = 9999.;
	double max = -9999.;
	double val;
	for (y = 0; y < H; y++)
		for (x = 0; x < W; x++) {
			val = p1[y][x];
			if (val > max) max = val;
			if (val < min) min = val;
		}

	if (max == min) {  // 모두 다 같음
		for (y = 0; y < H; y++)
			for (x = 0; x < W; x++)
				p2[y][x] = 0;
		return;
	}

	double dfactor = 255. / (max - min);
	for (y = 0; y < H; y++)
		for (x = 0; x < W; x++)
			p2[y][x] = (uchar)((p1[y][x] - min) * dfactor);
}
void arrange(double **real, double **imag, int W, int H) {
	for (int i = 0; i < H / 2; i++) {
		for (int j = 0; j < W / 2; j++) {
			swap(real[i][j], real[i + H / 2][j + W / 2]);
			swap(imag[i][j], imag[i + H / 2][j + W / 2]);
			swap(real[i][j + W / 2], real[i + H / 2][j]);
			swap(imag[i][j + W / 2], imag[i + H / 2][j]);
		}
	}
}
void readbmp(ifstream &in, uchar **data, char *header, int header_size, string basepath, string filepath, int W, int H) {
	uchar *row = new uchar[3 * W];
	in.open(basepath + filepath, ios::binary);
	in.read((char*)header, header_size);
	for (int i = 0; i < H; i++) {
		in.read((char*)row, 3 * W);
		for (int j = 0; j < W; j++) data[i][j] = row[3 * j];
	}
	in.close();
	delete[] row;
}
void writedata(ofstream &out, double **data, string basepath, string filepath, int W, int H, bool logscale, char *header, int header_size) {
	
	double **output = new double*[H];
	for (int i = 0; i < H; i++) {
		output[i] = new double[W];
		for (int j = 0; j < W; j++) output[i][j] = data[i][j];
	}

	if (logscale)
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
			data[i][j] = log(1. + data[i][j]);

	if (filepath.substr(filepath.size() - 3) == "csv") {
		out.open(basepath + filepath);
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
			out << data[i][j] << ((j == W - 1) ? "\n" : ",");
	}

	else {  // bmp
		out.open(basepath + filepath, ios::binary);
		uchar *row = new uchar[3 * W];
		uchar **normalized = new uchar*[H];
		for (int i = 0; i < H; i++) normalized[i] = new uchar[W];
		DNormalize2D(data, normalized, W, H);
		out.write((char*)header, header_size);
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++)
			{
				if (1.3*normalized[i][j] > 255)
					row[3 * j] = row[3 * j + 1] = row[3 * j + 2] = 255;
				else
					row[3 * j] = row[3 * j + 1] = row[3 * j + 2] = 1.3*normalized[i][j];
			}
			out.write((char*)row, 3 * W);
		}

		for (int i = 0; i < H; i++) delete[] normalized[i];
		delete[] row, normalized;
	}

	out.close();
	for (int i = 0; i < H; i++) delete[] output[i];
	delete[] output;

}
void writedata2(ofstream &out, double **data, string basepath, string filepath, int W, int H, bool logscale, char *header, int header_size) {

	double **output = new double*[H];
	for (int i = 0; i < H; i++) {
		output[i] = new double[W];
		for (int j = 0; j < W; j++) output[i][j] = data[i][j];
	}

	if (logscale)
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
			data[i][j] = log(1. + data[i][j]);

	if (filepath.substr(filepath.size() - 3) == "csv") {
		out.open(basepath + filepath);
		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
			out << data[i][j] << ((j == W - 1) ? "\n" : ",");
	}

	else {  // bmp
		out.open(basepath + filepath, ios::binary);
		uchar *row = new uchar[3 * W];
		uchar **normalized = new uchar*[H];
		for (int i = 0; i < H; i++) normalized[i] = new uchar[W];
		DNormalize2D2(data, normalized, W, H);
		out.write((char*)header, header_size);
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++)
				row[3 * j] = row[3 * j + 1] = row[3 * j + 2] = normalized[i][j];
			out.write((char*)row, 3 * W);
		}

		for (int i = 0; i < H; i++) delete[] normalized[i];
		delete[] row, normalized;
	}

	for (int i = 0; i < H; i++) delete[] output[i];
	delete[] output;

	out.close();
}
void bilinear(uchar **x, uchar **y, int Win, int Wout, int Hin, int Hout) {
	int nx, ny;
	double Rx = (Wout - 1) / (double)(Win - 1), Ry = (Hout - 1) / (double)(Hin - 1);
	double alphax, betax, alphay, betay;
	double tmp;
	for (int my = 0; my < Hout; my++) {
		for (int mx = 0; mx < Wout; mx++) {
			nx = (int)(mx / Rx);
			ny = (int)(my / Ry);
			alphax = mx / Rx - nx;
			alphay = my / Ry - ny;
			betax = 1 - alphax;
			betay = 1 - alphay;
			tmp = (
				betax  * betay  * x[ny][nx]
				+ alphax * betay  * x[ny][min(nx + 1, Win - 1)]
				+ betax * alphay * x[min(ny + 1, Hin - 1)][nx]
				+ alphax * alphay * x[min(ny + 1, Hin - 1)][min(nx + 1, Win - 1)]
				);
			y[my][mx] = ((tmp > 255) ? 255 : (tmp < 0) ? 0 : tmp);
		}
	}
}
void find_noisy_region(double **mag, vector<point> &peak_points, vector<point> &noisy_region, int W, int H, int nNoisyPeaks, double tau) {
	/*
	find peaks  // find 3 largest mag values
	remove low freq area  // center
	for every peak points
	while active points exist
	if valid
	mark it as blue zone (1)
	mark all non-bluezone inactive neightbors as active
	else
	mark it as inactive (0)
	*/

	// find peaks
	peak_points.resize(nNoisyPeaks + 1);
	vector<double> max(nNoisyPeaks + 1, -9999);
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			for (int k = 0; k < nNoisyPeaks + 1; k++) {
				if (mag[i][j] > max[k]) {
					max.insert(max.begin() + k, mag[i][j]);
					peak_points.insert(peak_points.begin() + k, { j, i });
					max.pop_back();
					peak_points.pop_back();
					break;
				}
			}

	// remove low freq area
	for (int k = 0; k < nNoisyPeaks + 1; k++)
		if (abs(peak_points[k].x - 128) < 3 && abs(peak_points[k].y - 128) < 3) {
			peak_points.erase(peak_points.begin() + k);
			break;
		}

	int xx, yy;
	for (const point &pp : peak_points) {

		double peak = mag[pp.y][pp.x];

		queue<point> active_points;
		active_points.push(pp);

		int **states = new int*[H];
		for (int i = 0; i < H; i++) {
			states[i] = new int[W];
			for (int j = 0; j < W; j++) states[i][j] = 0;
		}
		states[pp.y][pp.x] = -1;  // active

		point ap;

		while (!active_points.empty()) {
			ap = active_points.front();

			if (mag[ap.y][ap.x] / peak > tau) {  // valid?
				states[ap.y][ap.x] = 1;  // blue zone
				for (int ii = -1; ii < 2; ii++) for (int jj = -1; jj < 2; jj++) {
					xx = ap.x + jj;
					yy = ap.y + ii;
					if (xx >= W || xx < 0 || yy >= H || yy < 0) continue;
					if (states[yy][xx] == 0) {  // non-blue & inactive
						active_points.push({ xx, yy });
						states[yy][xx] = -1;
					}
				}
			}
			else states[ap.y][ap.x] = 0;  // mark it as inactive (0)

			active_points.pop();
		}

		for (int i = 0; i < H; i++) for (int j = 0; j < W; j++)
			if (states[i][j] == 1)
				noisy_region.push_back({ j, i });

		for (int i = 0; i < H; i++) delete[] states[i];
		delete[] states;
	}
}
void compute_GaSF(double **mag, double **GaSF, double a[], double b[], int W, int H, int nNoisyPeaks, double tau, double tol) {
	vector<point> peak_points, noisy_region;
	find_noisy_region(mag, peak_points, noisy_region, W, H, nNoisyPeaks, tau);
	double H1, H2, D1n, D2n, GaSLF;

	int u, v;
	for (v = 0; v < H; v++) for (u = 0; u < W; u++) GaSF[u][v] = 1;
	for (const point &p : noisy_region) {
		u = p.x; v = p.y;
		H1 = H2 = 0;
		for (int n = 0; n < 2; n++) {
			D1n = sqrt(
				pow((u - peak_points[n].x) / a[n], 2)
				+ pow((v - peak_points[n].y) / b[n], 2)
			);
			D2n = sqrt(
				pow((u - peak_points[n].x) / b[n], 2)
				+ pow((v - peak_points[n].y) / a[n], 2)
			);
			H1 += exp(-pow(D1n, 2) / 2.);
			H2 += exp(-pow(D2n, 2) / 2.);
		}
		H1 = ((H1 < tol) ? 0 : H1);
		H2 = ((H2 < tol) ? 0 : H2);
		GaSLF = ((H1 > tol && H2 > tol) ? max(H1, H2) : H1 + H2);
		GaSF[v][u] = 1 - 0.99*GaSLF;//GaSLF가 1이 피크이므로 0.X곱해주면 최소값 조절 가능
	}
}
void median(double** before, double** after, int Height, int Width) {
	double mid1[9];
	double mid2[5];
	double mid3[5];
	double temp3[3];
	for (int row = 1; row < Height - 1; ++row) {
		for (int col = 1; col < Width - 1; ++col) {
			mid1[0] = before[row - 1][col - 1];
			mid1[1] = before[row - 1][col];
			mid1[2] = before[row - 1][col + 1];
			mid1[3] = before[row][col - 1];
			mid1[4] = before[row][col];
			mid1[5] = before[row][col + 1];
			mid1[6] = before[row + 1][col - 1];
			mid1[7] = before[row + 1][col];
			mid1[8] = before[row + 1][col + 1];

			int i, j;
			double tmp;
			for (i = 1; i < 9; i++)
			{
				tmp = mid1[i];
				j = i - 1;
				while (j >= 0 && mid1[j] > tmp) {
					mid1[j + 1] = mid1[j];
					j = j - 1;
				}
				mid1[j + 1] = tmp;
			}
			temp3[0] = mid1[4];
			mid2[0] = before[row - 1][col];//1
			mid2[1] = before[row][col - 1];//3
			mid2[2] = before[row][col];//4
			mid2[3] = before[row][col + 1];//5
			mid2[4] = before[row + 1][col];//7
			for (i = 1; i < 5; i++) {
				tmp = mid2[i];
				j = i - 1;
				while (j >= 0 && mid2[j] > tmp) {
					mid2[j + 1] = mid2[j];
					j = j - 1;
				}
				mid2[j + 1] = tmp;
			}
			temp3[1] = mid2[2];
			mid3[0] = before[row - 1][col - 1];//0
			mid3[1] = before[row - 1][col + 1];//2
			mid3[2] = before[row][col];//4
			mid3[3] = before[row + 1][col - 1];//6
			mid3[4] = before[row + 1][col + 1];//8
			for (i = 1; i < 5; i++) {
				tmp = mid3[i];
				j = i - 1;
				while (j >= 0 && mid3[j] > tmp) {
					mid3[j + 1] = mid3[j];
					j = j - 1;
				}
				mid3[j + 1] = tmp;
			}
			temp3[1] = mid3[2];
			for (i = 1; i < 3; i++) {
				tmp = temp3[i];
				j = i - 1;
				while (j >= 0 && temp3[j] > tmp) {
					temp3[j + 1] = temp3[j];
					j = j - 1;
				}
				temp3[j + 1] = tmp;
			}

			after[row][col] = temp3[1];
		}
	}
}