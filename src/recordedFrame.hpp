//
//  recordedFrame.hpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#ifndef recordedFrame_hpp
#define recordedFrame_hpp

#include <stdio.h>
#include <string>
#include <vector>


#include "NiTE.h"
#include "opencv2/core/core.hpp"

#include "fileConstants.hpp"
#include "happernCore.hpp"

// two is appended since NUM_JOINS defined elsewhere, TODO find a better solution
const int NUM_JOINTS_2 = 15;

class recordedFrame {
public:
    recordedFrame();
    recordedFrame(std::string recordingString);
    
    
    int userId;
    int frameNumber;
    nite::BoundingBox boundingBox;
    cv::Point3f centerOfMass;
    //cv::Point3f positions[NUM_JOINTS_2];
    std::vector<cv::Point3f> positions;
    std::vector<nite::Quaternion> orientations;
    
    float positionConfidences[NUM_JOINTS_2];
    float orientationConfidences[NUM_JOINTS_2];
    
private:
    void extractFrameData(std::string data);
};

#endif /* recordedFrame_hpp */
