#include"include_all.h"

/**
 * @function filter
 * @author Sunnie CYQ
 * @brief  Ksize�˴�СΪ�������������þ���ֵ
 *         �˲���ksize��ѡ��ǳ�Ӱ�����Բ�ļ�⣬�²�����Ϊ����Բ������������Բ��⣬
           �ʲ�����ʧ̫��������Ϣ��������ϸ�о�houghcirclesԴ��
 */

void filterDE( cv::Mat &gray,int Ksize )      //Ĭ��Ksize=9
{
	/******************* Dilate & Erode ******************/
	cv::Mat g1, g2, g3;
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(Ksize, Ksize));
	dilate(gray, gray, element);
	erode(gray, g1, element);
	/*namedWindow("1", WINDOW_KEEPRATIO);
	imshow("1", g1);
	namedWindow("2", WINDOW_KEEPRATIO);
	imshow("2", g2);
	namedWindow("3", WINDOW_KEEPRATIO);
	imshow("3", g3);*/
}

void filterBLUR( cv::Mat &gray, int Ksize )      //Ĭ��Ksize=20
{
	/******************** Blur *************************/
	blur(gray, gray, cv::Size(Ksize, Ksize), cv::Point(-1, -1));
}

void filterGAUSS( cv::Mat &gray, int Ksize )        //Ĭ��Ksize=7
{
	/****************** GaussianBlur ********************/
	GaussianBlur(gray, gray, cv::Size(Ksize, Ksize), 0, 0);  
}

void filterMEDIAN( cv::Mat &gray, int Ksize )            //Ĭ��Ksize=5
{
	/******************* MedianBlur *********************/
	medianBlur(gray, gray, Ksize);
}

void filterBILAT( cv::Mat &src, cv::Mat &gray )
{
	/******************* BilateralFilter *****************/
	cv::Mat fil1, fil2, fil3;
	bilateralFilter(src, fil1, 0, 150, 5);
	pyrMeanShiftFiltering(fil1, fil2, 5, 100);
	GaussianBlur(fil2, fil3, cv::Size(13, 15), 15);
	cvtColor(fil3, gray, cv::COLOR_BGR2GRAY);
	/*namedWindow("fil1", WINDOW_KEEPRATIO);
	namedWindow("fil2", WINDOW_KEEPRATIO);
	namedWindow("fil3", WINDOW_KEEPRATIO);
	imshow("fil1", fil1);
	imshow("fil2", fil2);
	imshow("fil3", fil3);*/
}