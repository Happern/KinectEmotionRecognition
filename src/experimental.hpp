//
//  experimental.hpp
//  KinectEmotionRecognition
//
//  Created by Happern on 10/04/2017.
//
//

#ifndef experimental_hpp
#define experimental_hpp

#include <stdio.h>

#include <string>
#include <vector>

#include "NiTE.h"

#include "frameFeatures.hpp"
#include "happernCore.hpp"

void minmax(std::vector<std::vector<std::vector<frameFeatures>>> processedSessions);
void printMinMaxTriangularSymmetry(std::vector<std::vector<frameFeatures>> session);
void printSomeFrameFeatures(frameFeatures f);
void printNumberOfMovements(std::vector<std::vector<frameFeatures>> session);
void printMinMax3dSymmetry(std::vector<std::vector<frameFeatures>> session);
void printMinMaxDistances(std::vector<std::vector<frameFeatures>> session);
void printMinMaxDirection(std::vector<std::vector<frameFeatures>> session);
void printMinMaxKinematics (std::vector<std::vector<frameFeatures>> session);

#endif /* experimental_hpp */
