//
//  featureUtils.cpp
//  KinectEmotionRecognition
//
//  Created by Happern on 19/04/2017.
//
//

#include "featureUtils.hpp"


std::vector<std::vector<std::vector<frameFeatures>>> prepData(std::string dataPath) {
    std::vector<std::vector<std::vector<frameFeatures>>> processedSessions;
    
    std::vector<std::vector<frameFeatures>> processedSession;
    std::vector<frameFeatures> processedMovement;
    frameFeatures prev;
    
    std::vector<std::vector<std::vector<recordedFrame>>> sessions = getRecordedFrames(dataPath);
    
    for(std::vector<std::vector<recordedFrame>> session : sessions) {
        for (std::vector<recordedFrame> movement : session) {
            for(recordedFrame frame : movement) {
                
                if(processedMovement.size() > 0) {
                    prev = processedMovement.back();
                }
                
                frameFeatures f(frame.positions, frame.orientations, frame.centerOfMass, prev);
                processedMovement.push_back(f);
            }
            processedSession.push_back(processedMovement);
            processedMovement.clear();
        }
        processedSessions.push_back(processedSession);
        processedSession.clear();
    }
    
    return processedSessions;
}


//TODO very bad code :( fix
std::vector<float> getFeatureVector(std::vector<frameFeatures> frames) {
    std::vector<float> ke;
    std::vector<float> ci;
    std::vector<float> dci;
    std::vector<float> s3d;
    std::vector<float> sTriShld;
    std::vector<float> sTriHand;
    std::vector<nite::Quaternion> dir;
    std::vector<nite::Quaternion> dirHands;
    std::vector<nite::Quaternion> dirElb;
    std::vector<float> velHands;
    std::vector<float> velShldr;
    std::vector<float> velElb;
    std::vector<float> accHands;
    std::vector<float> accShldr;
    std::vector<float> accElb;
    std::vector<float> jerkHands;
    std::vector<float> jerkShldr;
    std::vector<float> jerkElb;
    std::vector<float> distBodHand;
    std::vector<float> distBodElb;
    std::vector<float> distHead;
    
    for (frameFeatures frame : frames) {
        ke.push_back(frame.kineticEnergy);
        ci.push_back(frame.contractionIndex);
        dci.push_back(frame.dynamicContractionIndex);
        s3d.push_back(frame.symmetry3d);
        sTriShld.push_back(frame.symmetryTriangular[1]);
        sTriHand.push_back(frame.symmetryTriangular[0]);
        dir.push_back(frame.direction);
        dirHands.push_back(frame.orientations[nite::JOINT_LEFT_HAND] * frame.orientations[nite::JOINT_RIGHT_HAND]);
        dirHands.push_back(frame.orientations[nite::JOINT_LEFT_ELBOW] * frame.orientations[nite::JOINT_RIGHT_ELBOW]);
        velHands.push_back(cv::norm(frame.velocity[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.velocity[nite::JOINT_RIGHT_HAND])/2);
        velShldr.push_back(cv::norm(frame.velocity[nite::JOINT_LEFT_SHOULDER])/2 + cv::norm(frame.velocity[nite::JOINT_RIGHT_SHOULDER])/2);
        velElb.push_back(cv::norm(frame.velocity[nite::JOINT_LEFT_ELBOW])/2 + cv::norm(frame.velocity[nite::JOINT_RIGHT_ELBOW])/2);
        accHands.push_back(cv::norm(frame.acceleration[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.acceleration[nite::JOINT_RIGHT_HAND])/2);
        accShldr.push_back(cv::norm(frame.acceleration[nite::JOINT_LEFT_SHOULDER])/2 + cv::norm(frame.acceleration[nite::JOINT_RIGHT_SHOULDER])/2);
        accElb.push_back(cv::norm(frame.acceleration[nite::JOINT_LEFT_ELBOW])/2 + cv::norm(frame.acceleration[nite::JOINT_RIGHT_ELBOW])/2);
        jerkHands.push_back(cv::norm(frame.jerk[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.jerk[nite::JOINT_RIGHT_HAND])/2);
        jerkShldr.push_back(cv::norm(frame.jerk[nite::JOINT_LEFT_SHOULDER])/2 + cv::norm(frame.jerk[nite::JOINT_RIGHT_SHOULDER])/2);
        jerkElb.push_back(cv::norm(frame.jerk[nite::JOINT_LEFT_ELBOW])/2 + cv::norm(frame.jerk[nite::JOINT_RIGHT_ELBOW])/2);
        distBodHand.push_back(cv::norm(frame.distFromBody[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.distFromBody[nite::JOINT_RIGHT_HAND])/2);
        distBodElb.push_back(cv::norm(frame.distFromBody[nite::JOINT_LEFT_ELBOW])/2 + cv::norm(frame.distFromBody[nite::JOINT_RIGHT_ELBOW])/2);
        distHead.push_back(cv::norm(frame.distFromHead[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.distFromHead[nite::JOINT_RIGHT_HAND])/2);
        
    }
    
    std::vector<float> fVector;
    fVector = calculateHistogramAndAppend(ke, 0, maxKin, fVector);
    fVector = calculateHistogramAndAppend(ci, 0, maxCi, fVector);
    fVector = calculateHistogramAndAppend(s3d, 0, max3d, fVector);
    fVector = calculateHistogramAndAppend(sTriShld, minTri, maxTri, fVector);
    fVector = calculateHistogramAndAppend(sTriHand, minTri, maxTri, fVector);
    //TODO find a way to process quaternion
    fVector = calculateHistogramAndAppend(velHands, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(velShldr, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(velElb, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(accHands, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(accShldr, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(accElb, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(jerkHands, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(jerkShldr, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(jerkElb, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(distBodHand, 0, maxDist, fVector);
    fVector = calculateHistogramAndAppend(distBodElb, 0, maxDist, fVector);
    fVector = calculateHistogramAndAppend(distHead, 0, maxDist, fVector);
    
    return fVector;
}



std::vector<float> calculateHistogramAndAppend(std::vector<float> rawFeatures, float min, float max, std::vector<float> fVector) {
    std::vector<int> hist(histLength, 0);
    float interval = (max - min) / histLength;
    //std::cout << std::to_string((max - min) / 2) << "\n";
    
    for (float feat: rawFeatures) {
        int index;
        if(feat >= max) index = histLength -1;
        else if (isnan(feat) || feat <= min) index = 0;
        else index = std::floor(feat/interval);
        //        std::cout << "feature " << std::to_string(feat) << "\n";
        //        std::cout << "interval " << std::to_string(interval) << "\n";
        //         std::cout << "feat/int " << std::to_string(feat/interval) << "\n";
        //        std::cout << std::to_string(index) << "\n";
        hist[index]++;
    }
    
    fVector.insert(std::end(fVector), std::begin(hist), std::end(hist));
    return fVector;
}
