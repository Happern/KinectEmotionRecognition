//
//  train.cpp
//  kinectTest
//
//  Created by Happern on 07/03/2017.
//
//

#include "train.hpp"

CvSVM mySVM;

int predictFromLiveData(std::vector<frameFeatures> frames) {
    // TODO filename must be moved
    mySVM.load("../Resources/test.xml");
    std::vector<float> fVector = getFeatureVector(frames);
    int numFeatures = 18; // for now, not including dirs
    std::vector<std::vector<float>> fVectorWrapper = {fVector};
    Mat dataMat = copyVectorToMat(fVectorWrapper, numFeatures * histLength);

    int prediction = mySVM.predict(dataMat); //might be int instead of float
    return prediction;
}


void trainFromSessionData(std::vector<std::vector<std::vector<frameFeatures>>> sessions, std::vector<float> sessionLabels) {
    //have a session labels array
    // have a movements array, each entry will be a feature vector
    std::vector<std::vector<float>> movements;
    std::vector<float> movementLabels;
    float label;
    std::vector<std::vector<frameFeatures>> session;
    int numSessions = sessions.size();
    
    if(sessionLabels.size() != numSessions) {
        std::cout << "training data and labels don't match\n";
    } else {
        for (int sessionInd = 0; sessionInd < numSessions; sessionInd++) {
            session = sessions[sessionInd];
            label = sessionLabels[sessionInd];
            std::cout << "label: " << std::to_string(label) << "\n";
            
            for(std::vector<frameFeatures> movement : session) {
                movementLabels.push_back(label);
                
                std::vector<float> fVector = getFeatureVector(movement);
                //std::list<float> featureList(fVector.begin(), fVector.end());
                movements.push_back(fVector);
            }
        }
    }
    int numFeatures = 18; // for now, not including dirs
    Mat trainingDataMat = copyVectorToMat(movements, numFeatures * histLength);
//    std::cout << "expect nr of elements to be " << std::to_string(movements.size() * numFeatures * histLength) << "\n";
//    std::cout << "total nr of element in training data " << std::to_string(trainingDataMat.total()) << "\n";
    
    Mat labelsMat = copyVectorToMat(movementLabels);
    
    
//    std::cout << "expect nr of elements to be " << std::to_string(movements.size()) << "\n";
//    std::cout << "total nr of element in label " << std::to_string(labelsMat.total()) << "\n";
//    for(int m = 0; m < movements.size(); m++) {
//        std::cout << std::to_string(labelsMat.at<float>(m,1)) << "\n";
//        std::cout << std::to_string(movementLabels[m]) << "\n";
//    }
    
    train(trainingDataMat, labelsMat);
}

void train(Mat data, Mat labels) {
    // Data for visual representation
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);
    
    // Set up SVM's parameters
    CvSVMParams params;
    params.svm_type    = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);
    
    // Train the SVM
    mySVM.train(data, labels, Mat(), Mat(), params);
    
    // TODO filename must be moved
    mySVM.save("test.xml");
}

//Copied from SVM tutorial
void train() {
    // Data for visual representation
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);
    
    // Set up training data
    float labels[4] = {1.0, -1.0, 2.0, -1.0};
    Mat labelsMat(4, 1, CV_32FC1, labels);
    
    float trainingData[4][3] = { {501, 10, 20}, {255, 10, 10}, {501, 255, 45}, {10, 501, 67} };
    Mat trainingDataMat(4, 3, CV_32FC1, trainingData);
    
    // Set up SVM's parameters
    CvSVMParams params;
    params.svm_type    = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);
    
    // Train the SVM
    CvSVM SVM;
    SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);
    
    Vec3b green(0,255,0), blue (255,0,0);
    // Show the decision regions given by the SVM
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
        {
            Mat sampleMat = (Mat_<float>(1,3) << j,i);
            float response = SVM.predict(sampleMat);
            
            if (response == 1)
                image.at<Vec3b>(i,j)  = green;
            else if (response == -1)
                image.at<Vec3b>(i,j)  = blue;
        }
    
    // Show the training data
    int thickness = -1;
    int lineType = 8;
    circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness, lineType);
    circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness, lineType);
    circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
    circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness, lineType);
    
    // Show support vectors
    thickness = 2;
    lineType  = 8;
    int c     = SVM.get_support_vector_count();
    
    for (int i = 0; i < c; ++i)
    {
        const float* v = SVM.get_support_vector(i);
        circle( image,  Point( (int) v[0], (int) v[1]),   6,  Scalar(128, 128, 128), thickness, lineType);
    }
    
    //imwrite("result.png", image);        // save the image
    
    imshow("SVM Simple Example", image); // show it to the user
    waitKey(0);
}
