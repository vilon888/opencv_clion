#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;


int main()
{

    Mat src = imread("../images/table.png");
    Mat srcClone = src.clone();


    // 检查是否为灰度图，如果不是，转化为灰度图
    Mat gray;
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    }
    else {
        gray = src;
    }


    //转化为二值图
    Mat bw;
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);


    //形态学
    Mat Structure = getStructuringElement(MORPH_RECT, Size(3, 3));

    // Apply morphology operations
    erode(bw, bw, Structure, Point(-1, -1));
    dilate(bw, bw, Structure, Point(-1, -1));


    //提取轮廓
    vector<Vec4i> hierarchy;
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(bw, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);// , Point(0, 0));

    //逼近多边形
    vector<vector<Point> > contours_poly(contours.size());

    int indexMax = 0;
    double areaMax = 0;
    for (size_t i = 0; i < contours.size(); i++)
    {
        //面积
        double area = contourArea(contours[i]);

        //筛选可能存在且不代表表的单独的行的行。
        if (area < 20) // value is randomly chosen
            continue;

        Scalar color(0, 255, 0);
        drawContours(srcClone, contours, i, color, 2, 8);

        //逼近区域成为一个形状
        approxPolyDP(Mat(contours[i]), contours_poly[i], 10, true);


        //不知为何，加了四个点的筛选之后，就没有最大的框了
        //if (contours_poly[i].size() != 4)
        //	continue;

        //找出面积最大的四边形
        if (area > areaMax)
        {
            areaMax = area;
            indexMax = i;
        }
    }


    Scalar color(0, 0, 255);
    drawContours(srcClone, contours, indexMax, color, 2, 8);
    imshow("contou1", srcClone);
    waitKey(0);


    Mat polyPic = Mat::zeros(src.size(), CV_8UC3);
    drawContours(polyPic, contours, indexMax, color, 2, 8);

    imshow("Contour2", polyPic);
    waitKey(0);


    vector<int>  hull;
    convexHull(contours_poly[indexMax], hull, false);    //检测该轮廓的凸包

    for (int j = 0; j < hull.size(); j++)
    {
        circle(src, contours_poly[indexMax][j], 10, Scalar(255, 0, 0));
    }


    //矫正后的坐标
    Mat outPic = Mat(Size(800, 800), src.type());
    Point2f srcPoints[4], dstPoints[4];
    dstPoints[0] = Point2f(0, 0);
    dstPoints[1] = Point2f(outPic.cols, 0);
    dstPoints[2] = Point2f(outPic.cols, outPic.rows);
    dstPoints[3] = Point2f(0, outPic.rows);

    //排序
    bool sorted = false;
    int n = 4;
    while (!sorted)
    {
        for (int i = 1; i < n; i++)
        {
            sorted = true;
            if (contours_poly[indexMax][i - 1].x > contours_poly[indexMax][i].x)
            {
                swap(contours_poly[indexMax][i - 1], contours_poly[indexMax][i]);
                sorted = false;
            }
        }
        n--;
    }

    if (contours_poly[indexMax][0].y < contours_poly[indexMax][1].y)
    {
        srcPoints[0] = contours_poly[indexMax][0];
        srcPoints[3] = contours_poly[indexMax][1];
    }
    else
    {
        srcPoints[0] = contours_poly[indexMax][1];
        srcPoints[3] = contours_poly[indexMax][0];
    }
    if (contours_poly[indexMax][2].y < contours_poly[indexMax][3].y)
    {
        srcPoints[1] = contours_poly[indexMax][2];
        srcPoints[2] = contours_poly[indexMax][3];
    }
    else
    {
        srcPoints[1] = contours_poly[indexMax][3];
        srcPoints[2] = contours_poly[indexMax][2];
    }

    Mat transMat = getPerspectiveTransform(srcPoints, dstPoints);    //得到变换矩阵
    warpPerspective(src, outPic, transMat, outPic.size()); //进行坐标变换

    imshow("final image", outPic);
    waitKey(0);
    return 0;
}
