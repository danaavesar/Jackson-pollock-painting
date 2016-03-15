#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //--------------- kinect ------------
    ofBackground(255, 255, 255);
    

              Stroke newStroke;
            strokes.push_back(newStroke);
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //--------------- kinect ------------
   
    
    
    //draw the points
    ofPushMatrix();
    ofScale(1.6 , 1.6, 0.0 );
//    ofTranslate( x, y, 0.0 );
for( int i=0; i<strokes.size(); i++ ) {
        strokes[0].draw();
    }
   
    ofPopMatrix();;
    
    

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
void ofApp::exit() {

    
}

