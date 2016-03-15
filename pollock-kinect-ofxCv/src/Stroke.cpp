//
//  Stroke.cpp
//  pollock-strokes-kinect-new
//
//  Created by Dana Avesar on 2/16/16.
//
//

#include "Stroke.h"

//--------------------------------------------------------------
void Stroke::setup(int _blobNumber){
    blobNumber = _blobNumber;
    color.r = ofRandom(0,255);
    color.g = ofRandom(0,255);
    color.b = ofRandom(0,255);
    
}

//--------------------------------------------------------------
void Stroke::update(){
    
}
//--------------------------------------------------------------
void Stroke::draw(){
    ofPushStyle();
    ofSetColor(color);
    ofFill();
    for(int i=0; i<circles.size(); i++){
        circles[i].draw();
    }
    
    ofNoFill();
    
    
    for(int i=0; i<weirdos.size(); i++){
        weirdos[i].draw();
    }
    if(lines.size() > 1){
        for(int i=0; i<lines.size()-2; i++){
            ofSetLineWidth(lines[i+1].width/2); //line width dependent on last point in line (determined by how far it is from first point, variable labeled wrong, posEnd is actually beginning point in each line)
            //            cout << lines[i].width << endl;
            ofBeginShape();
            //im actually drawing a bunch of little lines after one another so that i can manipulate the stroke width of each segement deoending on how fast the mouse is moving
            
            ofCurveVertex( lines[i].posEnd.x, lines[i].posEnd.y);
            ofCurveVertex( lines[i].posEnd.x, lines[i].posEnd.y);
            ofCurveVertex( lines[i+1].posEnd.x, lines[i+1].posEnd.y);
            
            ofCurveVertex( lines[i+2].posEnd.x, lines[i+2].posEnd.y);
            
            ofEndShape();
        }
    }
    ofPopStyle();
    
    
}

//--------------------------------------------------------------
void Stroke::loadPoints(int x, int y){
    //find the previous mouseX and the current mouseX
    //get the distance between those points
    //the bigger the distance the smaller the circle
    //divide the distance by constant int
    
    float dist  = ofDist(prevMouseX, prevMouseY, x, y);
    
    float radius;
    if(dist != 0){
        radius = divider/dist;
    }else{
        radius = 0;
    }
    
    
    Line myLine;
    curveProbability = ofRandom(0, 10);         //random probability for adding curvies in the line
    myLine.posEnd.x = x;
    myLine.posEnd.y = y;
    if(curveProbability < 2){
        myLine.posEnd.x = ofRandom(x-20, x);
        myLine.posEnd.y = ofRandom(y+20, y);
    }
    myLine.width = radius;
    lines.push_back(myLine);
    
    
    //if the distance is small then start adding circles
    weirdoCircleProbability = ofRandom(0,10);
    
    
    if(weirdoCircleProbability > 1){
        Circle tempCircle;
        tempCircle.setup(x,y, radius);
        circles.push_back(tempCircle);
    }else{
        Weirdo myWeirdo;
        myWeirdo.setup(x,y, prevMouseX,prevMouseY, radius);
        weirdos.push_back(myWeirdo);
    }
    
    prevMouseX = x;
    prevMouseY = y;
    
    
    
}
