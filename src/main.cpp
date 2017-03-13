#include "ofMain.h"
#include "Nite.h"
#include "ofApp.h"
#include "opencv2/core/core.hpp"
#include "train.hpp"


//========================================================================



int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());

    
    /* unit test for minMaxPoints
    
    cv::Point3f p(1,1,1);
    cv::Point3f q(2,2,2);
    cv::Point3f r(3,3,3);
    
    cv::Point3f points[3] = {p, q, r};
    
    std::vector<float> lalal = minMaxPoints(points, 3);
    
    std::cout << lalal[0] << " " << lalal[1] << " " << lalal[2] << " " << lalal[3] << " " << lalal[4] <<  " " << lalal[5] << "\n";
    
    */

   /* point symmetric to line unit test
    cv::Point3f p1(-1,0,0);
    cv::Point3f p2(1,0,0);
    cv::Point3f p3(0,1,0);
    
    cv::Point3f symm = pointSymmetricToLine(p1, p2, p3);
    
    std::cout << symm.x << " " << symm.y << " " << symm.z << "\n";*/
    
    //train();
    
    
   /*ofSetupOpenGL(800, 600, OF_WINDOW);
   ofRunApp(new ofApp());*/

    //./bin/kinectTestDebug/Contents/Resources
    //getRecordedFrames("/Users/happern/Library/DeveloperUserInstalled/of_v0.9.8_osx_release/apps/myApps/kinectTest/bin/kinectTestDebug.app/Contents/Resources/bin/kinectTestDebug/Contents/Resources/output.txt");
    
    prepData();
    
   }
