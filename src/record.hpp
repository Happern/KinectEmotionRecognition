//
//  record.hpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#ifndef record_hpp
#define record_hpp

#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>

#include "NiTE.h"

#include "happernCore.hpp"
#include "fileConstants.hpp"

/** Available joints in skeleton */
//find a better way to do this
const nite::JointType JOINTS[15] =
{
    nite::JOINT_HEAD,
    nite::JOINT_NECK,
    
    nite::JOINT_LEFT_SHOULDER,
    nite::JOINT_RIGHT_SHOULDER,
    nite::JOINT_LEFT_ELBOW,
    nite::JOINT_RIGHT_ELBOW,
    nite::JOINT_LEFT_HAND,
    nite::JOINT_RIGHT_HAND,
    
    nite::JOINT_TORSO,
    
    nite::JOINT_LEFT_HIP,
    nite::JOINT_RIGHT_HIP,
    nite::JOINT_LEFT_KNEE,
    nite::JOINT_RIGHT_KNEE,
    nite::JOINT_LEFT_FOOT,
    nite::JOINT_RIGHT_FOOT,
};


void startRecording(std::string path);
void writeToFile(std::string log);
void recordData(int frameCount, nite::UserData);
std::string getUserData(nite::UserData user);
std::string getJointData(nite::Skeleton skeleton);


#endif /* record_hpp */
