#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>
using namespace cv;
using namespace std;



int main()
{
    Mat img = imread("/home/vilon_tao/Projects/cv/opencv_clion/images/000000001000.jpg");
    imshow("原始图", img);

    Mat out;
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
    //膨胀操作
    dilate(img, out, element);
    imshow("膨胀操作", out);


    erode(img, out, element);
    imshow("腐蚀操作", out);

    morphologyEx(img, out, MORPH_TOPHAT, element);
    imshow("形态学处理操作", out);

    waitKey();


    return 0;
}