#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>
using namespace cv;
using namespace std;



int main()
{
    Mat img = imread("/home/vilon_tao/Projects/cv/opencv_clion/images/000000001296.jpg");
    imshow("原始图", img);
    Mat dst;
    cvtColor(img, img, COLOR_BGR2GRAY);
    imshow("灰度图", img);
    equalizeHist(img, dst);

    imshow("直方图均衡化", dst);
    waitKey();
    return 0;
}