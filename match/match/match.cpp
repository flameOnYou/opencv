// match.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;
int app(vector<double> minV);

int main()
{
	Mat img = imread("a.jpg");       //原图像
	Mat temp = imread("1.jpg");     //模板
	Mat result;

	vector<double> minV;
	vector<Point> minL;


	vector<Mat> down_temp;
	down_temp.push_back(temp);


	for (int i = 0; i<4; i++)
	{
		Mat temp1;

		cout << down_temp[i].cols << endl;
		cout << down_temp[i].rows << endl;

		int result_cols = img.cols - down_temp[i].cols + 1;
		int result_rows = img.rows - down_temp[i].rows + 1;
		result.create(result_cols, result_rows, CV_32FC1);
		matchTemplate(img, down_temp[i], result, CV_TM_SQDIFF);

		double minVal;
		double maxVal;
		Point  minLoc;
		Point  maxLoc;
		Point  matchLoc;

		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

		minVal = minVal / (down_temp[i].cols*down_temp[i].rows);
		cout << minVal << endl;
		minV.push_back(minVal);
		minL.push_back(minLoc);
		resize(down_temp[i], temp1, Size(down_temp[i].cols / 1.3, down_temp[i].rows / 1.3));
		down_temp.push_back(temp1);
	}


	int location;

	location = app(minV);

	rectangle(img, minL[location], Point(minL[location].x + down_temp[location].cols, minL[location].y + down_temp[location].rows), Scalar::all(0), 2, 8, 0);

	imshow("结果", img);

	waitKey();


	return 0;
}


int app(vector<double> minV)
{
	int t = 0;


	for (int i = 1; i < minV.size(); i++)
	{
		if (minV[i] < minV[t]) t = i;
	}


	return t;
}
