//
//  train.hpp
//  kinectTest
//
//  Created by Happern on 07/03/2017.
//
//

#ifndef train_hpp
#define train_hpp

#include <list>

#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "read.hpp"
#include "frameFeatures.hpp"

using namespace cv;



void train();
std::vector<std::vector<std::vector<frameFeatures>>> prepData(std::string dataPath);
std::vector<float> calculateHistogramAndAppend(std::vector<float> rawFeatures, float min, float max, std::vector<float> fVector);
void trainFromSessionData(std::vector<std::vector<std::vector<frameFeatures>>> sessions, std::vector<float> sessionLabels);
void train(Mat data, Mat labels);
int predictFromLiveData(std::vector<frameFeatures> frames);

std::vector<float> getFeatureVector(std::vector<frameFeatures> frames);
Mat copyVectorToMat(std::vector<std::vector<float>> vector, int matCols);
Mat copyVectorToMat(std::vector<float> vector);



#endif /* train_hpp */
