
#pragma once
#include "ofMain.h"

class Line : public ofBaseApp{
public:
    
    void setup(float _mouseX, float _mouseY, float _prevMouseX, float _prevMouseY, float _weight );
    void draw();
    void update();
    ofPoint posBeg;
    ofPoint posEnd;
    float width;
    ofPoint random;
    
    
    
};


