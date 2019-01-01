//INCLUDE
#include"fitellipse.h"


/**
 * @function fitellipse
 * @author Sunnie CYQ
 * @brief 椭圆拟合
 */

void _fitellipse( cv::Mat &filter,int &x, int &radius )
{
	cv::RotatedRect box, boxAMS, boxDirect;
	vector<vector<cv::Point> > contours;

	cv::Mat bimage = filter >= eThresh;
	findContours(bimage, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);


	canvas paper;
	paper.init(int(0.8*MIN(bimage.rows, bimage.cols)), int(1.2*MAX(bimage.rows, bimage.cols)));
	paper.stretch(cv::Point2f(0.0f, 0.0f), cv::Point2f((float)(bimage.cols + 2.0), (float)(bimage.rows + 2.0)));
	std::vector<std::string> text;
	std::vector<cv::Scalar> color;
	if (fitEllipseQ) {
		text.push_back("OpenCV");
		color.push_back(fitEllipseColor);
	}
	if (fitEllipseAMSQ) {
		text.push_back("AMS");
		color.push_back(fitEllipseAMSColor);
	}
	if (fitEllipseDirectQ) {
		text.push_back("Direct");
		color.push_back(fitEllipseDirectColor);
	}
	//paper.drawLabels(text, color);


	int margin = 2;
	vector< vector<cv::Point2f> > points;
	for (size_t i = 0; i < contours.size(); i++)
	{
		size_t count = contours[i].size();
		if (count < 6)
			continue;
		cv::Mat pointsf;
		cv::Mat(contours[i]).convertTo(pointsf, CV_32F);
		vector<cv::Point2f>pts;
		for (int j = 0; j < pointsf.rows; j++) {
			cv::Point2f pnt = cv::Point2f(pointsf.at<float>(j, 0), pointsf.at<float>(j, 1));
			if ((pnt.x > margin && pnt.y > margin && pnt.x < bimage.cols - margin && pnt.y < bimage.rows - margin)) {
				if (j % 20 == 0) {
					pts.push_back(pnt);
				}
			}
		}
		points.push_back(pts);
	}
	for (size_t i = 0; i < points.size(); i++)
	{
		vector<cv::Point2f> pts = points[i];
		if (pts.size() <= 5) {
			continue;
		}
		if (fitEllipseQ) {
			box = fitEllipse(pts);
			if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 30 ||
				MAX(box.size.width, box.size.height) <= 0 ||
				MIN(box.size.width, box.size.height) <= 0) {
				continue;
			}
			else if (box.size.height < 60 && box.size.width < 60 && (box.size.height - box.size.width) < 20 && (box.size.height - box.size.width) > (-20) )
			{
				radius = MAX(box.size.height, box.size.width) / 2;
				x = box.center.x;
				//cout << "FitEllipseQ:" << endl << "radius=" << radius << ",x=" << x << endl;
				paper.drawEllipseWithBox(box, fitEllipseColor, 3);
			}
			
		}
		if (fitEllipseAMSQ) {
			boxAMS = fitEllipseAMS(pts);
			if (MAX(boxAMS.size.width, boxAMS.size.height) > MIN(boxAMS.size.width, boxAMS.size.height) * 30 ||
				MAX(box.size.width, box.size.height) <= 0 ||
				MIN(box.size.width, box.size.height) <= 0) {
				continue;
			}
			else if ( box.size.height < 60 && box.size.width < 60&&(box.size.height- box.size.width)<20 && (box.size.height - box.size.width)> (-20) )
			{
				radius = MAX(boxAMS.size.height, boxAMS.size.width) / 2;
				x = boxAMS.center.x;
				//cout << "FitEllipseAMSQ:" << endl << "radius=" << radius << ",x=" << x << endl;
				paper.drawEllipseWithBox(boxAMS, fitEllipseAMSColor, 2);
			}
		}
		if (fitEllipseDirectQ) {
			boxDirect = fitEllipseDirect(pts);
			if (MAX(boxDirect.size.width, boxDirect.size.height) > MIN(boxDirect.size.width, boxDirect.size.height) * 30 ||
				MAX(box.size.width, box.size.height) <= 0 ||
				MIN(box.size.width, box.size.height) <= 0) {
				continue;
			}
			else if (box.size.height < 60 && box.size.width < 60 && (box.size.height - box.size.width) < 20 && (box.size.height - box.size.width) > (-20) )
			{
				radius = MAX(boxDirect.size.height, boxDirect.size.width) / 2;
				x = boxDirect.center.x;
				//cout << "FitEllipseDirectQ:" << endl << "radius=" << radius << ",x=" << x << endl;
				paper.drawEllipseWithBox(boxDirect, fitEllipseDirectColor, 1);
			}
			
		}
		
		//绘制拟合点
		paper.drawPoints(pts, cv::Scalar(255, 255, 255));
	}
	cv::namedWindow("fitellipse", cv::WINDOW_KEEPRATIO);
	imshow("fitellipse", paper.img);

}