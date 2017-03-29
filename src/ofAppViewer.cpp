//
//  ofAppViewer.cpp
//  KinectEmotionRecognition
//
//  Created by Happern on 29/03/2017.
//
//

#include "ofAppViewer.hpp"


void ofAppViewer::setup() {
    openni::OpenNI::initialize();
    
    if(readFromFile) {
        dev.open(filename);
    } else {
        //expect only one kinect to be connected
        dev.open(openni::ANY_DEVICE);
    }
    
    pixels.allocate(0, 0, 1);
    texture.clear();
    
    if(dev.isValid()){
        
        if(readMode == 0) {
            ir.create(dev, openni::SENSOR_IR);
            depth.create(dev, openni::SENSOR_DEPTH);
            depth.start();
            
            dev.setImageRegistrationMode (openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
            ir.start();
            
            //expected VideoMode is grayscale16 = 203 for ir
            openni::VideoMode mode = ir.getVideoMode();
            int pix = (int)mode.getPixelFormat();

            validStream = (ir.isValid() && pix == 203);
            
        } else if (readMode == 1) {
            color.create(dev, openni::SENSOR_COLOR);
            color.start();
            
            //expected VideoMode is RGB800 for color
            openni::VideoMode mode = color.getVideoMode();
            int pix = (int)mode.getPixelFormat();
            
            validStream = (color.isValid() && pix == 200);
        } else {
            validStream = false;
        }
        
        if (!validStream ) {
            std::cout << "error reading specified stream\n" ;
        }
    } else {
        std::cout << "device is invalid" << "\n";
        validStream = false;
    }
}

void ofAppViewer::update() {
    int resX;
    int resY;
    int frameWidth;
    int frameHeight;
    int numChannels;
    
    if (validStream){
        if (readMode == 0) {
            openni::Status frameStatusIr = ir.readFrame(&irFrame);
            openni::Status frameStatusDepth = depth.readFrame(&depthFrame);
            
            if ((int) frameStatusIr == 0 ) {
                frameRead = true;
                irFrameData = reinterpret_cast<const OniGrayscale16Pixel*>(irFrame.getData());
                
                resX = irFrame.getVideoMode().getResolutionX();
                resY = irFrame.getVideoMode().getResolutionY();
                frameWidth = irFrame.getWidth();
                frameHeight = irFrame.getHeight();
                numChannels = 1;
            } else {
                std::cout << "ir frame error \n";
                frameRead = false;
            }
        } else if (readMode == 1) {
            openni::Status frameStatusColor  = color.readFrame(&colorFrame);
        
            if ((int)frameStatusColor == 0){
                frameRead = true;
                
                colorFrameData = reinterpret_cast<const OniRGB888Pixel*>(colorFrame.getData());
                
                resX = colorFrame.getVideoMode().getResolutionX();
                resY = colorFrame.getVideoMode().getResolutionY();
                frameWidth = colorFrame.getWidth();
                frameHeight = colorFrame.getHeight();
                numChannels = 3;
            }else {
                std::cout << "color frame error \n";
                frameRead = false;
            }
        }
    }
    
    if (frameRead) {
        ofShortColor grayColor;
        ofColor color;
        
        pixels.allocate(resX, resY, numChannels);
        
        for (int heightIndex = 0; heightIndex < frameHeight; heightIndex++){
            for (int widthIndex = 0; widthIndex < frameWidth; widthIndex ++) {
                if (readMode == 0) {
                    OniGrayscale16Pixel px = irFrameData[heightIndex * frameWidth + widthIndex];
                    grayColor = ofShortColor(px);
                    pixels.setColor(widthIndex, heightIndex, grayColor);
                } else if (readMode == 1){
                    OniRGB888Pixel px = colorFrameData[heightIndex * frameWidth + widthIndex];
                    color = ofColor(px.r, px.g, px.b);
                    pixels.setColor(widthIndex, heightIndex, color);
                }
            }
        }
        
        
        if (!texture.isAllocated() || texture.getWidth() != resX || texture.getHeight() != resY) {
            texture.allocate(pixels);
        }
        
        texture.loadData(pixels);
    }
    
}


void ofAppViewer::draw() {
    ofBackground(0);
    
    if (texture.isAllocated()) {
        ofSetColor(ofColor::white);
        texture.draw(0, 0);
    }
    
}
