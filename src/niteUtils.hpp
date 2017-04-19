//
//  niteUtils.hpp
//  KinectEmotionRecognition
//
//  Created by Happern on 19/04/2017.
//
//

#ifndef niteUtils_hpp
#define niteUtils_hpp

#include <stdio.h>
#include "NiTE.h"
#include "opencv2/core/core.hpp"

//nite
cv::Point3f niteToCv(nite::Point3f p);
cv::Point3f niteToCv(NitePoint3f p);
nite::Point3f cvToNite(cv::Point3f p);
const nite::Quaternion operator *(const nite::Quaternion q1, const nite::Quaternion q2);
bool checkZeroQuaternion(nite::Quaternion q);


#endif /* niteUtils_hpp */
