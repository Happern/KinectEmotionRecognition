//
//  frameFeatures.cpp
//  kinectTest
//
//  Created by Happern on 03/02/2017.
//
//

#include "frameFeatures.hpp"


    frameFeatures::frameFeatures() {
        // fill in dummy data - accessed in proceeding frameFeatures
        for(int jointIndex = 0; jointIndex < NUM_JOINTS; jointIndex++) {
            cv::Point3f dummy(0,0,0);
            position.push_back(dummy);
            acceleration[jointIndex] = dummy;
            jerk[jointIndex] = dummy;
        }
    }
    frameFeatures::frameFeatures(const nite::Skeleton& skeleton, const nite::Point3f com, frameFeatures& previousFrame) {
        centerOfMass = niteToCv(com);
        initPositionsAndOrientations(skeleton);
        initKinematicFeatures(previousFrame);
    }

    // variable names preceded with _ are assigned to a class variable without modification
    frameFeatures::frameFeatures(std::vector<cv::Point3f> _position, std::vector<nite::Quaternion> _orientations, const cv::Point3f _com, frameFeatures& previousFrame) {
        position = _position;
        orientations = _orientations;
        centerOfMass = _com;
        initKinematicFeatures(previousFrame);
    }
   
    
    void frameFeatures::initPositionsAndOrientations(const nite::Skeleton& skeleton) {
        for (int i = nite::JOINT_HEAD; i < nite::JOINT_RIGHT_FOOT; i++) {
            //position[i] = niteToCv(skeleton.getJoint((JointType)i).getPosition());
            nite::SkeletonJoint joint = skeleton.getJoint((JointType)i);
            position.push_back(niteToCv(joint.getPosition()));
            orientations.push_back(joint.getOrientation());
        }
    }
    
    void frameFeatures::initKinematicFeatures(frameFeatures& previousFrame) {
        nite::Quaternion compositeRotation(1,1,1,1);
        nite::Quaternion currentOrientation;
        
        // TODO implement better way to loop through all the joints
        for (int i = nite::JOINT_HEAD; i < nite::JOINT_RIGHT_FOOT; i++) {
            velocity[i] = position[i] - previousFrame.position[i];
            velocityNorm[i] = cv::norm(velocity[i]);
            
            // composition of all non-zero orientations
            currentOrientation = orientations[i];
            if (!checkZeroQuaternion(currentOrientation)) {
                compositeRotation = compositeRotation * orientations[i];
            }
        }
        
        for (int joint: KINEMATIC_JOINTS) {
            acceleration[joint] = velocity[joint] - previousFrame.velocity[joint];
            jerk[joint] = jerk[joint] - previousFrame.jerk[joint];
        }
        
        //TODO add direction
        // composite rotation/orientation will be used as the directio for now
        direction = compositeRotation;
        
        // elbow orientations will be used separately, and possibly shoulders
     
        //kineticEnergy = calculateKineticEnergy();
    }
    
    void frameFeatures::initPostureFeatures(frameFeatures& previousFrame) {
        contractionIndex = calculateContractionIndex();
        dynamicContractionIndex = contractionIndex - previousFrame.contractionIndex;
        
        //calculate leaning position
        //calculate leaning velocity
        
        for (int joint: SIDED_JOINTS) {
            distFromBody[joint] = calculateDistanceFromBody(position[joint]);
        }

        cv::Point3f headPosition = position[JOINT_HEAD];
        
        for (int joint: SYMM_TRI_JOINTS) {
            distFromHead[joint] = calculateDistanceFromHead(headPosition, position[joint]);
        }
        
        symmetry3d = calculate3dSymmetry();
        
        for(int ind = 0; ind < NUM_SYMM_TRI_JOINTS; ind += 2) {
            symmetryTriangular[ind/2]  = calculateTriangularSymmetry(SYMM_TRI_JOINTS[ind], SYMM_TRI_JOINTS[ind +1]);
        }
    }
    
    float frameFeatures::calculateKineticEnergy() {
        float kineticEnergy = 0;
        
        for(int jointIndex = 0; jointIndex < NUM_JOINTS; jointIndex++) {
            kineticEnergy += velocityNorm[jointIndex] * jointEnergyWeights[jointIndex];
        }
        
        return kineticEnergy;
    }
    
    float frameFeatures::calculateContractionIndex() {
        std::vector<float> coords = minMaxPoints(position);
        
        return (coords[0] - coords[1]) * (coords[2] - coords[3]) * (coords[4] - coords[5]);
    }
    
    cv::Point3f frameFeatures::calculateLeaningPosition() {
        //TODO implement
        
        cv::Point3f p;
        return p;
    }
    
    cv::Point3f frameFeatures::calculateDistanceFromHead(cv::Point3f headPosition, cv::Point3f jointPosition) {
        return headPosition - jointPosition;
    }
    
    cv::Point3f frameFeatures::calculateDistanceFromBody(cv::Point3f jointPosition) {
        // is it right to use center of mass?
        return centerOfMass - jointPosition;
    }
    
    float frameFeatures::calculate3dSymmetry () {
        float sumX = 0;
        float sumY = 0;
        float sumZ = 0;
        
        cv::Point3f leftDist;
        cv::Point3f rightDist;
        cv::Point3f diff;
        cv::Point3f absDiff;
        
        int sidePairs = 6;
        //for now the difference btwn left and right joints is 1
        
        for (int sideIndex = 0; sideIndex < sidePairs; sideIndex++) {
            int leftJointIndex = SIDED_JOINTS[sideIndex*2];
            int rightJointIndex = leftJointIndex + 1;
            
            leftDist = distFromBody[leftJointIndex];
            rightDist = distFromBody[rightJointIndex];
            
            diff = leftDist - rightDist;
            absDiff = absPoint3f(leftDist) - absPoint3f(rightDist);
            
            sumX += diff.x / absDiff.x;
            sumY += diff.y /absDiff.y;
            sumZ += diff.z /absDiff.z;
        }
        
        return cv::sqrt((sumX * sumX) + (sumY * sumY) + (sumZ * sumZ)) / (sidePairs * sidePairs);
    }
    
    float frameFeatures::calculateSymIndex(float leftDistance, float rightDistance) {
        return leftDistance + rightDistance * (1 - (leftDistance - rightDistance));
    }
    
    float frameFeatures::calculateTriangularSymmetry(int leftJointIndex, int rightJointIndex) {
        cv::Point3f leftPos = position[leftJointIndex];
        cv::Point3f rightPos = position[rightJointIndex];
        
        //central joint is the head
        float leftDistance = cv::norm(distFromHead[leftJointIndex]);
        float rightDistance = cv::norm(distFromHead[rightJointIndex]);
        float leftRightDistance = cv::norm(leftPos - rightPos);
        
        //TODO fix projection should be wrt body planes
        cv::Point3f projectedPoint = pointSymmetricToLine(leftPos, rightPos, position[nite::JOINT_HEAD]);
        float projectedLeftDistance = cv::norm(projectedPoint - leftPos);
        float projectedRightDistance = cv::norm(projectedPoint - rightPos);
        
        float perimeter = leftDistance + rightDistance + leftRightDistance;
        
        float s1 = calculateSymIndex(leftDistance, rightDistance);
        float s2 = calculateSymIndex(projectedLeftDistance, projectedRightDistance);
        
        return (s1 + s2) / perimeter;
    }



