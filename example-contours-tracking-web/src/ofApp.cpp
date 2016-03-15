#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0);
	
    movie.load("walking2.m4v"); //video_1.mov");
	movie.play();
	
	contourFinder.setMinAreaRadius(1);
	contourFinder.setMaxAreaRadius(100);
	contourFinder.setThreshold(15);
  //  contourFinder.setAutoThreshold(false);
	 contourFinder.setSimplify(false);
    
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
    
    thresholded_mat = Mat(movie.getHeight(),movie.getWidth(),CV_8UC3);
    
    cam_image.allocate(movie.getWidth(), movie.getHeight(), OF_IMAGE_COLOR); //_ALPHA);
    cam_image.setUseTexture(false);

    
}

void ofApp::update() {
    
    //  background.setThresholdValue(ofMap(mouseX, 0, ofGetWidth(), 0, 100));
	movie.update();
	if(movie.isFrameNew()) {
        
         Mat liveMat;
        copy(movie,liveMat);
        
        bool bMirror = false;
        bool bFlip = false;
        
        int temp_mirror;
        if(bMirror == true && bFlip == true) temp_mirror = -1;
        if(bMirror == true && bFlip == false) temp_mirror = 0;
        if(bMirror == false && bFlip == true) temp_mirror = 1;
        if(bMirror == false && bFlip == false){
        }else{
            flip(liveMat,liveMat,temp_mirror); //0 flip x-axis, 1 means flip y-axis, -1 flip x&y axis
        }
        
        copy(liveMat, cam_image);
        cam_image.update();

        
        /*
        background.update(cam_image, thresholded); //_mat);
        thresholded.update();
        
      //  erode(thresholded, thresholded,40);
       // dilate(thresholded, thresholded,20);
		blur(thresholded, 20);
        contourFinder.findContours(thresholded); //_mat);
        */
        background.update(cam_image, thresholded_mat);
        //thresholded.update();

        
//        p1 = cv::Point(0,0);
//        p2 = cv::Point(ROI_left,camHeight);
//        cv::rectangle(thresholded_mat, p1, p2 , cvScalar(0, 0, 0), -1, 8, 0);

        cv::circle(thresholded_mat, cv::Point(mouseX,mouseY), 5, cvScalar(255,255,255),-1, 8, 0);
    
        
        //  erode(thresholded, thresholded,40);
        // dilate(thresholded, thresholded,20);
        blur(thresholded_mat,thresholded_mat,20);
        contourFinder.findContours(thresholded_mat); //_mat);
        tracker = contourFinder.getTracker();
        
        copy(thresholded_mat,thresholded);
        thresholded.update();
        
  

	}
}

void ofApp::draw() {
	ofSetBackgroundAuto(showLabels);
		
	//if(showLabels) {
		ofSetColor(255);
		movie.draw(0, 0);
		contourFinder.draw();
		for(int i = 0; i < contourFinder.size(); i++) {
			ofPoint center = toOf(contourFinder.getCenter(i));
			ofPushMatrix();
			ofTranslate(center.x, center.y);
			int label = contourFinder.getLabel(i);
			string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
			ofDrawBitmapStringHighlight(msg, 0, 0);
			ofVec2f velocity = toOf(contourFinder.getVelocity(i));
			ofScale(5, 5);
			ofDrawLine(0, 0, velocity.x, velocity.y);
			ofPopMatrix();
		}
	//} else {
    
    
    int a = contourFinder.size();
    int c = tracker.getCurrentLabels().size();
    int p = tracker.getDeadLabels().size();
    if(a-c != 0){
        ofLog()<<"contourFinder.size() "<<a;
        ofLog()<<"getCurrentLabels().size() "<<c;
    }
    if(a-p != 0){
        ofLog()<<"contourFinder.size() "<<a;
        ofLog()<<"getDeadLabels().size() "<<p;
    }
    
		for(int i = 0; i < contourFinder.size(); i++) {
			unsigned int label = contourFinder.getLabel(i);
			// only draw a line if this is not a new label
			if(tracker.existsPrevious(label)) {
				// use the label to pick a random color
				ofSeedRandom(label << 24);
				
				// get the tracked object (cv::Rect) at current and previous position
				const cv::Rect& previous = tracker.getPrevious(label);
				const cv::Rect& current = tracker.getCurrent(label);
				// get the centers of the rectangles
				ofVec2f previousPosition(previous.x + previous.width / 2, previous.y + previous.height / 2);
				ofVec2f currentPosition(current.x + current.width / 2, current.y + current.height / 2);
                
               // ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
                positions[label].addVertex(currentPosition);
				//ofDrawLine(previousPosition, currentPosition);
              //positions[label].draw();
			}
            
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
	ofSetColor(cyanPrint);
	for(int i = 0; i < currentLabels.size(); i++) {
		int j = currentLabels[i];
		ofDrawLine(j, 0, j, 4);
	}
	ofSetColor(magentaPrint);
	for(int i = 0; i < previousLabels.size(); i++) {
		int j = previousLabels[i];
		ofDrawLine(j, 4, j, 8);
	}
	ofSetColor(yellowPrint);
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
    drawMat(thresholded_mat, 0, 0);
    ofPopMatrix();
}

void ofApp::keyPressed(int key) {
	if(key == 'l') {
		showLabels = !showLabels;
	}
    
    if(key == ' ') {
        background.reset();
    }

    if(key == '0') {
        movie.setFrame(0);
    }
}