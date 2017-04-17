//
//  experimental.cpp
//  KinectEmotionRecognition
//
//  Created by Happern on 10/04/2017.
//
//

#include "experimental.hpp"


void minmax(std::vector<std::vector<std::vector<frameFeatures>>> processedSessions) {
    //std::cout << std::to_string(processedSessions.size()) << "\n";
    
    //std::cout << "First frame info:\n";
   // printSomeFrameFeatures(processedSessions[0][0][0]);
    
    std::cout << "\n\n";
    printMinMaxTriangularSymmetry(processedSessions[0]);
    std::cout << "\n";
    printMinMaxTriangularSymmetry(processedSessions[1]);
    std::cout << "\n\n";
    printMinMax3dSymmetry(processedSessions[0]);
    std::cout << "\n";
    printMinMax3dSymmetry(processedSessions[3]);
    std::cout << "\n\n";
    printMinMaxDistances(processedSessions[4]);
    std::cout << "\n";
    printMinMaxDistances(processedSessions[5]);
    std::cout << "\n";
    printMinMaxDistances(processedSessions[6]);
    std::cout << "\n\n";
    printMinMaxDirection(processedSessions[8]);
    std::cout << "\n";
    printMinMaxDirection(processedSessions[9]);
    std::cout << "\n\n";
    printMinMaxKinematics(processedSessions[10]);
    
}

void printSomeFrameFeatures(frameFeatures f) {
    std::cout << "position of first joint "; printPoint(f.position[0]);
    std::cout << "velocity of first joint "; printPoint(f.velocity[0]);
    std::cout << "jerk of first joint "; printPoint(f.jerk[0]);
    std::cout << "acceleration of first joint "; printPoint(f.acceleration[0]);
    std::cout << "contraction index " << std::to_string(f.contractionIndex) << "\n";
}

// TODO find a better comparison method
void printMinMaxDirection(std::vector<std::vector<frameFeatures>> session) {
    printNumberOfMovements(session);
    float minAngle = 0;
    float maxAngle = 0;
    
    for (std::vector<frameFeatures> movement : session) {
        std::cout << "There are: " << std::to_string(movement.size()) << " frames in this movement\n";
        for (frameFeatures frame : movement) {
            float ang = frame.direction.w;
            
            if (ang < minAngle) minAngle = ang;
            else if (ang > maxAngle) maxAngle = ang;
        }
    }
    
    std::cout << "Min Max Direction Angular value: " << std::to_string(minAngle) << ", " << std::to_string(maxAngle) << "\n";
}

void printMinMaxKinematics (std::vector<std::vector<frameFeatures>> session) {
    printNumberOfMovements(session);
    float minVel = 0;
    float maxVel = 0;
    
    float minAcc = 0;
    float maxAcc = 0;
    
    float minJerk = 0;
    float maxJerk = 0;
    
    for (std::vector<frameFeatures> movement : session) {
        int numFrames = movement.size();
        std::cout << "There are: " << numFrames << " frames in this movement\n";
        
        for (int frameIndex = 3; frameIndex <numFrames; frameIndex++) {
            frameFeatures frame = movement[frameIndex];
            float vel = cv::norm(frame.velocity[nite::JOINT_LEFT_HAND]);
            float acc = cv::norm(frame.acceleration[nite::JOINT_LEFT_HAND]);
            float jerk = cv::norm(frame.jerk[nite::JOINT_LEFT_HAND]);
            
            if (vel < minVel) minVel = vel;
            else if (vel > minVel) maxVel = vel;
            
            if (acc < minAcc) minAcc = acc;
            else if (acc > minAcc) maxAcc = acc;
            
            if (jerk < minJerk) minJerk = jerk;
            else if (jerk > minJerk) maxJerk = jerk;
        }
    }
    
    std::cout << "Min Max Left Hand Velocity: " << std::to_string(minVel) << ", " << std::to_string(maxVel) << "\n";
    std::cout << "Min Max Left Hand Acceleration: " << std::to_string(minAcc) << ", " << std::to_string(maxAcc) << "\n";
    std::cout << "Min Max Left Hand Jerk: " << std::to_string(minAcc) << ", " << std::to_string(maxAcc) << "\n";
    
}



