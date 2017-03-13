//
//  read.cpp
//  kinectTest
//
//  Created by Happern on 08/03/2017.
//
//

#include "read.hpp"

// will read and produce a positions array
// an orientation obj
// a center of mass obj
// i want one user - all frames

std::ifstream in;



std::vector<std::vector<std::vector<recordedFrame>>> getRecordedFrames(std::string path) {
    
    std::vector<std::vector<std::vector<recordedFrame>>> sessions;

    in.open(path, std::ios::in);
    
    if (!in.is_open()) {
        std::cout << "Can't read " << in.good() << "\n";
        return;
    }
    
    while(in.good()) {
        std::vector<std::vector<recordedFrame>> currSession = getSessionData();
        
        //TODO investigate 0 case mentioned below
        if(currSession.size() > 0){
            sessions.push_back(currSession);
        }
    }
   
    in.close();
    
    return sessions;
}

//TODO make a sessionData object - include time and possible other relevant info
std::vector<std::vector<recordedFrame>> getSessionData() {
    
    std::vector<recordedFrame> recordedFrames;
    std::string line;
    
    //this gets the initial session line with time frame - how will we use it?
    std::getline(in, line);
    std::getline(in, line);
    
    std::cout << line << "\n";
    
    while(in.good()) {
        
        std::getline(in, line);
        
        if(line == "End") break;
        
        
        recordedFrames.push_back(recordedFrame(line));
    }
    
    //TODO investigate why the recordedFrames size becomes 0
    //TODO investigate the right value for breakMargin
    if (recordedFrames.size() > 0) {
        return processSessionData(recordedFrames, 900);
    } else {
        return std::vector<std::vector<recordedFrame>>();
    }
   
}

std::vector<std::vector<recordedFrame>> processSessionData(std::vector<recordedFrame> frames, int breakMargin) {
    std::sort(frames.begin(), frames.end(), compareByUserId);
    std::vector<std::vector<recordedFrame>> users;
    
    int currUserId = frames[0].userId;
    std::vector<recordedFrame> currUser;
    recordedFrame currEntry;
    
    for(int entryIndex = 0; entryIndex < frames.size(); entryIndex++){
         currEntry = frames[entryIndex];
        
        
        //std::cout << currUser.back().frameNumber;
        //|| currEntry.frameNumber - currUser.back().frameNumber >= breakMargin
        
        if(currUserId != currEntry.userId || (currUser.size() > 0 &&  currEntry.frameNumber - currUser.back().frameNumber >= breakMargin)) {
            //std::vector<recordedFrame> userCopy;
            //userCopy.assign(currUser.begin(), currUser.end());
            users.push_back(currUser);
            if(currUserId != currEntry.userId) {
                currUserId = currEntry.userId;
            }
            currUser.clear();
        }
        
        currUser.push_back(currEntry);
    }
    
    users.push_back(currUser);
    
    return users;
}

bool compareByUserId(const recordedFrame &f1, const recordedFrame &f2) {
    return f1.userId > f2.userId;
}

