//
//  happernCore.hpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#ifndef happernCore_hpp
#define happernCore_hpp

#include <stdio.h>
#include "NiTE.h"
#include <iostream>
#include <vector>
#include <string>
#include "opencv2/core/core.hpp"

#include "fileConstants.hpp"


cv::Point3f operator-(const cv::Point3f p1, const cv::Point3f p2);
cv::Point3f operator+(const cv::Point3f p1, const cv::Point3f p2);
std::vector<float> minMaxPoints(std::vector<cv::Point3f> list);
std::vector<float> minMaxPoints(cv::Point3f * list, int numElements);
cv::Point3f niteToCv(nite::Point3f p);
cv::Point3f niteToCv(NitePoint3f p);
nite::Point3f cvToNite(cv::Point3f p);
cv::Point3f absPoint3f(cv::Point3f p);
cv::Point3f crossProduct(cv::Point3f p1, cv::Point3f p2);
float dotProduct(cv::Point3f p1, cv::Point3f p2);
cv::Point3f divideByScalar(cv::Point3f p, float scalar);
void printPoint(cv::Point3f p);
cv::Point3f pointSymmetricToLine(cv::Point3f base1, cv::Point3f base2, cv::Point3f p3);
std::string point3fToString(cv::Point3f p);
std::string point3fToString(NitePoint3f p);
std::string quaternionToString(nite::Quaternion q);
const nite::Quaternion operator *(const nite::Quaternion q1, const nite::Quaternion q2);
bool checkZeroQuaternion(nite::Quaternion q);

// for reading
std::vector<std::string> split(std::string str, std::string delimiter);
cv::Point3f parsePoint3f(std::string point);
nite::Quaternion parseQuaternion(std::string quaternion);



#endif /* happernCore_hpp */
