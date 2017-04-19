//
//  niteUtils.cpp
//  KinectEmotionRecognition
//
//  Created by Happern on 19/04/2017.
//
//

#include "niteUtils.hpp"


cv::Point3f niteToCv(nite::Point3f p) {
    return cv::Point3f(p.x, p.y, p.z);
}

cv::Point3f niteToCv(NitePoint3f p) {
    return cv::Point3f(p.x, p.y, p.z);
}

nite::Point3f cvToNite(cv::Point3f p) {
    return nite::Point3f(p.x, p.y, p.z);
}


const nite::Quaternion operator *(const nite::Quaternion q1, const nite::Quaternion q2)
{	return nite::Quaternion(q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
                            q1.y * q2.z - q1.z * q2.y + q1.w * q2.x + q1.x * q2.w,
                            q1.z * q2.x - q1.x * q2.z + q1.w * q2.y + q1.y * q2.w,
                            q1.x * q2.y - q1.y * q2.x + q1.w * q2.z + q1.z * q2.w);
}


bool checkZeroQuaternion(nite::Quaternion q) {
    return q.w == 0 && q.x == 0 && q.y == 0 && q.z == 0;
}
