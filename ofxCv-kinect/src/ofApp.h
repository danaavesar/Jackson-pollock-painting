#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxCv.h"

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
    
    ofxKinect kinect;       //Kinectインスタンス
    ofImage kinectImage;    // Kinectカメラ映像
    ofImage depthImage;     // Kinect深度映像
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
    
    cv::Mat thresholded_mat;
    
    ofxCv::RectTracker tracker;
    ofImage cam_image;

};