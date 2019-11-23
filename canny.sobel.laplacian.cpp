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

    Mat DstPic, edge, grayImage;

    //创建与src同类型和同大小的矩阵
    DstPic.create(img.size(), img.type());

    //将原始图转化为灰度图
    cvtColor(img, grayImage, COLOR_BGR2GRAY);

    //先使用3*3内核来降噪
    blur(grayImage, edge, Size(5, 5));

    //运行canny算子
    Canny(edge, edge, 25, 30, 3);

    imshow("canny边缘提取效果", edge);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y, dst;

    //求x方向梯度
    Sobel(grayImage, grad_x, CV_16S, 1, 0, 3, 1, 1,BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    imshow("x方向soble", abs_grad_x);

    //求y方向梯度
    Sobel(grayImage, grad_y,CV_16S,0, 1,3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_y,abs_grad_y);
    imshow("y向soble", abs_grad_y);

    //合并梯度
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
    imshow("整体方向soble", dst);


    Mat gray, dst1,abs_dst;
    //高斯滤波消除噪声
    GaussianBlur(img, img, Size(3, 3), 0, 0, BORDER_DEFAULT);
    //转换为灰度图
    cvtColor(img, gray, COLOR_RGB2GRAY);
    //使用Laplace函数
    //第三个参数：目标图像深度；第四个参数：滤波器孔径尺寸；第五个参数：比例因子；第六个参数：表示结果存入目标图
    Laplacian(gray, dst1, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    //计算绝对值，并将结果转为8位
    convertScaleAbs(dst1, abs_dst);

    imshow("laplace效果图", abs_dst);

    waitKey();
    return 0;
}