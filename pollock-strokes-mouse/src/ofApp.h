#pragma once

#pragma once

#include "ofMain.h"
#include "Circle.h"
#include "Line.h"
#include "Weirdo.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    
    int blobNumber;
    int divider = 150;
    vector <Circle> circles;
    vector <Line> lines;
    vector <Weirdo> weirdos;
    int prevMouseX;
    int prevMouseY;
    float weight;
    int curveProbability;
    int weirdoCircleProbability;
    ofColor color;
    
    ofImage Pollock;
    
    
    
    
};
