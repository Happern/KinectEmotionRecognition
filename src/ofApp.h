#pragma once

#include <string>

#include "ofMain.h"
#include "NiTE.h"

#include "frameFeatures.hpp"
#include "record.hpp"
#include "read.hpp"
#include "train.hpp"


#define MAX_USERS 10
#define MAX_DEPTH 10000
#define NUM_FRAMES 100

struct user_t {
    bool visible;
    ofVec2f head;
    ofVec2f neck;
    ofVec2f leftShoulder;
    ofVec2f rightShoulder;
    ofVec2f leftElbow;
    ofVec2f rightElbow;
    ofVec2f leftHand;
    ofVec2f rightHand;
    ofVec2f torso;
    ofVec2f leftHip;
    ofVec2f rightHip;
    ofVec2f leftKnee;
    ofVec2f rightKnee;
    ofVec2f leftFoot;
    ofVec2f rightFoot;
    ofVec3f centerOfMassWorldCoord;
    
    std::vector<frameFeatures> features;
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void calculateHistogram(float* histogram, int histogramSize, const openni::VideoFrameRef& frame);
    ofVec2f getJointInDepthCoordinates(nite::UserData user, nite::JointType jointType);
    void drawUser(user_t user);
    
    ofPixels depthPixels;
    ofTexture depthTexture;
    
    openni::Device device;
    nite::UserTracker userTracker;
    
    float depthHist[MAX_DEPTH];
    user_t users[MAX_USERS];
    
    int frameCount;
    bool isRecording = true; //Set this from the arguments -- move to main
    std::string logFileName = "output.txt"; //possibly move this somewhere else, also get from the arguments
};
