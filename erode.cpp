#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>
using namespace cv;
using namespace std;



int main()
{
    Mat SrcPic = imread("/home/vilon_tao/Projects/cv/opencv_clion/images/000000001296.jpg", IMREAD_GRAYSCALE);
    imshow("Src Pic", SrcPic);
    Mat element = getStructuringElement(MORPH_CROSS, Size(15, 15)); //getStructuringElement函数返回的是指定形状和尺寸的结构元素
    Mat DstPic;
    erode(SrcPic, DstPic, element, Point(-1,-1), 2,
          BORDER_REPLICATE); //腐蚀操作
    imshow("腐蚀效果图", DstPic);
    waitKey();
    return 0;
}