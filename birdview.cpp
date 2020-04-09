#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main()
{
    // get original image.
    cv::Mat originalImage = cv::imread("../images/road.png");

    // perspective image.
    cv::Mat perspectiveImage;

    // perspective transform
    cv::Point2f objectivePoints[4], imagePoints[4];

    // original image points.
    imagePoints[0].x = 0.0; imagePoints[0].y = 745.0;
    imagePoints[1].x = 395.0; imagePoints[1].y = 200.0;
    imagePoints[2].x = 624.0; imagePoints[2].y = 200.0;
    imagePoints[3].x = 1020.0; imagePoints[3].y = 745.0;

    // objective points of perspective image.
    // move up the perspective image : objectivePoints.y - value .
    // move left the perspective image : objectivePoints.x - value.
    double moveValueX = 0.0;
    double moveValueY = 0.0;

    objectivePoints[0].x = 46.0 + moveValueX; objectivePoints[0].y = 920.0 + moveValueY;
    objectivePoints[1].x = 46.0 + moveValueX; objectivePoints[1].y = 100.0 + moveValueY;
    objectivePoints[2].x = 600.0 + moveValueX; objectivePoints[2].y = 100.0 + moveValueY;
    objectivePoints[3].x = 600.0 + moveValueX; objectivePoints[3].y = 920.0 + moveValueY;

    for(auto p: imagePoints){
        cv::circle(originalImage, p, 1, cv::Scalar(0, 255, 0), 3);
    }

    cv::Mat transform = cv::getPerspectiveTransform(objectivePoints, imagePoints);

    // perspective.
    cv::warpPerspective(originalImage,
                        perspectiveImage,
                        transform,
                        cv::Size(originalImage.rows, originalImage.cols),
                        cv::INTER_LINEAR | cv::WARP_INVERSE_MAP);

    // cv::imshow("perspective image", perspectiveImage);
    // cvWaitKey(0);

    cv::imwrite("../temp/perspectiveImage.png", perspectiveImage);

    for(auto p: objectivePoints){
        cv::circle(perspectiveImage, p, 1, cv::Scalar(255, 0, 0), 3);
    }
    cv::imshow("Orginal road", originalImage);
    cv::imshow("Bird View Road", perspectiveImage );
    cv::waitKey();

    return 0;
}