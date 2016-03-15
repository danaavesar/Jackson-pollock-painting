#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "Stroke.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxKinect kinect;       //Kinect
    ofImage kinectImage;    // Kinect
    ofImage depthImage;     // Kinect
    // GUI
    ofxPanel gui;
    ofxFloatSlider thresh;
    ofxFloatSlider minRadius;
    ofxFloatSlider maxRadius;
    
    
    //blob tracking
    float threshold;
    ofxCv::ContourFinder contourFinder;
    bool showLabels;
    
    ofxCv::RunningBackground background;
   	ofImage thresholded;
    
    vector<ofPolyline> positions;
    vector<int> strokeNumbers;
    
    cv::Mat thresholded_mat;
    
    ofxCv::RectTracker tracker;
    ofImage cam_image;
    
    //painting
    vector <Stroke> strokes;
//    vector <unsigned int> & newLabels;
    vector <int> prevLabels;
    int prevNumBlobs;
   // const vector<unsigned int>& prevDeadLabels;
    stringstream data;
    int strokeSize;

    
};