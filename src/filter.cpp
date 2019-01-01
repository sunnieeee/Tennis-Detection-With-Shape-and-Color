#include"include_all.h"

/**
 * @function filter
 * @author Sunnie CYQ
 * @brief  Ksize核大小为据样本测试所得经验值
 *         滤波和ksize的选择非常影响霍夫圆的检测，猜测是因为霍夫圆依靠轮廓进行圆检测，
           故不能损失太多轮廓信息，还需仔细研究houghcircles源码
 */

void filterDE( cv::Mat &gray,int Ksize )      //默认Ksize=9
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

void filterBLUR( cv::Mat &gray, int Ksize )      //默认Ksize=20
{
	/******************** Blur *************************/
	blur(gray, gray, cv::Size(Ksize, Ksize), cv::Point(-1, -1));
}

void filterGAUSS( cv::Mat &gray, int Ksize )        //默认Ksize=7
{
	/****************** GaussianBlur ********************/
	GaussianBlur(gray, gray, cv::Size(Ksize, Ksize), 0, 0);  
}

void filterMEDIAN( cv::Mat &gray, int Ksize )            //默认Ksize=5
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