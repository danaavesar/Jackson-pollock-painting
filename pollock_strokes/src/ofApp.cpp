#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetFrameRate(260);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
   

    ofSetColor(0, 0, 0);
    ofFill();
    for(int i=0; i<circles.size(); i++){
        circles[i].draw();
    }
    
    
        ofNoFill();
        ofSetColor(0,0,0);
        ofBeginShape();
        for(int i=0; i<lines.size(); i++){
            ofCurveVertex( lines[i].posEnd.x, lines[i].posEnd.y);
        }
        ofEndShape();
   
    for(int i=0; i<weirdos.size(); i++){
        weirdos[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //find the previous mouseX and the current mouseX
    //get the distance between those points
    //the bigger the distance the smaller the circle
    //divide the distance by constant int

    float dist  = ofDist(prevMouseX, prevMouseY, x, y);
//     cout << dist << endl;
    float radius;
    if(dist != 0){
         radius = divider/dist;
    }else{
        radius = 0;
    }
         cout << radius << endl;

//        Circle tempCircle;
//        tempCircle.setup(mouseX,mouseY, radius);
//        circles.push_back(tempCircle);
    
    if(dist < 60){
        Line myLine;
         curveProbability = ofRandom(0, 10);         //random probability for adding curvies in the line
        myLine.posBeg.x= prevMouseX;
        myLine.posBeg.y = prevMouseY;
        myLine.posEnd.x = x;
        myLine.posEnd.y = y;
        if(curveProbability < 2){
         myLine.posEnd.x = ofRandom(x-20, x);
         myLine.posEnd.y = ofRandom(y+20, y);
        }
        width = weight;
   
//        myLine.setup(x,y, prevMouseX,prevMouseY, weight);
        lines.push_back(myLine);
    }
    
    //if the distance is small then start adding circles
    weirdoCircleProbability = ofRandom(0,10);
    
//    if(dist <4){
    if(weirdoCircleProbability > 1){
        Circle tempCircle;
        tempCircle.setup(mouseX,mouseY, radius);
        circles.push_back(tempCircle);
    }else{
        Weirdo myWeirdo;
        myWeirdo.setup(x,y, prevMouseX,prevMouseY, radius);
        weirdos.push_back(myWeirdo);
    }
    
//    }


  
    prevMouseX = x;
    prevMouseY = y;
    
    
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
