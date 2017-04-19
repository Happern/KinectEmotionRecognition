//
//  featureUtils.hpp
//  KinectEmotionRecognition
//
//  Created by Happern on 19/04/2017.
//
//

#ifndef featureUtils_hpp
#define featureUtils_hpp

#include <stdio.h>
#include <vector>

#include "frameFeatures.hpp"
#include "recordedFrame.hpp"
#include "read.hpp"

#include "featureConstants.hpp"

std::vector<std::vector<std::vector<frameFeatures>>> prepData(std::string dataPath);
std::vector<float> calculateHistogramAndAppend(std::vector<float> rawFeatures, float min, float max, std::vector<float> fVector);
std::vector<float> getFeatureVector(std::vector<frameFeatures> frames);

#endif /* featureUtils_hpp */
