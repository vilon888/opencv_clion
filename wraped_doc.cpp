#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/features2d.hpp"
//#include "opencv2/xfeatures2d.hpp"
//using namespace cv::xfeatures2d;
using namespace cv;
using namespace std;

/****
 1.首先对输入图像进行二值变换，然后进行轮廓分析，得到文档轮廓

 2.调用approxPolyDP函数进行轮廓逼近，找到四个顶点坐标，这里需要注意一下，使用approxPolyDP函数进行轮廓逼近的时候，最后一个参数是表示轮廓逼近得到轮廓与原来轮廓之后的距离差值，值越小越逼近真实轮廓。我们这里希望得到一个大致近似的矩形即可，所以该值要尽可能的大一点，这个也是使用这个函数的一个编程技巧。

 3.得到四个点之后，创建目标点，然后调用findHomography，得到变换矩阵H，基于H完成透视变换得到最终的输出。
 ****/

/***
 *
 *
 * @param pointO
 * @param point1
 * @return
 */

float getDistance(Point2f pointO, Point2f point1)
{
    float distance;
    distance = powf((pointO.x - point1.x), 2) + powf((pointO.y - point1.y), 2);
    distance = sqrtf(distance);
    return distance;
}

int main()
{

    Mat src = imread("../images/wraped_doc.png");
    Mat image = src.clone();
    Mat gray, binary;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

// 发现轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;
    findContours(binary, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    int index = -1;
    double max = -1;
    double angle = 0;
    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > max) {
            max = area;
            index = i;
        }
    }
    drawContours(image, contours, index, Scalar(0, 255, 0), 2, 8);
    imshow("轮廓", image);
    waitKey(0);

    // 寻找矩形轮廓四个点
    Mat approxCurves;
    approxPolyDP(contours[index], approxCurves, 100, true);
    printf("rows : %d, cols : %d \n", approxCurves.rows, approxCurves.cols);
    vector<Point2f> srcPts;
    for (int n = 0; n < approxCurves.rows; n++) {
        Vec2i pt = approxCurves.at<Vec2i>(n, 0);
        printf("pt.x= %d, pt.y = %d \n", pt[0], pt[1]);
        srcPts.push_back(Point2f(pt[0], pt[1]));
        circle(image, Point(pt[0], pt[1]), 12, Scalar(0, 0, 255), 8, 8, 0);
    }
    imwrite("../temp/result.png", image);
    vector<Point2f> dstPts;
    int rows = (int)getDistance(srcPts[0],srcPts[1]);
    int cols = (int)getDistance(srcPts[1],srcPts[2]);
    Mat dst(rows, cols, CV_8UC3);
    dstPts.push_back(Point2f(0., 0.));
    dstPts.push_back(Point2f(0., rows));

    dstPts.push_back(Point2f(cols, rows));
    dstPts.push_back(Point2f(cols, 0.));

    Mat h = findHomography(srcPts, dstPts);


    warpPerspective(src, dst, h, dst.size());
    imwrite("../temp/correct_document.png", dst);
    imshow("corrected document", dst);
    waitKey(0);
    return 0;
}
//
//#include <opencv2/opencv.hpp>
//#include "opencv2/xfeatures2d.hpp"
//#include "opencv2/features2d.hpp"
//
//using namespace std;
//using namespace cv;
//using namespace cv::xfeatures2d;
//
//const int MAX_FEATURES = 500;
//const float GOOD_MATCH_PERCENT = 0.15f;
//
//
//void alignImages(Mat &im1, Mat &im2, Mat &im1Reg, Mat &h)
//
//{
//
//    // Convert images to grayscale
//    Mat im1Gray, im2Gray;
//    cvtColor(im1, im1Gray, COLOR_BGR2GRAY);
//    cvtColor(im2, im2Gray, COLOR_BGR2GRAY);
//
//    // Variables to store keypoints and descriptors
//    std::vector<KeyPoint> keypoints1, keypoints2;
//    Mat descriptors1, descriptors2;
//
//    // Detect ORB features and compute descriptors.
//    Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);
//    orb->detectAndCompute(im1Gray, Mat(), keypoints1, descriptors1);
//    orb->detectAndCompute(im2Gray, Mat(), keypoints2, descriptors2);
//
//    // Match features.
//    std::vector<DMatch> matches;
//    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
//    matcher->match(descriptors1, descriptors2, matches, Mat());
//
//    // Sort matches by score
//    std::sort(matches.begin(), matches.end());
//
//    // Remove not so good matches
//    const int numGoodMatches = matches.size() * GOOD_MATCH_PERCENT;
//    matches.erase(matches.begin()+numGoodMatches, matches.end());
//
//
//    // Draw top matches
//    Mat imMatches;
//    drawMatches(im1, keypoints1, im2, keypoints2, matches, imMatches);
//    imwrite("matches.jpg", imMatches);
//
//
//    // Extract location of good matches
//    std::vector<Point2f> points1, points2;
//
//    for( size_t i = 0; i < matches.size(); i++ )
//    {
//        points1.push_back( keypoints1[ matches[i].queryIdx ].pt );
//        points2.push_back( keypoints2[ matches[i].trainIdx ].pt );
//    }
//
//    // Find homography
//    h = findHomography( points1, points2, RANSAC );
//
//    // Use homography to warp image
//    warpPerspective(im1, im1Reg, h, im2.size());
//
//}
//
//
//int main(int argc, char **argv)
//{
//    // Read reference image
//    string refFilename("../images/form.jpg");
//    cout << "Reading reference image : " << refFilename << endl;
//    Mat imReference = imread(refFilename);
//
//
//    // Read image to be aligned
//    string imFilename("../images/scanned-form.jpg");
//    cout << "Reading image to align : " << imFilename << endl;
//    Mat im = imread(imFilename);
//
//
//    // Registered image will be resotred in imReg.
//    // The estimated homography will be stored in h.
//    Mat imReg, h;
//
//    // Align images
//    cout << "Aligning images ..." << endl;
//    alignImages(im, imReference, imReg, h);
//
//    // Write aligned image to disk.
//    string outFilename("../temp/aligned.jpg");
//    cout << "Saving aligned image : " << outFilename << endl;
//    imwrite(outFilename, imReg);
//
//    // Print estimated homography
//    cout << "Estimated homography : \n" << h << endl;
//
//}