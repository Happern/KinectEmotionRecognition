//
//  train.cpp
//  kinectTest
//
//  Created by Happern on 07/03/2017.
//
//

#include "train.hpp"

std::vector<std::vector<std::vector<frameFeatures>>> prepData(std::string dataPath) {
    std::vector<std::vector<std::vector<frameFeatures>>> processedSessions;
    
    std::vector<std::vector<frameFeatures>> processedSession;
    std::vector<frameFeatures> processedMovement;
    frameFeatures prev;
    
    std::vector<std::vector<std::vector<recordedFrame>>> sessions = getRecordedFrames(dataPath);
    
    for(std::vector<std::vector<recordedFrame>> session : sessions) {
        for (std::vector<recordedFrame> movement : session) {
            for(recordedFrame frame : movement) {
                
                if(processedMovement.size() > 0) {
                    prev = processedMovement.back();
                }
                
                frameFeatures f(frame.positions, frame.orientations, frame.centerOfMass, prev);
                processedMovement.push_back(f);
            }
            processedSession.push_back(processedMovement);
            processedMovement.clear();
        }
        processedSessions.push_back(processedSession);
        processedSession.clear();
    }
    
    return processedSessions;
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
