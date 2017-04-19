//
//  cvUtils.hpp
//  KinectEmotionRecognition
//
//  Created by Happern on 19/04/2017.
//
//

#ifndef cvUtils_hpp
#define cvUtils_hpp

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"

// cv
cv::Point3f operator-(const cv::Point3f p1, const cv::Point3f p2);
cv::Point3f operator+(const cv::Point3f p1, const cv::Point3f p2);
cv::Mat copyVectorToMat(std::vector<std::vector<float>> vector, int matCols);
cv::Mat copyVectorToMat(std::vector<float> vector);
cv::Point3f absPoint3f(cv::Point3f p);
cv::Point3f crossProduct(cv::Point3f p1, cv::Point3f p2);
float dotProduct(cv::Point3f p1, cv::Point3f p2);
cv::Point3f divideByScalar(cv::Point3f p, float scalar);
void printPoint(cv::Point3f p);

std::string point3fToString(cv::Point3f p);
std::vector<float> minMaxPoints(std::vector<cv::Point3f> list);
std::vector<float> minMaxPoints(cv::Point3f * list, int numElements);
cv::Point3f pointSymmetricToLine(cv::Point3f base1, cv::Point3f base2, cv::Point3f p3);

#endif /* cvUtils_hpp */
