//
//  record.cpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#include "record.hpp"

//why can this not go in the header file?
std::ofstream out;

void startRecording(std::string path) {
    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    out.open(path, std::ios::app);
    if(!out.is_open()) {
        std::cout<< "File could not be opened or created for writing\n";
        return;
    } else {
        std::cout << "File opened\n";
    }
    
    //append timestamp
    std::time_t lala = std::time(nullptr);
    std::string initSession = "Session Start ";
    initSession += std::asctime(std::localtime(&lala));
    writeToFile(initSession);
}

void finishRecording() {
    writeToFile("End");
    out.close();
}

void writeToFile(std::string log) {
    out << log << "\n";
}

void recordData(int frameCount, nite::UserData user) {
    std::string dataString = std::to_string(frameCount) + betweenSeparator;
    
    dataString += getUserData(user) + betweenSeparator;
    dataString += getJointData(user.getSkeleton());
    
    writeToFile(dataString);
}

std::string getUserData(nite::UserData user) {
    std::string userData = std::to_string(user.getId()) + betweenSeparator;
    
    nite::BoundingBox bb = user.getBoundingBox();
    userData += point3fToString(bb.min) + withinSeparator + point3fToString(bb.max) + betweenSeparator;
    
    userData += point3fToString(user.getCenterOfMass());
    
    //check if isNew, isVisible, isLost are relevant since we are only getting here if the skeleton is tracked
    
    return userData;
}

std::string getJointData(nite::Skeleton skeleton){
    std::string jointData = "";
    
    for(nite::JointType j: JOINTS) {
        nite::SkeletonJoint joint = skeleton.getJoint(j);
        
        //test how to encode joint type
        
        jointData += point3fToString(joint.getPosition()) + withinSeparator + std::to_string(joint.getPositionConfidence()) + withinSeparator;
        
        jointData += quaternionToString(joint.getOrientation()) + withinSeparator + std::to_string(joint.getOrientationConfidence()) + betweenSeparator;
    }
    
    return jointData;
}

