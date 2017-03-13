//
//  recordedFrame.cpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#include "recordedFrame.hpp"

class recordedFrame {
public:
    recordedFrame() {
        
    }
    recordedFrame(std::string recordingString) {
        extractFrameData(recordingString);
    }
    

    int userId;
    int frameNumber;
    nite::BoundingBox boundingBox;
    cv::Point3f centerOfMass;
    //cv::Point3f positions[NUM_JOINTS_2];
    std::vector<cv::Point3f> positions;
    
    float positionConfidences[NUM_JOINTS_2];
    nite::Quaternion orientation;
    float orientationConfidence;
    
private:
    
    //TODO make this method more general
    void extractFrameData(std::string data) {
        std::vector<std::string> elements = split(data, betweenSeparator);
        
        frameNumber = std::stoi(elements[0]);
        userId = std::stoi(elements[1]);
        
        
        std::vector<std::string> bbMinMax = split(elements[2], withinSeparator);

        boundingBox = nite::BoundingBox(cvToNite(parsePoint3f(bbMinMax[0])), cvToNite(parsePoint3f(bbMinMax[1])));
        
        centerOfMass = parsePoint3f(elements[3]);
        
        int offset = 4;
        
        for(int jointIndex=0; jointIndex < NUM_JOINTS_2; jointIndex++) {
            std::vector<std::string> jointData = split(elements[jointIndex + offset], withinSeparator);
            //positions[jointIndex] = parsePoint3f(jointData[0]);
            positions.push_back(parsePoint3f(jointData[0]));
            positionConfidences[jointIndex] = std::stof(jointData[1]);
            // LATER orientation = nite::Quaternion()
            orientationConfidence = std::stof(jointData[3]);
        }
    }
    
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
    
};
