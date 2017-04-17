//
//  train.cpp
//  kinectTest
//
//  Created by Happern on 07/03/2017.
//
//

#include "train.hpp"

int histLength = 30;
int maxTri = 100;
int minTri = -50;
int max3d = 4000;
int maxDist = 1500;
int maxVaj = 100;
int maxKin = 1500;
int maxCi = 1;
int maxDci = 1;
CvSVM mySVM;


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

int predictFromLiveData(std::vector<frameFeatures> frames) {
    mySVM.load("../Resources/test.xml");
    std::vector<float> fVector = getFeatureVector(frames);
    int numFeatures = 18; // for now, not including dirs
    std::vector<std::vector<float>> fVectorWrapper = {fVector};
    Mat dataMat = copyVectorToMat(fVectorWrapper, numFeatures * histLength);

    int prediction = mySVM.predict(dataMat); //might be int instead of float
    return prediction;
}

std::vector<float> getFeatureVector(std::vector<frameFeatures> frames) {
    std::vector<float> ke;
    std::vector<float> ci;
    std::vector<float> dci;
    std::vector<float> s3d;
    std::vector<float> sTriShld;
    std::vector<float> sTriHand;
    std::vector<nite::Quaternion> dir;
    std::vector<nite::Quaternion> dirHands;
    std::vector<nite::Quaternion> dirElb;
    std::vector<float> velHands;
    std::vector<float> velShldr;
    std::vector<float> velElb;
    std::vector<float> accHands;
    std::vector<float> accShldr;
    std::vector<float> accElb;
    std::vector<float> jerkHands;
    std::vector<float> jerkShldr;
    std::vector<float> jerkElb;
    std::vector<float> distBodHand;
    std::vector<float> distBodElb;
    std::vector<float> distHead;
    
    for (frameFeatures frame : frames) {
        ke.push_back(frame.kineticEnergy);
        ci.push_back(frame.contractionIndex);
        dci.push_back(frame.dynamicContractionIndex);
        s3d.push_back(frame.symmetry3d);
        sTriShld.push_back(frame.symmetryTriangular[1]);
        sTriHand.push_back(frame.symmetryTriangular[0]);
        dir.push_back(frame.direction);
        dirHands.push_back(frame.orientations[nite::JOINT_LEFT_HAND] * frame.orientations[nite::JOINT_RIGHT_HAND]);
        dirHands.push_back(frame.orientations[nite::JOINT_LEFT_ELBOW] * frame.orientations[nite::JOINT_RIGHT_ELBOW]);
        velHands.push_back(cv::norm(frame.velocity[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.velocity[nite::JOINT_RIGHT_HAND])/2);
        velShldr.push_back(cv::norm(frame.velocity[nite::JOINT_LEFT_SHOULDER])/2 + cv::norm(frame.velocity[nite::JOINT_RIGHT_SHOULDER])/2);
        velElb.push_back(cv::norm(frame.velocity[nite::JOINT_LEFT_ELBOW])/2 + cv::norm(frame.velocity[nite::JOINT_RIGHT_ELBOW])/2);
        accHands.push_back(cv::norm(frame.acceleration[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.acceleration[nite::JOINT_RIGHT_HAND])/2);
        accShldr.push_back(cv::norm(frame.acceleration[nite::JOINT_LEFT_SHOULDER])/2 + cv::norm(frame.acceleration[nite::JOINT_RIGHT_SHOULDER])/2);
        accElb.push_back(cv::norm(frame.acceleration[nite::JOINT_LEFT_ELBOW])/2 + cv::norm(frame.acceleration[nite::JOINT_RIGHT_ELBOW])/2);
        jerkHands.push_back(cv::norm(frame.jerk[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.jerk[nite::JOINT_RIGHT_HAND])/2);
        jerkShldr.push_back(cv::norm(frame.jerk[nite::JOINT_LEFT_SHOULDER])/2 + cv::norm(frame.jerk[nite::JOINT_RIGHT_SHOULDER])/2);
        jerkElb.push_back(cv::norm(frame.jerk[nite::JOINT_LEFT_ELBOW])/2 + cv::norm(frame.jerk[nite::JOINT_RIGHT_ELBOW])/2);
        distBodHand.push_back(cv::norm(frame.distFromBody[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.distFromBody[nite::JOINT_RIGHT_HAND])/2);
        distBodElb.push_back(cv::norm(frame.distFromBody[nite::JOINT_LEFT_ELBOW])/2 + cv::norm(frame.distFromBody[nite::JOINT_RIGHT_ELBOW])/2);
        distHead.push_back(cv::norm(frame.distFromHead[nite::JOINT_LEFT_HAND])/2 + cv::norm(frame.distFromHead[nite::JOINT_RIGHT_HAND])/2);
        
    }
    
    std::vector<float> fVector;
    fVector = calculateHistogramAndAppend(ke, 0, maxKin, fVector);
    fVector = calculateHistogramAndAppend(ci, 0, maxCi, fVector);
    fVector = calculateHistogramAndAppend(s3d, 0, max3d, fVector);
    fVector = calculateHistogramAndAppend(sTriShld, minTri, maxTri, fVector);
    fVector = calculateHistogramAndAppend(sTriHand, minTri, maxTri, fVector);
    //TODO find a way to process quaternion
    fVector = calculateHistogramAndAppend(velHands, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(velShldr, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(velElb, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(accHands, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(accShldr, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(accElb, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(jerkHands, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(jerkShldr, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(jerkElb, 0, maxVaj, fVector);
    fVector = calculateHistogramAndAppend(distBodHand, 0, maxDist, fVector);
    fVector = calculateHistogramAndAppend(distBodElb, 0, maxDist, fVector);
    fVector = calculateHistogramAndAppend(distHead, 0, maxDist, fVector);
    
    return fVector;
}

//TODO very bad code :( fix
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

Mat copyVectorToMat(std::vector<std::vector<float>> vector, int matCols) {
    int matRows = vector.size();
    
    Mat matrx(matRows, matCols, CV_32FC1);
    
    for(int row = 0; row < matRows; row++) {
            std::vector<float> vRow = vector[row];
            
            for (int col = 0; col < matCols; col++) {
                matrx.at<float>(row,col) = vRow[col];
            }
    }
    
    return matrx;
}

Mat copyVectorToMat(std::vector<float> vector) {
    int matRows = vector.size();
    
    Mat matrx(matRows, 1, CV_32SC1);
    
    for(int row = 0; row < matRows; row++) {
        matrx.at<int>(row,1) = round(vector[row]);
    }
    
    return matrx;
}


std::vector<float> calculateHistogramAndAppend(std::vector<float> rawFeatures, float min, float max, std::vector<float> fVector) {
    std::vector<int> hist(histLength, 0);
    float interval = (max - min) / histLength;
    //std::cout << std::to_string((max - min) / 2) << "\n";
    
    for (float feat: rawFeatures) {
        int index;
        if(feat >= max) index = histLength -1;
        else if (isnan(feat) || feat <= min) index = 0;
        else index = std::floor(feat/interval);
//        std::cout << "feature " << std::to_string(feat) << "\n";
//        std::cout << "interval " << std::to_string(interval) << "\n";
//         std::cout << "feat/int " << std::to_string(feat/interval) << "\n";
//        std::cout << std::to_string(index) << "\n";
        hist[index]++;
    }
    
    fVector.insert(std::end(fVector), std::begin(hist), std::end(hist));
    return fVector;
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
