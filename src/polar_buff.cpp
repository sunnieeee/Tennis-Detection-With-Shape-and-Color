#include"include_all.h"

/**
 * @function filter
 * @author Sunnie CYQ
 * @brief 将极坐标转化为buff数组
 */

void polar_buff( bool tennis, unsigned char (&send_buf)[10], double s, double theta )
{
	char scc[5] = "0000";       //4位有效数字
	char thetacc[4] = "000";    //3位有效数字
	char sc[5] = "0000";
	char thetac[4] = "000";

	int si = (int)(s*1e3);
	int thetai = (int)(theta * 180 / pii);
	//cout << "s=" << s << endl;
	//cout << "si=" << si << endl;

	sprintf_s(scc, "%d", si);
	sprintf_s(thetacc, "%d", thetai);
	/*cout << "start:" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << thetacc[i] << endl;
	}
	cout << "end" << endl;*/

	/************************ DISTANCE ***********************/
	if (!int(s))   //下位机默认位移的第一位为个位
	{
		for (int i = 1; i < 5; i++)
		{
			if (scc[i - 1] != '\0')
				sc[i] = scc[i - 1];
			else
				break;
		}
	}
	else    //10m以内
	{
		for (int i = 0; i < 5; i++)
		{
			sc[i] = scc[i];
			if (scc[i] = '\0') break;
		}
	}

	/**************************** ANGLE ***************************/
	if (theta < 0)   //0正1负
	{
		thetac[0] = '1';  //第一位是符号位

		if (!int(theta * 180 / pii)) {}   //不用旋转
		else if (!int(theta * 180 / pii / 10))        //旋转10度以内，下位机默认第二位为十位
		{
			//thetac[1] = '0';
			thetac[2] = thetacc[1];
		}
		else   //旋转度数为两位数
		{
			thetac[1] = thetacc[1];
			thetac[2] = thetacc[2];
		}
	}
	else
	{
		//thetac[0] = '0';
		if (!int(theta * 180 / pii)) {}   //不用旋转
		else if (!int(theta * 180 / pii / 10))        //旋转10度以内，下位机默认第二位为十位
		{
			//thetac[1] = '0';
			thetac[2] = thetacc[0];
		}
		else   //旋转度数为两位数
		{
			thetac[1] = thetacc[0];
			thetac[2] = thetacc[1];
		}
	}
	//cout << "s的字符=" << sc << endl;
	//cout << "theta的字符=" << thetac << endl;


	/**************************** SEND BUFF ***************************/

	for (int i = 0; i < 4; i++)
	{
		send_buf[i] = sc[i];
	}
	send_buf[4] = thetac[0];
	send_buf[5] = '0';
	send_buf[6] = thetac[1];
	send_buf[7] = thetac[2];
	send_buf[8] = thetac[3];
	//send_buf[8] = '\n';
	send_buf[9] = '\r';
	//WHY从第一个非零位开始收.....蜜汁下位机
	send_buf[0] = '1';
	cout << "buff=" << send_buf << endl;

	if (!tennis)
	{
		send_buf[0] = '1';     //无意义，非0即可，故仅10m以内
		//send_buf[0] = '0';
		send_buf[1] = '0';
		send_buf[2] = '0';
		send_buf[3] = '0';
		send_buf[4] = '0';
		send_buf[5] = '0';
		send_buf[6] = '0';
		send_buf[7] = '0';
		send_buf[8] = '\0';
		send_buf[9] = '\r';
		cout << "buff=" << send_buf << endl;

	}
}