void printMinMaxDistances(std::vector<std::vector<frameFeatures>> session) {
    printNumberOfMovements(session);
    float minHandHead = 0;
    float maxHandHead = 0;
    
    float minHandBody = 0;
    float maxHandBody = 0;
    
    float minElbowBody = 0;
    float maxElbowBody = 0;
    
    for (std::vector<frameFeatures> movement : session) {
        std::cout << "There are: " << std::to_string(movement.size()) << " frames in this movement\n";
        for (frameFeatures frame : movement) {
            cv::Point3f * head = frame.distFromHead;
            cv::Point3f * body = frame.distFromBody;
            
            float aveHandHead = cv::norm(head[nite::JOINT_LEFT_HAND]) + cv::norm(head[nite::JOINT_RIGHT_HAND]);
            float aveHandBody = cv::norm(body[nite::JOINT_LEFT_HAND]) + cv::norm(body[nite::JOINT_RIGHT_HAND]);
            float aveElbowBody = cv::norm(body[nite::JOINT_LEFT_ELBOW]) + cv::norm(body[nite::JOINT_RIGHT_ELBOW]);
            
            if (aveHandHead < minHandHead) minHandHead = aveHandHead;
            else if (aveHandHead > maxHandHead) maxHandHead = aveHandHead;
            
            if (aveHandBody < minHandBody) minHandBody = aveHandBody;
            else if (aveHandBody > maxHandBody) maxHandBody = aveHandBody;
            
            if (aveElbowBody < minElbowBody) minElbowBody = aveElbowBody;
            else if (aveElbowBody > maxElbowBody) maxElbowBody = aveElbowBody;
        }
    }
    
    std::cout << "Min Max Head Hand Dist: " << std::to_string(minHandHead) << ", " << std::to_string(maxHandHead) << "\n";
    std::cout << "Min Max Head Body Dist: " << std::to_string(minHandBody) << ", " << std::to_string(maxHandBody) << "\n";
    std::cout << "Min Max Elbow Body Dist: " << std::to_string(minElbowBody) << ", " << std::to_string(maxElbowBody) << "\n";
    
}

void printMinMaxTriangularSymmetry(std::vector<std::vector<frameFeatures>> session) {
    printNumberOfMovements(session);
    float minHandSymmetry = 0;
    float maxHandSymmetry = 0;
    
    float minShoulderSymmetry = 0;
    float maxShoulderSymmetry = 0;
    
    for (std::vector<frameFeatures> movement : session) {
        std::cout << "There are: " << std::to_string(movement.size()) << " frames in this movement\n";
        for (frameFeatures frame : movement) {
            float * tri = frame.symmetryTriangular;
            float hSym = tri[0];
            float sSym = tri[1];
            
            if (hSym < minHandSymmetry) minHandSymmetry = hSym;
            else if (hSym > maxHandSymmetry) maxHandSymmetry = hSym;
            
            if (sSym < minShoulderSymmetry) minShoulderSymmetry = sSym;
            else if (sSym > maxShoulderSymmetry) maxShoulderSymmetry = sSym;
        }
    }
    
    std::cout << "Min Max Triangular Hand Symmetries: " << std::to_string(minHandSymmetry) << ", " << std::to_string(maxHandSymmetry) << "\n";
    std::cout << "Min Max Triangular Shoulder Symmetries: " << std::to_string(minShoulderSymmetry) << ", " << std::to_string(maxShoulderSymmetry) << "\n";
    
}

void printMinMax3dSymmetry(std::vector<std::vector<frameFeatures>> session) {
    printNumberOfMovements(session);
    float minSym = 0;
    float maxSym = 0;
    
    for (std::vector<frameFeatures> movement : session) {
        std::cout << "There are: " << std::to_string(movement.size()) << " frames in this movement\n";
        for (frameFeatures frame : movement) {
            float sym = frame.symmetry3d;
            
            if (sym < minSym) minSym = sym;
            else if (sym > maxSym) maxSym = sym;
        }
    }
    
    std::cout << "Min Max 3d Sym values: " << std::to_string(minSym) << ", " << std::to_string(maxSym) << "\n";
    
}

void printNumberOfMovements(std::vector<std::vector<frameFeatures>> session) {
    int numMovements = session.size();
    std::cout << "There are " << std::to_string(numMovements) << " movements in this session\n";
    
    //   return numMovements;
}

