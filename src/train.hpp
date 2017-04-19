//
//  train.hpp
//  kinectTest
//
//  Created by Happern on 07/03/2017.
//
//

#ifndef train_hpp
#define train_hpp

#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "frameFeatures.hpp"
#include "featureUtils.hpp"
#include "happernCore.hpp"

using namespace cv;

void train();

void trainFromSessionData(std::vector<std::vector<std::vector<frameFeatures>>> sessions, std::vector<float> sessionLabels);
void train(Mat data, Mat labels);
int predictFromLiveData(std::vector<frameFeatures> frames);

#endif /* train_hpp */
