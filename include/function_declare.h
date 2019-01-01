#ifndef FUNCTION_DECLARE_H
#define FUNCTION_DECLARE_H

/// INCLUDE
#include"include_all.h"

/// Function Declarations
/***************************** FILTER ********************************/
void filterDE(cv::Mat &gray, int Ksize = 15);     //��������
void filterBLUR(cv::Mat &gray, int Ksize = 20);    //��ֵ�˲�
void filterGAUSS(cv::Mat &gray, int Ksize = 7);    //��˹�˲�
void filterMEDIAN(cv::Mat &gray, int Ksize = 5);    //��ֵ�˲�
void filterBILAT(cv::Mat &src, cv::Mat &gray);    //˫���˲�

/************************** COORDINATE TRANS **************************/
void cartesian_to_polar(double x, int radius, double centre_x, double &s , double &theta );
void polar_buff(bool tennis, unsigned char(&send_buf)[10], double s = 0, double theta = 0);

/**************************** SVM PREDICT *****************************/
void svm_predict(cv::Mat&);

#endif // !FUNCTION_DECLARE_H