#include"function_declare.h"

using namespace cv::ml;

void svm_predict(cv::Mat &src)
{	
	resize(src,src, cv::Size(k*src.cols, k*src.rows));
	
	cv::Ptr<SVM> svm = SVM::load("./data/model.xml");

	cv::Vec3b color(0, 0, 0);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			cv::Vec3b point = src.at<cv::Vec3b>(i, j);
			cv::Mat sampleMat = (cv::Mat_<float>(1, 3) << point[0], point[1], point[2]);
			float response = svm->predict(sampleMat);
			if ((int)response != 1)
			{
				src.at<cv::Vec3b>(i, j) = color;
			}
		}
	}

	namedWindow("predict", cv::WINDOW_KEEPRATIO);
	imshow("predict", src);
}