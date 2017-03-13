//
//  read.hpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#ifndef read_hpp
#define read_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "recordedFrame.cpp"

std::vector<std::vector<recordedFrame>> getSessionData();
std::vector<std::vector<std::vector<recordedFrame>>> getRecordedFrames(std::string path);
std::vector<std::vector<recordedFrame>> processSessionData(std::vector<recordedFrame> frames, int breakMargin);

bool compareByUserId(const recordedFrame &f1, const recordedFrame &f2);


#endif /* read_hpp */
