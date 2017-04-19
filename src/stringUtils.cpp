//
//  stringUtils.cpp
//  KinectEmotionRecognition
//
//  Created by Happern on 19/04/2017.
//
//

#include "stringUtils.hpp"

// for reading
std::vector<std::string> split(std::string str, std::string delimiter) {
    std::vector<std::string> array;
    std::size_t pos = 0, found;
    while((found = str.find_first_of(delimiter, pos)) != std::string::npos) {
        array.push_back(str.substr(pos, found - pos));
        pos = found+1;
    }
    array.push_back(str.substr(pos));
    
    return array;
}


nite::Quaternion parseQuaternion(std::string quaternion) {
    std::vector<std::string> comps = split(quaternion, pointDelimiter);
    
    return nite::Quaternion(std::stof(comps[0]), std::stof(comps[1]), std::stof(comps[2]), std::stof(comps[3]));
}


cv::Point3f parsePoint3f(std::string point) {
    std::vector<std::string> coords = split(point, pointDelimiter);
    
    return cv::Point3f(std::stof(coords[0]), std::stof(coords[1]), std::stof(coords[2]));
}

std::string point3fToString(NitePoint3f p) {
    return point3fToString(niteToCv(p));
}

std::string quaternionToString(nite::Quaternion q) {
    //TODO implement
    return std::to_string(q.w) + " " + std::to_string(q.x) + " " + std::to_string(q.y) + " " + std::to_string(q.z);;
}

