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

//    Mat dst = Mat::zeros(512, 512, CV_8UC3); //我要转化为512*512大小的
//    resize(img, dst, dst.size());
//
//    imshow("尺寸调整之后", dst);

    Mat dst;
    resize(img, dst, Size(),0.5,0.5);//我长宽都变为原来的0.5倍

    imshow("尺寸调整之后", dst);


    Mat dst1,dst2;
    pyrUp(img, dst1, Size(img.cols*2, img.rows*2)); //放大一倍
    pyrDown(img, dst2, Size(img.cols * 0.5, img.rows * 0.5)); //缩小为原来的一半
    imshow("尺寸放大之后", dst1);
    imshow("尺寸缩小之后", dst2);

    waitKey();
    return 0;
}