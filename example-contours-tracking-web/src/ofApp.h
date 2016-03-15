#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	float threshold;
	ofVideoPlayer movie;	
	ofxCv::ContourFinder contourFinder;
	bool showLabels;
    
        ofxCv::RunningBackground background;
   	ofImage thresholded;

    vector<ofPolyline> positions;
    
      cv::Mat thresholded_mat;
    
    ofxCv::RectTracker tracker;
    ofImage cam_image;
};
