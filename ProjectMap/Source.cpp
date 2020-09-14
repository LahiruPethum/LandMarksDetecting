#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include "stdio.h"
#include "string"
#include <stdlib.h>

using namespace cv;
using namespace std;

int lowerH = 168;
int upperH = 256;

int lowerS = 175;
int upperS = 256;

int lowerV = 0;
int upperV = 256;

IplImage* frame = 0;
IplImage* frm = 0;
IplImage* imgHSV = 0;
IplImage* imgThresh = 0;

//vector<vector<Point> > contours;
//vector<Vec4i> hierarchy;

void draw_conture(IplImage * temp)
{

	CvSeq* contour;  //hold the pointer to a contour
	CvSeq* result;     //hold sequence of points of a contour
	CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

	cvFindContours(temp, storage, &contour, sizeof(CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	for (; contour != 0; contour = contour->h_next)
	{
		result = cvApproxPoly(contour, sizeof(CvContour),
			storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);
		CvRect rect = cvBoundingRect(contour, 0); //extract bounding box for current contour
		if (cvContourArea(result, CV_WHOLE_SEQ, 0) >= 1000)
		{
			//cvDrawContours(frame, contour, CV_RGB(0,0,255), CV_RGB(0,0,255), 2, 1, 8, cvPoint(0, 0));
			frm = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
			cvCopy(frame, frm);
			cvRectangle(frm, cvPoint(rect.x, rect.y),
			cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(0, 255, 255), 2, 8, 0);
		}
	}
	cvShowImage("Object Color Range", frm);
}

#pragma region trackbar

void on_trackbar1(int position)
{
	lowerH = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar2(int position)
{
	upperH = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar3(int position)
{
	lowerS = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar4(int position)
{
	upperS = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar5(int position)
{
	lowerV = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

void on_trackbar6(int position)
{
	upperV = position;
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);
	cvShowImage("Object Detected", imgThresh);
	draw_conture(imgThresh);
}

#pragma endregion trackbar

int main()
{
	int x,a,b,d,e,f;
	for (;;) {

		cout << "\n\t\t\t\t\t------Land Mark Ditection Application------";
		cout << "\n\t\t\t\t\t\t  ---Los Anjeles City---\n";
		cout << "\n\n\tSelect one of below marks\n\n";
		cout << "1.Ground \n2.Harbour \n3.Car Park\n4.Town Hall\n5.Swimming pool\n";
		cout << "\n Select a place : ";
		cin >> x;
		cout << "\n Select one of below view : \n";
		cout << "\n1.over view side 1 \n2.over view side 2\n3.3D view \n";
		cout << "\n Select a view :";

		switch (x) {

		case 1:

			cin >> a;

			if (a == 1) {
				cvNamedWindow("Object Color Range", 1);

				frame = cvLoadImage("MyMap1.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(9, 135, 73), cvScalar(93, 193, 137), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (a == 2) {

				frame = cvLoadImage("MyMap2.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(0, 138, 69), cvScalar(196, 234, 164), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (a == 3) {

				frame = cvLoadImage("MyMap3.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(0, 68, 81), cvScalar(256, 256, 151), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();
			}
			else {

				cout << "Invalid No";
			}break;

		case 2:
			
			cin >> b;

			if (b == 1) {
				cvNamedWindow("Object Color Range", 1);

				frame = cvLoadImage("MyMap1.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(88, 123, 69), cvScalar(112, 222, 139), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (b == 2) {

				frame = cvLoadImage("MyMap2.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(102, 138, 52), cvScalar(243, 202, 198), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (b == 3) {

				frame = cvLoadImage("MyMap3.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(102, 138, 52), cvScalar(243, 202, 198), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else {

				cout << "invalid No";
			}break;


		case 3:
			
			cin >> d;

			if (d == 1) {
				cvNamedWindow("Object Color Range", 1);

				frame = cvLoadImage("MyMap1.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(112, 28, 122), cvScalar(120, 212, 240), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (d == 2) {

				frame = cvLoadImage("MyMap2.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(101, 47, 85), cvScalar(121, 118, 144), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (d == 3) {

				frame = cvLoadImage("MyMap3.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(57, 38, 118), cvScalar(131, 202, 256), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();
			}
			else {
				cout << "invalid No";
			}
			break;

		case 4:

		
			cin >> e;

			if (e == 1) {
				cvNamedWindow("Object Color Range", 1);

				frame = cvLoadImage("MyMap1.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(0, 56, 151), cvScalar(9, 107, 251), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (e == 2) {

				frame = cvLoadImage("MyMap2.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(0, 95, 147), cvScalar(120, 125, 233), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (e == 3) {

				frame = cvLoadImage("MyMap3.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(0, 54, 177), cvScalar(61, 231, 256), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else {
				cout << "invalid No";
			}break;

		case 5:

			cin >> f;

			if (f == 1) {
				cvNamedWindow("Object Color Range", 1);

				frame = cvLoadImage("MyMap1.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(86, 0, 185), cvScalar(124, 256, 256), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (f == 2) {

				frame = cvLoadImage("MyMap2.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(90, 0, 172), cvScalar(246, 190, 215), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else if (f == 3) {

				frame = cvLoadImage("MyMap3.jpg", 1);

				imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
				imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
				cvCvtColor(frame, imgHSV, CV_BGR2HSV);
				cvInRangeS(imgHSV, cvScalar(61, 0, 173), cvScalar(133, 256, 256), imgThresh);

				cvShowImage("Object Color Range", frame);

				draw_conture(imgThresh);
				cvWaitKey(0);

				cvDestroyAllWindows();

			}
			else {
				cout << "Invalid No";
			}break;

		}
	}
	/*cvNamedWindow("MyMap",CV_WINDOW_AUTOSIZE );
	cvNamedWindow("Object Detected", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("LowerH", "Object Detected", &lowerH, 256, on_trackbar1);
	cvCreateTrackbar("UpperH", "Object Detected", &upperH, 256, on_trackbar2);
	cvCreateTrackbar("LowerS", "Object Detected", &lowerS, 256, on_trackbar3);
	cvCreateTrackbar("UpperS", "Object Detected", &upperS, 256, on_trackbar4);
	cvCreateTrackbar("LowerV", "Object Detected", &lowerV, 256, on_trackbar5);
	cvCreateTrackbar("UpperV", "Object Detected", &upperV, 256, on_trackbar6);
	frame = cvLoadImage("MyMap1.jpg", 1);

	imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
	imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
	cvCvtColor(frame, imgHSV, CV_BGR2HSV);
	cvInRangeS(imgHSV, cvScalar(lowerH, lowerS, lowerV), cvScalar(upperH, upperS, upperV), imgThresh);

	cvShowImage("Object Detected", imgThresh);
	cvShowImage("MyMap1", frame);

	draw_conture(imgThresh);
	cvWaitKey(0);

	cvReleaseImage(&imgHSV);
	cvReleaseImage(&imgThresh);
	cvReleaseImage(&frame);


	cvDestroyAllWindows();*/
	return 0;
}