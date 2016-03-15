//
//  Stroke.h
//  pollock-strokes-kinect-new
//
//  Created by Dana Avesar on 2/16/16.
//
//


#pragma once

#include "ofMain.h"
#include "Circle.h"
#include "Line.h"
#include "Weirdo.h"


class Stroke : public ofBaseApp{
    
public:
    void setup(int blobNumber);
    void update();
    void draw();
    void loadPoints(int x, int y);
    
    int blobNumber;
    int divider = 50;
    vector <Circle> circles;
    vector <Line> lines;
    vector <Weirdo> weirdos;
    int prevMouseX;
    int prevMouseY;
    float weight;
    int curveProbability;
    int weirdoCircleProbability;
    ofColor color;
    
    
};