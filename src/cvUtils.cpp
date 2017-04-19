//
//  cvUtils.cpp
//  KinectEmotionRecognition
//
//  Created by Happern on 19/04/2017.
//
//

#include "cvUtils.hpp"

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
        
        //std::cout << xMin << " " << yMin << " " << zMin << "\n";
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
        
        //std::cout << xMin << " " << yMin << " " << zMin << "\n";
    }
    
    std::vector<float> coords = {xMax, xMin, yMax, yMin, zMax, zMin};
    return coords;
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


cv::Mat copyVectorToMat(std::vector<std::vector<float>> vector, int matCols) {
    int matRows = vector.size();
    
    cv::Mat matrx(matRows, matCols, CV_32FC1);
    
    for(int row = 0; row < matRows; row++) {
        std::vector<float> vRow = vector[row];
        
        for (int col = 0; col < matCols; col++) {
            matrx.at<float>(row,col) = vRow[col];
        }
    }
    
    return matrx;
}

cv::Mat copyVectorToMat(std::vector<float> vector) {
    int matRows = vector.size();
    
    cv::Mat matrx(matRows, 1, CV_32SC1);
    
    for(int row = 0; row < matRows; row++) {
        matrx.at<int>(row,1) = round(vector[row]);
    }
    
    return matrx;
}

