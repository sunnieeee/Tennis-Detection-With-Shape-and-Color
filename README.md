[TOC]

# 基于轮廓检测

## HoughCircles

若使用霍夫圆检测，在main函数中设置 

```c++
bool HOUGH = true；
```

DRAWBACKS: 霍夫圆检测的精确度和灵敏度很难在同一个参数下保证

## FitEllipse

若使用椭圆拟合，在fitellipse.h中设置

```c++
const bool fitEllipseQ = true;
const bool fitEllipseAMSQ = false;
const bool fitEllipseDirectQ = false;
```

分别对应

 \*  1: OpenCV's original method fitEllipse which implements Fitzgibbon 1995 method.

 \*  2: The Approximate Mean Square (AMS) method fitEllipseAMS  proposed by Taubin 1991

 \*  3: The Direct least square (Direct) method fitEllipseDirect proposed by Fitzgibbon1999.

DRAWBACKS: 对小圆的检测灵敏度不如houghcircles

# 基于颜色检测

## BGR with SVM

若使用SVM，在main函数中设置

```c++
bool SVM = true;
```

DRAWBACKS: windows上的预测每帧1s左右

因为目前后续检测都是基于轮廓的，所以颜色分离后再检测效果挺不理想的诶。。。

## HSV

若使用HSV模型

我还没写好......

# 串口通信协议

发送的字符共10位

前四位：距离：个位、小数点后一位、......

第5~8位：角度：符号位、十位、个位

其中符号位0负1正，以逆时针方向为正方向

后两位：‘\0’ '\r'