#include "ofMain.h"
#include "Nite.h"

#include "ofApp.h"
#include "ofAppViewer.hpp"

#include "opencv2/core/core.hpp"
#include "train.hpp"
#include "experimental.hpp"


//========================================================================



int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());

    ofSetupOpenGL(800, 600, OF_WINDOW);
    
    std::string mode = "";
    
    //TODO below will be taken from the commandline or will be chosen from a gui
    if (mode == "train") {
        // no need for GUI -- or ofApp
        // get data path from the user
        std::string path = "../Resources/basic_movement_measurements/deneme.txt";
        std::vector<float> labels{1.0,2.0,3.0, 4.0, 1.0, 2.0, 3.0, 4.0};
        std::vector<std::vector<std::vector<frameFeatures>>> data = prepData(path);
        //minmax(data);
        trainFromSessionData(data, labels);
        //train();
    } else if (mode == "view") {
        // if filename is provided read from file, pass readFromFile as true / 1
        // o.w. read from device
        // check streams, if ir set readMode as 0 if color set readMode as 1
        ofRunApp(new ofAppViewer());
    } else if (mode == "record") {
        // pass mode as 1
        // pass recording directory
        ofRunApp(new ofApp());
    } else {
        // default mode would be to detect emotions on runtime
        ofRunApp(new ofApp());
    }
    
   }
