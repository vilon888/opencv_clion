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
    Mat out;
    boxFilter(img, out, -1, Size(5, 5));//-1指原图深度
    imshow("方框滤波", out);


    blur(img, out,Size(5, 5));//-1指原图深度
    imshow("均值滤波", out);

    GaussianBlur(img, out, Size(3, 3), 0, 0);
    imshow("高斯滤波", out);

    medianBlur(img, out, 7);//第三个参数表示孔径的线性尺寸，它的值必须是大于1的奇数
    imshow("中值滤波", out);


    bilateralFilter(img, out, 25, 25 * 2, 25 / 2);
    imshow("双边滤波", out);
    
    waitKey();
    return 0;
}