//
//  frameFeatures.hpp
//  kinectTest
//
//  Created by Happern on 03/02/2017.
//
//

#ifndef frameFeatures_hpp
#define frameFeatures_hpp

#include <stdio.h>
#include "Nite.h"
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"

#include "happernCore.hpp"

const int NUM_JOINTS = 15;
const int NUM_KINEMATIC_JOINTS = 6;
const int NUM_SYMM_TRI_JOINTS = 4;
const int NUM_SIDED_JOINTS = 12;

using namespace nite;
const int KINEMATIC_JOINTS[NUM_KINEMATIC_JOINTS] = {JOINT_LEFT_HAND, JOINT_RIGHT_HAND, JOINT_LEFT_ELBOW, JOINT_RIGHT_ELBOW, JOINT_LEFT_SHOULDER, JOINT_RIGHT_SHOULDER};

const int SIDED_JOINTS[NUM_SIDED_JOINTS] = {JOINT_LEFT_HAND, JOINT_RIGHT_HAND, JOINT_LEFT_ELBOW, JOINT_RIGHT_ELBOW, JOINT_LEFT_SHOULDER, JOINT_RIGHT_SHOULDER, JOINT_LEFT_HIP, JOINT_RIGHT_HIP, JOINT_LEFT_KNEE, JOINT_RIGHT_KNEE, JOINT_LEFT_FOOT, JOINT_RIGHT_FOOT};

const int SYMM_TRI_JOINTS[NUM_SYMM_TRI_JOINTS] = {JOINT_LEFT_HAND, JOINT_RIGHT_HAND, JOINT_LEFT_SHOULDER, JOINT_RIGHT_SHOULDER};

class frameFeatures {
public:
    frameFeatures();
    frameFeatures(const nite::Skeleton& skeleton, const nite::Point3f com, frameFeatures& previousFrame);
    frameFeatures(std::vector<cv::Point3f> _position, std::vector<nite::Quaternion> _orientations_, const cv::Point3f _com, frameFeatures& previousFrame);
private:
    cv::Point3f centerOfMass;
    
    //cv::Point3f position[NUM_JOINTS] ;
    std::vector<cv::Point3f> position;
    
    cv::Point3f velocity[NUM_JOINTS] ;
    float velocityNorm[NUM_JOINTS];
    
    cv::Point3f acceleration[NUM_JOINTS];
    cv::Point3f jerk[NUM_JOINTS];
    
    float symmetry3d;
    float symmetryTriangular[NUM_SYMM_TRI_JOINTS / 2];
    
    cv::Point3f leaningPosition;
    cv::Point3f leaningVelocity;
    
    cv::Point3f distFromHead[NUM_JOINTS];
    cv::Point3f distFromBody[NUM_JOINTS];
    
    float kineticEnergy;
    float jointEnergyWeights[NUM_JOINTS];
    
    float contractionIndex;
    float dynamicContractionIndex;
    
    nite::Quaternion direction;
    std::vector<nite::Quaternion> orientations;
    
    void initPositionsAndOrientations(const nite::Skeleton& skeleton);
    void initKinematicFeatures(frameFeatures& previousFrame);
    void initPostureFeatures(frameFeatures& previousFrame);
    float calculateKineticEnergy();
    float calculateContractionIndex();
    cv::Point3f calculateLeaningPosition();
    cv::Point3f calculateDistanceFromHead(cv::Point3f headPosition, cv::Point3f jointPosition);
    cv::Point3f calculateDistanceFromBody(cv::Point3f jointPosition);
    float calculate3dSymmetry();
    float calculateSymIndex(float leftDistance, float rightDistance);
    float calculateTriangularSymmetry(int leftJointIndex, int rightJointIndex);
};

#endif /* frameFeatures_hpp */
