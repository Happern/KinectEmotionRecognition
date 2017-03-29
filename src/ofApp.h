#pragma once

#include <string>

#include <ctime>

#include "ofMain.h"

#include "NiTE.h"
#include "OpenNI.h"

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
    
    void mousePressed(int x, int y, int button);
    void checkSensors(openni::Device * dev);
    void toggleRecordButton();
    void calculateHistogram(float* histogram, int histogramSize, const openni::VideoFrameRef& frame);
    ofVec2f getJointInDepthCoordinates(nite::UserData user, nite::JointType jointType);
    void drawUser(user_t user);
    
    ofPixels depthPixels;
    ofTexture depthTexture;
    
    nite::UserTracker userTracker;
    
    float depthHist[MAX_DEPTH];
    user_t users[MAX_USERS];
    
    // variables used in the record mode
    bool isRecording = false;
    bool isShutdown = false;
    int recordingCounter = 0;
    const ofRectangle recordButton = ofRectangle(50, 50, 50, 50);
    const ofRectangle stopButton = ofRectangle(700, 500, 20, 20);
    openni::Device dev;
    
    
    
    int runMode = 0; //0 for detect, 1 for record
    int frameCount;
    std::string logFileName = "deneme.txt"; //get as an argument
};
