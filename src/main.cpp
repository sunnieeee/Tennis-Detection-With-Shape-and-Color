#include "function_declare.h"
#include "fitellipse.h"
#include <math.h>
#include <SerialPort.h>


int main(int argc, const char** argv)
{
	cv::Mat srcImage;
	bool tennis = false;  //默认未检测到网球
	
	/************choose methods***********/
	bool HOUGH = false;
	bool SVM = true;
	if (HOUGH)
	{
		cout << "Using HoughCircle!" << endl;
	}
	if (SVM)
	{
		cout << "Using SVM!" << endl;
	}
	if (fitEllipseQ || fitEllipseAMSQ || fitEllipseDirectQ)
	{
		cout << "Using fitEllipse!" << endl;
	}

	/********************************* SERIAL PORT OPEN ************************************/
	unsigned char send_buf[10] = "00000000";     //初始化串口数组
	CSerialPort mySerialPort;
	if (!mySerialPort.InitPort(6))               //com5，cyq电脑左边的串口;com6,右边第三个
	{
		cout << "initPort fail !" << endl;
	}
	else
	{
		cout << "initPort success !" << endl;
	}
	if (!mySerialPort.OpenListenThread())
	{
		cout << "OpenListenThread fail !" << endl;
	}
	else
	{
		cout << "OpenListenThread success !" << endl;
	}
	
	/********************************** IMAGE PRE-PROCESSING *************************************/
	//若读取图片
	/*srcImage = cv::imread("./data/tennis1/t1346.jpg");

	if (srcImage.empty())
	{
		cout << "Image open error!" << endl;
		return 0;
	}

	else
	{
		cv::namedWindow("原图", cv::WINDOW_KEEPRATIO);
		imshow("原图", srcImage);
		
		if (SVM)
		{	
			int st1, et1;
			st1 = cvGetTickCount();
			resize(srcImage, srcImage, cv::Size(k*srcImage.cols, k*srcImage.rows));
			svm_predict(srcImage);
			et1 = cvGetTickCount();
			cout << "times cost:" << (et1 - st1) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";

			cv::waitKey(0);
		}
	}*/
	
	
	//若读视频
	cv::VideoCapture cap(1);
	if (!cap.isOpened())
		cout << "error open!" << endl;
	else
	while (1)
	{
		cap >> srcImage;
		cv::Mat src;
		srcImage.copyTo(src);

		//设定感兴趣区域
		cv::Mat roi; 
		int roi_x = 20;
		int roi_y = 5;
		int roi_width = 600;   //不大于640
		int roi_height = 470;   //不大于480
		int width = srcImage.cols;

		cv::Rect rec(roi_x, roi_y, roi_width, roi_height);
		roi = srcImage(rec);

		double centre_x = width / 2 - roi_x;
		//cout << "ROI中心" << centre_x << endl << endl;
		

		/************************************ SVM ****************************************/
		if (SVM)
		{
			int st1, et1;
			st1 = cvGetTickCount();
			svm_predict(roi);
			et1 = cvGetTickCount();
			cout << "times cost:" << (et1 - st1) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";
		}


		/***********************************************************************************/
		double s = 0;               //小车底盘中心与网球的距离，单位m
		double theta = 0;           //机器人极坐标系下，网球偏离的角度，左正右负
		int radius = 0;             //网球像素半径
		int x = 0;
		int y = 0;
		int rx = 0;
		int ry = 0;                 //原图，ROI中网球中心坐标

		int max_radius = 0;       //储存相应的半径
		double max_r_x = centre_x;   //储存相应的坐标

		/********************************** HOUGH CIRCLES ***********************************/
		if (HOUGH)
		{
			//转灰度图，降噪
			cv::Mat gray;
			cvtColor(roi, gray, cv::COLOR_BGR2GRAY); //若选择双边滤波要注释掉此行
			filterGAUSS(gray);        //为根据应用场景选择的filter
			//namedWindow("hough_filter", WINDOW_KEEPRATIO);
			//imshow("hough_filter", gray);

			vector<cv::Vec3f>circles;
			vector<cv::Point>polar_centers;
			HoughCircles(gray, circles, cv::HOUGH_GRADIENT, //输入，输出，方法（类型）
				1.5, //dp(dp=1时表示霍夫空间与输入图像空间的大小一致，dp=2时霍夫空间是输入图像空间的一半，以此类推)
				250, //最短距离-可以分辨是两个圆，否则认为是同心圆 ,
				200, //边缘检测时使用Canny算子的高阈值
				40, //中心点累加器阈值—候选圆心（霍夫空间内累加和大于该阈值的点就对应于圆心），越小越敏感，注意太敏感会导致死循环
				0, 0);


			//轮询查找距离最近的网球
			for (size_t i = 0; i < circles.size(); i++)
			{
				rx = cvRound(circles[i][0]);
				ry = cvRound(circles[i][1]);
				x = rx + roi_x;
				y = ry + roi_y;

				radius = cvRound(circles[i][2]);
				//cout << "半径" << radius << endl;

				//[todo]加一个颜色判断
				int B, G, R;
				/*
				B = (srcImage.at<Vec3b>(y, x)[0] + srcImage.at<Vec3b>(y + 5, x + 5)[0] + srcImage.at<Vec3b>(y + 5, x - 5)[0] + srcImage.at<Vec3b>(y - 5, x - 5)[0] + srcImage.at<Vec3b>(y - 5, x + 5)[0]) / 5;
				G = (srcImage.at<Vec3b>(y, x)[1] + srcImage.at<Vec3b>(y + 5, x + 5)[1] + srcImage.at<Vec3b>(y + 5, x - 5)[1] + srcImage.at<Vec3b>(y - 5, x - 5)[1] + srcImage.at<Vec3b>(y - 5, x + 5)[1]) / 5;
				R = (srcImage.at<Vec3b>(y, x)[2] + srcImage.at<Vec3b>(y + 5, x + 5)[2] + srcImage.at<Vec3b>(y + 5, x - 5)[2] + srcImage.at<Vec3b>(y - 5, x - 5)[2] + srcImage.at<Vec3b>(y - 5, x + 5)[2]) / 5;
				*/
				B = srcImage.at<cv::Vec3b>(y, x)[0];
				G = srcImage.at<cv::Vec3b>(y, x)[1];
				R = srcImage.at<cv::Vec3b>(y, x)[2];

				if (radius < 60 /*&& B<maxB && B>minB && G<maxG && G>minG && R<maxR && R>minR*/)
				{
					tennis = true;    //检测到了网球

					if (radius > max_radius)
					{
						max_radius = radius;
						max_r_x = x;
					}

					cv::Point center(x, y);
					//cout << "像素坐标：" << center << endl << endl;

					///////////////TEST//////////////////////
					/*B = srcImage.at<Vec3b>(y, x)[0];
					G = srcImage.at<Vec3b>(y, x)[1];
					R = srcImage.at<Vec3b>(y, x)[2];
					cout << "B=" << B << ",G=" << G << ",R=" << R << endl;*/

					circle(srcImage, center, 4, cv::Scalar(0, 255, 0), -1, 8, 0);
					circle(srcImage, center, radius, cv::Scalar(155, 50, 255), 3, 4, 0);   //为什么Mat roi里也自动画上了，，

					//若路径规划需所有网球坐标
					/*cartesian_to_polar(x, radius, centre_x, s, theta);
					cv::Point polar_center(s, theta);
					polar_centers.push_back(polar_center);*/

				}

			}


			//cout << "maxradius=" << max_radius << endl;
			//若路径规划为选择距离最近的球返回
			cartesian_to_polar(max_r_x, max_radius, centre_x, s, theta);
		}


		/********************************** FITELLIPSE ***********************************/
		if ( fitEllipseQ || fitEllipseAMSQ || fitEllipseDirectQ )
		{
			cv::Mat filter;
			cvtColor(roi, filter, cv::COLOR_BGR2GRAY);
			filterGAUSS(filter, 15);
			filterDE(filter);
			//namedWindow("FE_filter", WINDOW_KEEPRATIO);
			//imshow("FE_filter", gray);

			_fitellipse(filter, rx, radius);
			if (radius)
			{
				tennis = true;
				x = rx + roi_x;
				cout << "FitEllipse:" << "radius=" << radius << ",x=" << x << endl;
				cartesian_to_polar(x, radius, centre_x, theta, s);
			}
		}
		/************************************ OUTPUT ****************************************/


		polar_buff(tennis, send_buf, s, theta);
		mySerialPort.WriteData(send_buf, 10);
		tennis = false;


		cv::namedWindow("roi", cv::WINDOW_KEEPRATIO);
		cv::namedWindow("src", cv::WINDOW_KEEPRATIO);
		imshow("roi", roi);
		imshow("src", src);


		if (cv::waitKey(50) == 27) break;

	}

	return 0;
}