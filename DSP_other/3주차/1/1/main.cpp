#include <iostream>
#include <fstream>
using namespace std;
#define Width 300
#define Height 200
#define WH 60000

int main()
{
	int i, j, m, individual_idx, compositive_idx;
	ofstream fff("video.rgb", ios::out | ios::binary);
	unsigned char R[WH], G[WH], B[WH], RGB[3 * WH];

	for (m = 100; m < 200; m += 5)//동영상
	{
		for (i = 0; i < WH; i++)//배경
		{
			R[i] = 78;
			G[i] = 119;
			B[i] = 188;
		}
		for (i = 0; i < Height; i++)
		{
			for(int j =0; j<Width;j++)
			if ((i >= 50 && i < 100) && (j >= 50 && j < 100))
			{
				individual_idx = (i * 300 + j + m);
				R[individual_idx] = G[individual_idx] = 255; *(B + individual_idx) = 0;
			}
			
		}
		for (i = compositive_idx = 0; i < WH; i++, compositive_idx += 3)
		{
			RGB[compositive_idx] = R[i];
			RGB[compositive_idx + 1] = G[i];
			RGB[compositive_idx + 2] = B[i];
		}
		fff.write((const char*)RGB, 3 * WH);
	}
	fff.close();
	return 0;
}