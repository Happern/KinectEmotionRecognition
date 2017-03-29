//
//  train.hpp
//  kinectTest
//
//  Created by Happern on 07/03/2017.
//
//

#ifndef train_hpp
#define train_hpp

#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "read.hpp"
#include "frameFeatures.hpp"

using namespace cv;

void train();
std::vector<std::vector<std::vector<frameFeatures>>> prepData(std::string dataPath);

#endif /* train_hpp */
