#include"include_all.h"

/**
 * @function filter
 * @author Sunnie CYQ
 * @brief  ����ת�����õ�������
 */

void cartesian_to_polar(double x, int radius, double centre_x, double &s, double &theta)
{
	double d = 0;                        //�����������ľ��룬��λm
	double dx = 0;                      //�����˵ѿ�������ϵ�£���������ƫ��С�����ĵľ���
	
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
	//cout << "theta=" << theta << "=" << theta * 180 / pii << "��" << endl << endl;

}