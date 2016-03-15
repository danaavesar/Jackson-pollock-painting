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
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    int width;
    int divider = 90;
    vector <Circle> circles;
    vector <Line> lines;
    vector <Weirdo> weirdos;
    int prevMouseX;
    int prevMouseY;
    float weight;
    int curveProbability;
    int weirdoCircleProbability;
    
};
