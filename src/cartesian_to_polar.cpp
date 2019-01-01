#include"include_all.h"

/**
 * @function filter
 * @author Sunnie CYQ
 * @brief  坐标转换，得到极坐标
 */

void cartesian_to_polar(double x, int radius, double centre_x, double &s, double &theta)
{
	double d = 0;                        //摄像机与网球的距离，单位m
	double dx = 0;                      //机器人笛卡尔坐标系下，网球中心偏离小车中心的距离
	
	if (radius)
	{
		d = trans / radius;
		dx = (centre_x - x) * t_diameter / (2 * pixel_radius);
	}

	if (d > cam_height)                   
	{
		s = sqrt(d*d - cam_height * cam_height);
		theta = atan(dx / s);
	}
	else
	{
		s = 0;
		theta = 0;
	}
	
	//cout << "dx =" << dx << "m, d =" << d << "m, s =" << s << "m" << endl;
	//cout << "theta=" << theta << "=" << theta * 180 / pii << "度" << endl << endl;

}