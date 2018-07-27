/*
代码选自：https://blog.csdn.net/u011600592/article/details/75044803
借助半调算法，实现两张图像的融合，将背景纹理融合到目标图像中，
算法效果如图ImageBlendTest1.jpg所示
*/

#include <iostream>
#include "core/core.hpp"  
#include "highgui/highgui.hpp"  
#include "imgproc/imgproc.hpp"  
#include <algorithm>
#include <cmath>

using namespace std;
using namespace cv;

float Cube(float a, float b, float x)
{
	if (x < a)return 0;
	if (x >= b) return 1;
	x = (x - a) / (b - a);
	return x*x*(3 + 2 * x);
}

int main(int argc, char *argv[])
{
	Mat image = imread("test.jpg");
	Mat image2 = imread("test2.jpg");
	imshow("original image", image);
	imshow("image2", image2);

	int cols = min(image.cols, image2.cols);
	int rows = min(image.rows, image2.rows);

	float s = 200;
	Mat res(rows, cols, CV_32FC3);
	res = Mat::zeros(res.size(), res.type());

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Vec3b P = image.at<Vec3b>(i, j);
			Vec3b D = image2.at<Vec3b>(i, j);
			int ib = P[0];
			int ig = P[1];
			int ir = P[2];

			int mb = D[0];
			int mg = D[1];
			int mr = D[2];
			//float tem =  Cube(ir - s, ir + s, mr);
			res.at<Vec3f>(i, j)[0] =  int(255 * (1 - Cube(ib - s, ib + s, mb)));
			res.at<Vec3f>(i, j)[1] = int(255 * (1 - Cube(ig - s, ig + s, mg)));
			res.at<Vec3f>(i, j)[2] =  int(255 * (1 - Cube(ir - s, ir + s, mr)));

		}
	}
	//normalize(res, res, 0, 255, NORM_MINMAX);
	convertScaleAbs(res, res);
	
	imshow("res image", res);

	waitKey(0);
	return 0;
}

