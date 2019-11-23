#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>
using namespace cv;
using namespace std;



int main()
{

    Mat image = imread("/home/vilon_tao/Projects/cv/opencv_clion/images/000000001000.jpg", IMREAD_GRAYSCALE); //注意了，必须是载入灰度图
    if (image.empty())
    {
        cout << "read image failure" << endl;
        return -1;
    }

    // 全局二值化
    int th = 100;
    Mat global;

    threshold(image, global, th, 255, THRESH_BINARY_INV);

    // 局部二值化
    int blockSize = 25;
    int constValue = 10;
    Mat local;
    adaptiveThreshold(image, local, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, blockSize, constValue);

    imshow("原始二值图", image);
    imshow("全局二值化", global);
    imshow("局部二值化", local);

    waitKey(0);
    return 0;
}