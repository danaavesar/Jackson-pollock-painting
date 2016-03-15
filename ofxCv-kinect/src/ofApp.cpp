#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //画面設定
    ofSetFrameRate(60);
    ofBackground(0);
    // Kinect初期化
    kinect.init();
    kinect.open();
    // GUI初期設定
    gui.setup();
    gui.add(thresh.setup("Threshhold", 127, 0, 255));
    gui.add(minRadius.setup("Min Radius", 10, 0, 400));
    gui.add(maxRadius.setup("Max Radius", 200, 0, 400));
    
    //TRACKER
    // wait for half a frame before forgetting something
    contourFinder.getTracker().setPersistence(200);
    // an object can move up to 32 pixels per frame
    contourFinder.getTracker().setMaximumDistance(123);
    showLabels = true;
    
    background.setDifferenceMode(background.ABSDIFF);
    background.setIgnoreForeground(false);
    background.setLearningTime(80);
    background.setThresholdValue(50);
    positions.resize(10000);
}

//--------------------------------------------------------------
void ofApp::update(){
    // CV設定
    contourFinder.setMinAreaRadius(minRadius);
    contourFinder.setMaxAreaRadius(maxRadius);
    // Kinect状態更新
    kinect.update();
    if (kinect.isFrameNew()) {
        // Kinectの深度画像を、cv::Mat形式に変換
        cv::Mat mat = cv::Mat(kinect.height, kinect.width, CV_8UC1, kinect.getDepthPixels(), 0);
        // ofxCvで輪郭抽出
        contourFinder.setThreshold(thresh);
        contourFinder.findContours(mat);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    kinect.drawDepth(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 255, 0);
    ofPushMatrix();
    ofScale(ofGetWidth() / float(kinect.width), ofGetHeight() / float(kinect.height));
    contourFinder.draw();
    ofPopMatrix();
    // GUI
    gui.draw();
    
    //TRACKER -------------------------------------
     tracker = contourFinder.getTracker();
    for(int i = 0; i < contourFinder.size(); i++) {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i)); //center of blobs?
        ofPushMatrix();
        ofTranslate(center.x, center.y);
        int label = contourFinder.getLabel(i);
        string msg = ofToString(label); //label is the id i guess
        ofDrawBitmapStringHighlight(msg, 0, 0);
        ofVec2f velocity = ofxCv::toOf(contourFinder.getVelocity(i));
        ofScale(5, 5);
        ofDrawLine(0, 0, velocity.x, velocity.y);
        ofPopMatrix();
    }

    
    ofSetColor(0,0,255);
    for(int i = 0; i < tracker.getCurrentLabels().size(); i++) {
        int label = tracker.getLabelFromIndex(i);
        
        ofLog()<<i<<" label "<<label<<" age "<<tracker.getAge(label);
        positions[label].draw();
    }
    
    ofSetColor(255,0,0);
    vector<unsigned int> dead = tracker.getDeadLabels();
    for(int i = 0; i < dead.size(); i++) {
        int label = dead[i];
        positions[label].draw();
        ofPoint lastPoint = positions[label].getPointAtPercent(100);
        string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
        ofDrawBitmapStringHighlight(msg, lastPoint,ofColor(255,0,0),ofColor(255,255,255));
        
    }
    
    
    for(int i = 0; i < contourFinder.size(); i++) {
        int label = tracker.getLabelFromIndex(i);
        ofLog()<<i<<" n ."<<label<<" , "<<tracker.getLastSeen(label)<<" , "<<tracker.getAge(label);
    }
    ofLog()<<"------------";
    for(int i = 0; i < dead.size(); i++) {
        int label = dead[i];
        ofLog()<<i<<" o ."<<label<<" , "<<tracker.getLastSeen(label)<<" , "<<tracker.getAge(label);
        
    }
    //}
    
    // this chunk of code visualizes the creation and destruction of labels
    const vector<unsigned int>& currentLabels = tracker.getCurrentLabels();
    const vector<unsigned int>& previousLabels = tracker.getPreviousLabels();
    const vector<unsigned int>& newLabels = tracker.getNewLabels();
    const vector<unsigned int>& deadLabels = tracker.getDeadLabels();
    ofSetColor(ofxCv::cyanPrint);
    for(int i = 0; i < currentLabels.size(); i++) {
        int j = currentLabels[i];
        ofDrawLine(j, 0, j, 4);
    }
    ofSetColor(ofxCv::magentaPrint);
    for(int i = 0; i < previousLabels.size(); i++) {
        int j = previousLabels[i];
        ofDrawLine(j, 4, j, 8);
    }
    ofSetColor(ofxCv::yellowPrint);
    for(int i = 0; i < newLabels.size(); i++) {
        int j = newLabels[i];
        ofDrawLine(j, 8, j, 12);
    }
    ofSetColor(ofColor::white);
    for(int i = 0; i < deadLabels.size(); i++) {
        int j = deadLabels[i];
        ofDrawLine(j, 12, j, 16);
    }
    
    //thresholded.draw(0, ofGetHeight()-320,320,320*9/16.0);
    ofPushMatrix();
    ofTranslate(0, ofGetHeight()-320);
    ofScale(0.3, 0.3);
    ofxCv::drawMat(thresholded_mat, 0, 0);
    ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}