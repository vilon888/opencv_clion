#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>
using namespace cv;
using namespace std;



int main()
{
    Mat SrcPic = imread("/home/vilon_tao/Projects/cv/opencv_clion/images/000000001296.jpg");
    imshow("Src Pic", SrcPic);
    Mat DstPic;
    blur(SrcPic, DstPic, Size(7, 7));
    namedWindow("均值模糊效果图", WINDOW_NORMAL);
    imshow("均值模糊效果图", DstPic);
    waitKey();
    return 0;
}