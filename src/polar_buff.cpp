#include"include_all.h"

/**
 * @function filter
 * @author Sunnie CYQ
 * @brief ��������ת��Ϊbuff����
 */

void polar_buff( bool tennis, unsigned char (&send_buf)[10], double s, double theta )
{
	char scc[5] = "0000";       //4λ��Ч����
	char thetacc[4] = "000";    //3λ��Ч����
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
	if (!int(s))   //��λ��Ĭ��λ�Ƶĵ�һλΪ��λ
	{
		for (int i = 1; i < 5; i++)
		{
			if (scc[i - 1] != '\0')
				sc[i] = scc[i - 1];
			else
				break;
		}
	}
	else    //10m����
	{
		for (int i = 0; i < 5; i++)
		{
			sc[i] = scc[i];
			if (scc[i] = '\0') break;
		}
	}

	/**************************** ANGLE ***************************/
	if (theta < 0)   //0��1��
	{
		thetac[0] = '1';  //��һλ�Ƿ���λ

		if (!int(theta * 180 / pii)) {}   //������ת
		else if (!int(theta * 180 / pii / 10))        //��ת10�����ڣ���λ��Ĭ�ϵڶ�λΪʮλ
		{
			//thetac[1] = '0';
			thetac[2] = thetacc[1];
		}
		else   //��ת����Ϊ��λ��
		{
			thetac[1] = thetacc[1];
			thetac[2] = thetacc[2];
		}
	}
	else
	{
		//thetac[0] = '0';
		if (!int(theta * 180 / pii)) {}   //������ת
		else if (!int(theta * 180 / pii / 10))        //��ת10�����ڣ���λ��Ĭ�ϵڶ�λΪʮλ
		{
			//thetac[1] = '0';
			thetac[2] = thetacc[0];
		}
		else   //��ת����Ϊ��λ��
		{
			thetac[1] = thetacc[0];
			thetac[2] = thetacc[1];
		}
	}
	//cout << "s���ַ�=" << sc << endl;
	//cout << "theta���ַ�=" << thetac << endl;


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
	//WHY�ӵ�һ������λ��ʼ��.....��֭��λ��
	send_buf[0] = '1';
	cout << "buff=" << send_buf << endl;

	if (!tennis)
	{
		send_buf[0] = '1';     //�����壬��0���ɣ��ʽ�10m����
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