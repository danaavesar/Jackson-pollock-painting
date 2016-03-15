#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    // Kinect
    kinect.init();
    kinect.open();
    // GUI
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
    
//    background.setDifferenceMode(background.ABSDIFF);
//    background.setIgnoreForeground(false);
//    background.setLearningTime(80);
//    background.setThresholdValue(50);
    positions.resize(10000);
    strokeSize = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
   
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //previously update
    // CV
    contourFinder.setMinAreaRadius(38);//44
    contourFinder.setMaxAreaRadius(130);
    // Kinect
    kinect.update();
    if (kinect.isFrameNew()) {
        // Kinect cv::Mat
        cv::Mat mat = cv::Mat(kinect.height, kinect.width, CV_8UC1, kinect.getDepthPixels(), 0);
        // ofxCv
        contourFinder.setThreshold(thresh);//178.5
        contourFinder.findContours(mat);
    }
    
    //check when new blobs appear, check when blobs disappear
    //create strokes for every new blob
    //tracker.getPreviousLabels();
    //    tracker.getNewLabels();
    //    tracker.getDeadLabels();
    
    const vector<unsigned int>& newLabels = tracker.getNewLabels();
    const vector<unsigned int>& deadLabels = tracker.getDeadLabels();
    const vector<unsigned int>& currentLabels = tracker.getCurrentLabels();
    //    const vector<unsigned int>& previousLabels = tracker.getPreviousLabels();
    
    for(int i = 0; i < contourFinder.size(); i++) {
        unsigned int label = contourFinder.getLabel(i);
        if(!tracker.existsPrevious(label)){
            
            bool inAlready = false;
            if(strokes.size() > 0){ //check to see if this label has been added before (the existPrevious doesnt work well
                for(int i=0; i<strokes.size(); i++){
                    if(label == strokes[i].blobNumber){
                        inAlready = true;
                    }
                }
                if(inAlready == false){
                    cout<< label << endl;
                    Stroke newStroke;
                    newStroke.setup(label);
                    strokes.push_back(newStroke);
                }
            }else if(strokes.size() == 0){
                Stroke newStroke;
                newStroke.setup(label);
                strokes.push_back(newStroke);
            }
            
        }
    }
    
    //    for( int i=0; i<deadLabels.size(); i++){
    //        cout << "dead " << deadLabels[i] << endl;
    //    }
    
    //load the points into the strokes
    if(strokes.size()>0){
        for(int i = 0; i < contourFinder.size(); i++) {
            int label = contourFinder.getLabel(i); //check which label == which stroke
            for( int j=0; j<strokes.size(); j++ ) { //loop through all strokes
                
                if(label == strokes[j].blobNumber){
                    ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
                    strokes[j].loadPoints(center.x,center.y);
                }
            }
            
            
            
        }
    }
//--------------------------------------------------------------------
    ofSetColor(255);
    //kinect.drawDepth(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255, 255, 0);
    ofPushMatrix();
    ofScale(ofGetWidth() / float(kinect.width), ofGetHeight() / float(kinect.height));
    //contourFinder.draw();
    ofPopMatrix();
    // GUI
    gui.draw();
    
    //TRACKER -------------------------------------
    tracker = contourFinder.getTracker();
    ofPushMatrix();
    ofScale(ofGetWidth() / float(kinect.width), ofGetHeight() / float(kinect.height));
    for(int i = 0; i < contourFinder.size(); i++) {
        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i)); //center of blobs?
        ofPushMatrix();
        ofTranslate(center.x, center.y);
        int label = contourFinder.getLabel(i);
        string msg = ofToString(label); //label is the id i guess
//        ofDrawBitmapStringHighlight(msg, 0, 0);
        ofVec2f velocity = ofxCv::toOf(contourFinder.getVelocity(i));
        ofScale(5, 5);
       // ofDrawLine(0, 0, velocity.x, velocity.y);
        ofPopMatrix();
        
    }
    ofPopMatrix();
    

    
    
    //----strokes
    //draw the points
    ofPushMatrix();
    //ofScale(1.6 , 1.6, 0.0 );
    ofScale(ofGetWidth() / float(kinect.width), ofGetHeight() / float(kinect.height));
    
     
    for( int i=0; i<strokes.size(); i++ ) {
        strokes[i].draw();
        
    }
    
    
    
    ofPopMatrix();
    
    ofPushStyle();
    ofSetColor(255,0,0);

    //if(strokes.size() > strokeSize){
        //for(int i= strokeSize; i< strokes.size(); i++){
        for(int i= 0; i< strokes.size(); i++){
            //ofDrawBitmapString(strokes[i].blobNumber, 20 + i*20, 652);
        }
   // }
    
    ofPopStyle();

    strokeSize = strokes.size();
    
    

    
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