#ifndef INCLUDE_ALL_H
#define INCLUDE_ALL_H

/// INCLUDE
#include <opencv2/opencv.hpp>

#include<stdio.h>
#include<iostream>

using namespace std;

/// MACRO
#define k (double)0.9    //ͼƬѹ������

#define pii (double)3.1415926
#define car_height (double)0.205   //���ߣ���λm
#define cam_height (double)0.45   //���ߣ���λm
#define pixel_radius (int)34  //����0.5mʱ��������ذ뾶���������������
#define trans (double)17.0   //ת��ϵ����pixel_radius*0.5m
#define t_diameter (double)0.065   //����ֱ������λm
#define d_camcar (int)70  //���ƫ��С�����ĵľ��룬�����Ҹ�

#define maxB   (uchar)150
#define minB   (uchar)0
#define maxG   (uchar)255
#define minG   (uchar)180
#define maxR   (uchar)255
#define minR   (uchar)0

#define maxH   (uchar)77
#define minH   (uchar)26
#define maxS   (uchar)255
#define minS   (uchar)43
#define maxV   (uchar)255
#define minV   (uchar)46





#endif // !INCLUDE_ALL_H
