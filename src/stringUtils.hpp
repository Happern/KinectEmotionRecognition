//
//  stringUtils.hpp
//  KinectEmotionRecognition
//
//  Created by Happern on 19/04/2017.
//
//

#ifndef stringUtils_hpp
#define stringUtils_hpp

#include <stdio.h>

#include <string>

// could be better if utils were independent from each other
#include "opencv2/core/core.hpp"
#include "cvUtils.hpp"
#include "NiTE.h"
#include "niteUtils.hpp"
#include "fileConstants.hpp"

std::vector<std::string> split(std::string str, std::string delimiter);
cv::Point3f parsePoint3f(std::string point);
nite::Quaternion parseQuaternion(std::string quaternion);

std::string point3fToString(NitePoint3f p);
std::string quaternionToString(nite::Quaternion q);

#endif /* stringUtils_hpp */
