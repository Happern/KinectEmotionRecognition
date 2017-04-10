//
//  happernCore.cpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#include "happernCore.hpp"


 cv::Point3f operator-(const cv::Point3f p1, const cv::Point3f p2) {
    return cv::Point3f(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}


 cv::Point3f operator+(const cv::Point3f p1, const cv::Point3f p2) {
    return cv::Point3f(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

 std::vector<float> minMaxPoints(cv::Point3f * list, int numElements) {
    cv::Point3f firstPoint = list[0];
    float xMax = firstPoint.x;
    float yMax = firstPoint.y;
    float zMax = firstPoint.z;
    
    float xMin = firstPoint.x;
    float yMin = firstPoint.y;
    float zMin = firstPoint.z;
    
    cv::Point3f currPoint;
    
    for(int ind = 1; ind < numElements; ind++) {
        currPoint = list[ind];
        
        xMax = cv::max(xMax, currPoint.x);
        yMax = cv::max(yMax, currPoint.y);
        zMax = cv::max(zMax, currPoint.z);
        
        xMin = cv::min(xMin, currPoint.x);
        yMin = cv::min(yMin, currPoint.y);
        zMin = cv::min(zMin, currPoint.z);
        
        std::cout << xMin << " " << yMin << " " << zMin << "\n";
    }
    
    std::vector<float> coords = {xMax, xMin, yMax, yMin, zMax, zMin};
    return coords;
}

 std::vector<float> minMaxPoints(std::vector<cv::Point3f> list) {
    cv::Point3f firstPoint = list[0];
    float xMax = firstPoint.x;
    float yMax = firstPoint.y;
    float zMax = firstPoint.z;
    
    float xMin = firstPoint.x;
    float yMin = firstPoint.y;
    float zMin = firstPoint.z;
    
    cv::Point3f currPoint;
    
    for(int ind = 1; ind < list.size(); ind++) {
        currPoint = list[ind];
        
        xMax = cv::max(xMax, currPoint.x);
        yMax = cv::max(yMax, currPoint.y);
        zMax = cv::max(zMax, currPoint.z);
        
        xMin = cv::min(xMin, currPoint.x);
        yMin = cv::min(yMin, currPoint.y);
        zMin = cv::min(zMin, currPoint.z);
        
        std::cout << xMin << " " << yMin << " " << zMin << "\n";
    }
    
    std::vector<float> coords = {xMax, xMin, yMax, yMin, zMax, zMin};
    return coords;
}

 cv::Point3f niteToCv(nite::Point3f p) {
    return cv::Point3f(p.x, p.y, p.z);
}

 cv::Point3f niteToCv(NitePoint3f p) {
    return cv::Point3f(p.x, p.y, p.z);
}

 nite::Point3f cvToNite(cv::Point3f p) {
    return nite::Point3f(p.x, p.y, p.z);
}

 cv::Point3f absPoint3f(cv::Point3f p) {
    return cv::Point3f(fabs(p.x), fabs(p.y), fabs(p.z));
}

 cv::Point3f crossProduct(cv::Point3f p1, cv::Point3f p2) {
    return cv::Point3f((p1.y * p2.z - p1.z * p2.y), (p1.z * p2.x - p2.x * p1.z), (p1.z * p2.y - p1.y * p2.x));
}

 float dotProduct(cv::Point3f p1, cv::Point3f p2) {
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

 cv::Point3f divideByScalar(cv::Point3f p, float scalar) {
    return cv::Point3f(p.x/scalar, p.y/scalar, p.z/scalar);
}

 void printPoint(cv::Point3f p) {
    std::cout << p.x << " " << p.y << " " << p.z << "\n";
}

 cv::Point3f pointSymmetricToLine(cv::Point3f base1, cv::Point3f base2, cv::Point3f p3) {
    cv::Point3f baseVector = divideByScalar((base1 - base2), norm(base2 - base1));
    cv::Point3f sideVector = base1 - p3;
    
    float distanceToProjection = dotProduct(baseVector, sideVector);
    
    cv::Point3f projectionOnLine = base2 + distanceToProjection * baseVector;
    cv::Point3f distanceFromTopToBase = p3 - projectionOnLine;
    return projectionOnLine - distanceFromTopToBase;
}

 std::string point3fToString(cv::Point3f p) {
    return std::to_string(p.x) + " " + std::to_string(p.y) + " " + std::to_string(p.z);
}

 std::string point3fToString(NitePoint3f p) {
    return point3fToString(niteToCv(p));
}

 std::string quaternionToString(nite::Quaternion q) {
    //TODO implement
    return std::to_string(q.w) + " " + std::to_string(q.x) + " " + std::to_string(q.y) + " " + std::to_string(q.z);;
}

const nite::Quaternion operator *(const nite::Quaternion q1, const nite::Quaternion q2)
{	return nite::Quaternion(q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
                            q1.y * q2.z - q1.z * q2.y + q1.w * q2.x + q1.x * q2.w,
                            q1.z * q2.x - q1.x * q2.z + q1.w * q2.y + q1.y * q2.w,
                            q1.x * q2.y - q1.y * q2.x + q1.w * q2.z + q1.z * q2.w);
}

// for reading
std::vector<std::string> split(std::string str, std::string delimiter) {
    std::vector<std::string> array;
    std::size_t pos = 0, found;
    while((found = str.find_first_of(delimiter, pos)) != std::string::npos) {
        array.push_back(str.substr(pos, found - pos));
        pos = found+1;
    }
    array.push_back(str.substr(pos));
    
    return array;
}

cv::Point3f parsePoint3f(std::string point) {
    std::vector<std::string> coords = split(point, pointDelimiter);
    
    return cv::Point3f(std::stof(coords[0]), std::stof(coords[1]), std::stof(coords[2]));
}

nite::Quaternion parseQuaternion(std::string quaternion) {
    std::vector<std::string> comps = split(quaternion, pointDelimiter);
    
    return nite::Quaternion(std::stof(comps[0]), std::stof(comps[1]), std::stof(comps[2]), std::stof(comps[3]));
}

bool checkZeroQuaternion(nite::Quaternion q) {
    return q.w == 0 && q.x == 0 && q.y == 0 && q.z == 0;
}
