//
//  ofAppViewer.hpp
//  KinectEmotionRecognition
//
//  Created by Happern on 29/03/2017.
//
//

#ifndef ofAppViewer_hpp
#define ofAppViewer_hpp

#include <stdio.h>
#include "ofMain.h"
#include "OpenNI.h"
#include "OniCTypes.h"

#include <string.h>

class ofAppViewer : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    openni::Device dev;
    openni::VideoStream color;
    openni::VideoStream ir;
    openni::VideoStream depth;
    
    openni::VideoFrameRef colorFrame;
    openni::VideoFrameRef irFrame;
    openni::VideoFrameRef depthFrame;
    
    bool validStream;
    bool frameRead;
    
    
    const OniGrayscale16Pixel * irFrameData;
    const OniRGB888Pixel * colorFrameData;

    ofPixels pixels;
    ofTexture texture;
    
    // TODO get the below info from main function
    int readMode = 0; // 0 for ir, 1 for color
    int readFromFile = false;
    std::string filenameStr = "/Users/happern/Library/DeveloperUserInstalled/of_v0.9.8_osx_release/apps/myApps/KinectEmotionRecognition/bin/KinectEmotionRecognitionDebug.app/Contents/Resources/onifile0.oni";
    const char * filename = filenameStr.c_str();
};



#endif /* ofAppViewer_hpp */
