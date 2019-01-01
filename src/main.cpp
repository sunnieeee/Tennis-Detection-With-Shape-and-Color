#include "function_declare.h"
#include "fitellipse.h"
#include <math.h>
#include <SerialPort.h>


int main(int argc, const char** argv)
{
	cv::Mat srcImage;
	bool tennis = false;  //Ĭ��δ��⵽����
	
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
	unsigned char send_buf[10] = "00000000";     //��ʼ����������
	CSerialPort mySerialPort;
	if (!mySerialPort.InitPort(6))               //com5��cyq������ߵĴ���;com6,�ұߵ�����
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
	//����ȡͼƬ
	/*srcImage = cv::imread("./data/tennis1/t1346.jpg");

	if (srcImage.empty())
	{
		cout << "Image open error!" << endl;
		return 0;
	}

	else
	{
		cv::namedWindow("ԭͼ", cv::WINDOW_KEEPRATIO);
		imshow("ԭͼ", srcImage);
		
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
	
	
	//������Ƶ
	cv::VideoCapture cap(1);
	if (!cap.isOpened())
		cout << "error open!" << endl;
	else
	while (1)
	{
		cap >> srcImage;
		cv::Mat src;
		srcImage.copyTo(src);

		//�趨����Ȥ����
		cv::Mat roi; 
		int roi_x = 20;
		int roi_y = 5;
		int roi_width = 600;   //������640
		int roi_height = 470;   //������480
		int width = srcImage.cols;

		cv::Rect rec(roi_x, roi_y, roi_width, roi_height);
		roi = srcImage(rec);

		double centre_x = width / 2 - roi_x;
		//cout << "ROI����" << centre_x << endl << endl;
		

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
		double s = 0;               //С����������������ľ��룬��λm
		double theta = 0;           //�����˼�����ϵ�£�����ƫ��ĽǶȣ������Ҹ�
		int radius = 0;             //�������ذ뾶
		int x = 0;
		int y = 0;
		int rx = 0;
		int ry = 0;                 //ԭͼ��ROI��������������

		int max_radius = 0;       //������Ӧ�İ뾶
		double max_r_x = centre_x;   //������Ӧ������

		/********************************** HOUGH CIRCLES ***********************************/
		if (HOUGH)
		{
			//ת�Ҷ�ͼ������
			cv::Mat gray;
			cvtColor(roi, gray, cv::COLOR_BGR2GRAY); //��ѡ��˫���˲�Ҫע�͵�����
			filterGAUSS(gray);        //Ϊ����Ӧ�ó���ѡ���filter
			//namedWindow("hough_filter", WINDOW_KEEPRATIO);
			//imshow("hough_filter", gray);

			vector<cv::Vec3f>circles;
			vector<cv::Point>polar_centers;
			HoughCircles(gray, circles, cv::HOUGH_GRADIENT, //���룬��������������ͣ�
				1.5, //dp(dp=1ʱ��ʾ����ռ�������ͼ��ռ�Ĵ�Сһ�£�dp=2ʱ����ռ�������ͼ��ռ��һ�룬�Դ�����)
				250, //��̾���-���Էֱ�������Բ��������Ϊ��ͬ��Բ ,
				200, //��Ե���ʱʹ��Canny���ӵĸ���ֵ
				40, //���ĵ��ۼ�����ֵ����ѡԲ�ģ�����ռ����ۼӺʹ��ڸ���ֵ�ĵ�Ͷ�Ӧ��Բ�ģ���ԽСԽ���У�ע��̫���лᵼ����ѭ��
				0, 0);


			//��ѯ���Ҿ������������
			for (size_t i = 0; i < circles.size(); i++)
			{
				rx = cvRound(circles[i][0]);
				ry = cvRound(circles[i][1]);
				x = rx + roi_x;
				y = ry + roi_y;

				radius = cvRound(circles[i][2]);
				//cout << "�뾶" << radius << endl;

				//[todo]��һ����ɫ�ж�
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
					tennis = true;    //��⵽������

					if (radius > max_radius)
					{
						max_radius = radius;
						max_r_x = x;
					}

					cv::Point center(x, y);
					//cout << "�������꣺" << center << endl << endl;

					///////////////TEST//////////////////////
					/*B = srcImage.at<Vec3b>(y, x)[0];
					G = srcImage.at<Vec3b>(y, x)[1];
					R = srcImage.at<Vec3b>(y, x)[2];
					cout << "B=" << B << ",G=" << G << ",R=" << R << endl;*/

					circle(srcImage, center, 4, cv::Scalar(0, 255, 0), -1, 8, 0);
					circle(srcImage, center, radius, cv::Scalar(155, 50, 255), 3, 4, 0);   //ΪʲôMat roi��Ҳ�Զ������ˣ���

					//��·���滮��������������
					/*cartesian_to_polar(x, radius, centre_x, s, theta);
					cv::Point polar_center(s, theta);
					polar_centers.push_back(polar_center);*/

				}

			}


			//cout << "maxradius=" << max_radius << endl;
			//��·���滮Ϊѡ�����������򷵻�
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