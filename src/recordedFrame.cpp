//
//  recordedFrame.cpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#include "recordedFrame.hpp"


    recordedFrame::recordedFrame() {
        
    }
     recordedFrame::recordedFrame(std::string recordingString) {
        extractFrameData(recordingString);
    }

    
    //TODO make this method more general
    void  recordedFrame::extractFrameData(std::string data) {
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
            
            orientations.push_back(parseQuaternion(jointData[2]));
            orientationConfidences[jointIndex] = std::stof(jointData[3]);
        }
    }
