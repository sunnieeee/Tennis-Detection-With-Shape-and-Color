#ifndef INCLUDE_ALL_H
#define INCLUDE_ALL_H

/// INCLUDE
#include <opencv2/opencv.hpp>

#include<stdio.h>
#include<iostream>

using namespace std;

/// MACRO
#define k (double)0.9    //图片压缩比例

#define pii (double)3.1415926
#define car_height (double)0.205   //车高，单位m
#define cam_height (double)0.45   //车高，单位m
#define pixel_radius (int)34  //距离0.5m时网球的像素半径，由相机参数决定
#define trans (double)17.0   //转换系数，pixel_radius*0.5m
#define t_diameter (double)0.065   //网球直径，单位m
#define d_camcar (int)70  //相机偏离小车中心的距离，左正右负

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
